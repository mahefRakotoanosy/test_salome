//  SALOME Container : implementation of container and engine for Kernel
//
//  Copyright (C) 2003  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
//  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS 
// 
//  This library is free software; you can redistribute it and/or 
//  modify it under the terms of the GNU Lesser General Public 
//  License as published by the Free Software Foundation; either 
//  version 2.1 of the License. 
// 
//  This library is distributed in the hope that it will be useful, 
//  but WITHOUT ANY WARRANTY; without even the implied warranty of 
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
//  Lesser General Public License for more details. 
// 
//  You should have received a copy of the GNU Lesser General Public 
//  License along with this library; if not, write to the Free Software 
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA 
// 
//  See http://www.opencascade.org/SALOME/ or email : webmaster.salome@opencascade.org 
//
//
//
//  File   : Component_i.cxx
//  Author : Paul RASCLE, EDF - MARC TAJCHMAN, CEA
//  Module : SALOME
//  $Header$

using namespace std;
#include "SALOME_Component_i.hxx"
#include "RegistryConnexion.hxx"
#include "OpUtil.hxx"
#include <stdio.h>
#include <dlfcn.h>
#include "utilities.h"

extern bool _Sleeping ;

Engines_Component_i::Engines_Component_i()
{
//  MESSAGE("Component constructor");
}

Engines_Component_i::Engines_Component_i(CORBA::ORB_ptr orb,
					 PortableServer::POA_ptr poa, 
					 PortableServer::ObjectId * contId, 
					 const char *instanceName,
					 const char *interfaceName,
                                         bool notif) :
  _instanceName(instanceName), _interfaceName(interfaceName),
  _myConnexionToRegistry(0), _ThreadId(0) , _graphName("") , _nodeName("") {
  MESSAGE("Component constructor with instanceName "<< _instanceName);
  _orb = CORBA::ORB::_duplicate(orb);
  _poa = PortableServer::POA::_duplicate(poa);
  _contId = contId ;
  CORBA::Object_var o = _poa->id_to_reference(*contId); // container ior...
  const CORBA::String_var ior = _orb->object_to_string(o);
  _myConnexionToRegistry = new RegistryConnexion(0, 0, ior, "theSession", _instanceName.c_str());

  _notifSupplier = new NOTIFICATION_Supplier(instanceName, notif);
}

// Constructeur pour composant parallele: ne pas faire appel au registry!!
Engines_Component_i::Engines_Component_i(CORBA::ORB_ptr orb,
					 PortableServer::POA_ptr poa, 
					 PortableServer::ObjectId * contId, 
					 const char *instanceName,
					 const char *interfaceName,
					 int flag,
                                         bool notif )
  : _instanceName(instanceName),
    _interfaceName(interfaceName),
    _myConnexionToRegistry(0),
    _ThreadId(0)
{
//  MESSAGE("Component constructor with instanceName "<< _instanceName);
  _orb = CORBA::ORB::_duplicate(orb);
  _poa = PortableServer::POA::_duplicate(poa);
  _contId = contId ;
  //  CORBA::Object_var myself = this->_this(); //appel a _this = increment reference

  _notifSupplier = new NOTIFICATION_Supplier(instanceName, notif);
}

Engines_Component_i::~Engines_Component_i()
{
  MESSAGE("Component destructor");
//   delete _myConnexionToRegistry;
//   _myConnexionToRegistry = 0 ;
}

char* Engines_Component_i::instanceName() {
   return CORBA::string_dup(_instanceName.c_str()) ;
}

char* Engines_Component_i::interfaceName() {
   return CORBA::string_dup(_interfaceName.c_str()) ;
}

void Engines_Component_i::ping()
{
  MESSAGE("Engines_Component_i::ping() pid "<< getpid() << " threadid "
          << pthread_self());
}

void Engines_Component_i::destroy()
{
  MESSAGE("Engines_Component_i::destroy()");

  delete _notifSupplier;
  _notifSupplier = 0;

  delete _myConnexionToRegistry;
  _myConnexionToRegistry = 0 ;
  _poa->deactivate_object(*_id) ;
  CORBA::release(_poa) ;
  delete(_id) ;
  _thisObj->_remove_ref();
  MESSAGE("Engines_Component_i::destroyed") ;
}

Engines::Container_ptr Engines_Component_i::GetContainerRef()
{
  MESSAGE("Engines_Component_i::GetContainerRef");
  CORBA::Object_ptr o = _poa->id_to_reference(*_contId) ;
  return Engines::Container::_narrow(o);
}

PortableServer::ObjectId * Engines_Component_i::getId()
{
//  MESSAGE("PortableServer::ObjectId * Engines_Component_i::getId()");
  return _id ;
}

void Engines_Component_i::beginService(const char *serviceName)
{
  MESSAGE("Send BeginService notification for " << serviceName << endl
	  << "Component instance : " << _instanceName << endl << endl);
  _ThreadId = pthread_self() ;
  _StartUsed = 0 ;
  _StartUsed = CpuUsed_impl() ;
  _serviceName = serviceName ;
  if ( pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS , NULL ) ) {
    perror("pthread_setcanceltype ") ;
    exit(0) ;
  }
  if ( pthread_setcancelstate( PTHREAD_CANCEL_ENABLE , NULL ) ) {
    perror("pthread_setcancelstate ") ;
    exit(0) ;
  }
  MESSAGE("Return from BeginService for " << serviceName
          << " ThreadId " << _ThreadId
          << " _graphName " << _graphName << " _nodeName " << _nodeName );
}

