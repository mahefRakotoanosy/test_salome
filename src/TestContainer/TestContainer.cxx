//  SALOME TestContainer : test of container creation and its life cycle
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
//  File   : TestContainer.cxx
//  Author : Paul RASCLE, EDF - MARC TAJCHMAN, CEA
//  Module : SALOME
//  $Header$

using namespace std;
#include "utilities.h"
#include <iostream>
#include <unistd.h>
#include <SALOMEconfig.h>
#include CORBA_CLIENT_HEADER(SALOME_Component)
#include CORBA_CLIENT_HEADER(SALOME_TestComponent)

#include "SALOME_NamingService.hxx"
#include "OpUtil.hxx"
#include "Utils_ORB_INIT.hxx"
#include "Utils_SINGLETON.hxx"
#include "Utils_SALOME_Exception.hxx"
#include "Utils_CommException.hxx"
using namespace std;

int main (int argc, char * argv[])
{

  try
    {
      // Initializing omniORB
      CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
    
      // use IOR to find container
      //if (argc != 2) { return 1; }
      //CORBA::Object_var obj = orb->string_to_object(argv[1]);
      //Engines::Container_var iGenFact = Engines::Container::_narrow(obj);

      // Obtain a reference to the root POA
      //
      long TIMESleep = 250000000;
      int NumberOfTries = 40;
      int a;
      timespec ts_req;
      ts_req.tv_nsec=TIMESleep;
      ts_req.tv_sec=0;
      timespec ts_rem;
      ts_rem.tv_nsec=0;
      ts_rem.tv_sec=0;
      CosNaming::NamingContext_var inc;
      PortableServer::POA_var poa;
      CORBA::Object_var theObj;
      CORBA::Object_var obj;
      CORBA::Object_var object;
      SALOME_NamingService &naming = *SINGLETON_<SALOME_NamingService>::Instance() ;
      int TEST_CONTAINER=0;
      const char * Env = getenv("USE_LOGGER"); 
      int EnvL =0;
      if ((Env!=NULL) && (strlen(Env)))
	EnvL=1;
      CosNaming::Name name;
      name.length(1);
      name[0].id=CORBA::string_dup("Logger");    
      PortableServer::POAManager_var manager; 
      for (int i = 1; i<=NumberOfTries; i++)
	{
	  if (i!=1) 
	    a=nanosleep(&ts_req,&ts_rem);
	  try
	    { 
	      obj = orb->resolve_initial_references("RootPOA");
	      if(!CORBA::is_nil(obj))
		poa = PortableServer::POA::_narrow(obj);
	      if(!CORBA::is_nil(poa))
		manager = poa->the_POAManager();
	      if(!CORBA::is_nil(orb)) 
		theObj = orb->resolve_initial_references("NameService");
	      if (!CORBA::is_nil(theObj))
		inc = CosNaming::NamingContext::_narrow(theObj);
	    }
	  catch( CORBA::COMM_FAILURE& )
	    {
	      MESSAGE( "Test Container: CORBA::COMM_FAILURE: Unable to contact the Naming Service" )
		}
	  if(!CORBA::is_nil(inc))
	    {
	      MESSAGE( "Test Container: Naming Service was found" )
		if(EnvL==1)
		  {
		    for(int j=1; j<=NumberOfTries; j++)
		      {
			if (j!=1) 
			  a=nanosleep(&ts_req, &ts_rem);
			try
			  {
			    object = inc->resolve(name);
			  }
			catch(CosNaming::NamingContext::NotFound)
			  {
			    MESSAGE( "Test Container: Logger Server wasn't found" );
			  }
			catch(...)
			  {
			    MESSAGE( "Test Container: Unknown exception" );
			  }
			if (!CORBA::is_nil(object))
			  {
			    MESSAGE( "Test Container: Loger Server was found" );
			    TEST_CONTAINER=1;
			    break;
			  }
		      }
		  }
	    }
	  if ((TEST_CONTAINER==1)||((EnvL==0)&&(!CORBA::is_nil(inc))))
            break;
	}
      // Use Name Service to find container
      SALOME_NamingService _NS(orb) ;
      string containerName = "/Containers/" ;
      string hostName = GetHostname();
      containerName += hostName + "/FactoryServer";

      obj = _NS.Resolve(containerName.c_str()) ;
      Engines::Container_var iGenFact = Engines::Container::_narrow(obj);

      Engines::TestComponent_var m1;
    
      for (int iter = 0; iter < 3 ; iter++)
	{
	  INFOS("----------------------------------------------------" << iter);   
          string dirn = getenv("KERNEL_ROOT_DIR");
          dirn += "/lib/salome/libSalomeTestComponentEngine.so";
          obj = iGenFact->load_impl("SalomeTestComponent",dirn.c_str());
	  m1 = Engines::TestComponent::_narrow(obj);
	  INFOS("recup m1");
	  SCRUTE(m1->instanceName());
	  INFOS("Coucou " << m1->Coucou(1L));
	  iGenFact->remove_impl(m1) ;
	  //iGenFact->finalize_removal() ; // unpredictable results ...
          sleep(5);
	}    
      // Clean-up.
      iGenFact->finalize_removal() ;
      orb->destroy();
    }
  catch(CORBA::COMM_FAILURE& ex) {
    INFOS("Caught system exception COMM_FAILURE -- unable to contact the object.")
      }
  catch(CORBA::SystemException&) {
    INFOS("Caught a CORBA::SystemException.")
      }
  catch(CORBA::Exception&) {
    INFOS("Caught CORBA::Exception.")
      }
  catch(...) {
    INFOS("Caught unknown exception.")
      }

  return 0;
}