void Engines_Component_i::endService(const char *serviceName)
{
  MESSAGE("Send EndService notification for " << serviceName << endl
	  << "Component instance : " << _instanceName << endl << endl);
  _ThreadId = 0 ;
}

void Engines_Component_i::Names( const char * graphName ,
                                 const char * nodeName ) {
  _graphName = graphName ;
  _nodeName = nodeName ;
//  MESSAGE("Engines_Component_i::Names( '" << _graphName << "' , '"
//          << _nodeName << "' )");
}

char* Engines_Component_i::graphName() {
  return CORBA::string_dup( _graphName.c_str() ) ;
}

char* Engines_Component_i::nodeName() {
  return CORBA::string_dup( _nodeName.c_str() ) ;
}

bool Killer( int ThreadId , int signum ) {
  if ( ThreadId ) {
    if ( signum == 0 ) {
      if ( pthread_cancel( ThreadId ) ) {
        perror("Killer pthread_cancel error") ;
        return false ;
      }
      else {
        MESSAGE("Killer : ThreadId " << ThreadId << " pthread_canceled") ;
      }
    }
    else {
      if ( pthread_kill( ThreadId , signum ) == -1 ) {
        perror("Killer pthread_kill error") ;
        return false ;
      }
      else {
        MESSAGE("Killer : ThreadId " << ThreadId << " pthread_killed("
                << signum << ")") ;
      }
    }
  }
  return true ;
}

bool Engines_Component_i::Kill_impl() {
  MESSAGE("Engines_Component_i::Kill_i() pthread_t "<< pthread_self()
          << " pid " << getpid() << " instanceName "
          << _instanceName.c_str() << " interface " << _interfaceName.c_str()
          << " machineName " << GetHostname().c_str()<< " _id " << hex << _id
          << dec << " _ThreadId " << _ThreadId << " this " << hex << this
          << dec ) ;
  bool RetVal = false ;
  if ( _ThreadId > 0 && pthread_self() != _ThreadId ) {
    RetVal = Killer( _ThreadId , 0 ) ;
    _ThreadId = (pthread_t ) -1 ;
  }
  return RetVal ;
}

bool Engines_Component_i::Stop_impl() {
  MESSAGE("Engines_Component_i::Stop_i() pthread_t "<< pthread_self()
          << " pid " << getpid() << " instanceName "
          << _instanceName.c_str() << " interface " << _interfaceName.c_str()
          << " machineName " << GetHostname().c_str()<< " _id " << hex << _id
          << dec << " _ThreadId " << _ThreadId );
  bool RetVal = false ;
  if ( _ThreadId > 0 && pthread_self() != _ThreadId ) {
    RetVal = Killer( _ThreadId , 0 ) ;
    _ThreadId = (pthread_t ) -1 ;
  }
  return RetVal ;
}

bool Engines_Component_i::Suspend_impl() {
  MESSAGE("Engines_Component_i::Suspend_i() pthread_t "<< pthread_self()
          << " pid " << getpid() << " instanceName "
          << _instanceName.c_str() << " interface " << _interfaceName.c_str()
          << " machineName " << GetHostname().c_str()<< " _id " << hex << _id
          << dec << " _ThreadId " << _ThreadId );
  bool RetVal = false ;
  if ( _ThreadId > 0 && pthread_self() != _ThreadId ) {
    if ( _Sleeping ) {
      return false ;
    }
    else {
      RetVal = Killer( _ThreadId ,SIGINT ) ;
    }
  }
  return RetVal ;
}

bool Engines_Component_i::Resume_impl() {
  MESSAGE("Engines_Component_i::Resume_i() pthread_t "<< pthread_self()
          << " pid " << getpid() << " instanceName "
          << _instanceName.c_str() << " interface " << _interfaceName.c_str()
          << " machineName " << GetHostname().c_str()<< " _id " << hex << _id
          << dec << " _ThreadId " << _ThreadId );
  bool RetVal = false ;
  if ( _ThreadId > 0 && pthread_self() != _ThreadId ) {
    if ( _Sleeping ) {
      _Sleeping = false ;
      RetVal = true ;
    }
    else {
      RetVal = false ;
    }
  }
  return RetVal ;

}

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

long Engines_Component_i::CpuUsed_impl() {
  struct rusage usage ;
  long cpu ;
  if ( getrusage( RUSAGE_SELF , &usage ) == -1 ) {
    perror("GraphBase::CpuUsed") ;
    return 0 ;
  }
//  return usage.ru_utime.__time_t tv_sec ;
  cout << "CpuUsed " << usage.ru_utime.tv_sec << " " << usage.ru_utime.tv_usec << " "
       << usage.ru_stime.tv_sec << " " << usage.ru_stime.tv_usec << endl ;
  cpu = usage.ru_utime.tv_sec - _StartUsed ;
  return cpu ;
}

// Send message to event channel

void Engines_Component_i::sendMessage(const char *event_type, const char *message) {
    _notifSupplier->Send(graphName(), nodeName(), event_type, message);
}
