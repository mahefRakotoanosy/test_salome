//  SALOME ModuleCatalog : implementation of ModuleCatalog server which parsers xml description of modules
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
//  File   : SALOME_ModuleCatalog_Client.cxx
//  Module : SALOME

/* $Header$ */

#include <iostream>
#include "SALOME_NamingService.hxx"
#include "SALOME_ModuleCatalog.hh"
#include <string>
#include "utilities.h"
using namespace std;

void PrintService(SALOME_ModuleCatalog::Acomponent_ptr C,
		  const string & InterfaceName,
		  const string & ServiceName);

void PrintInterface(SALOME_ModuleCatalog::Acomponent_ptr C,
		    const string & InterfaceName);

void PrintComponent(SALOME_ModuleCatalog::Acomponent_ptr C);

int main(int argc,char **argv)
{

  CORBA::ORB_var orb;
  CosNaming::NamingContext_var _rootContext;
  CORBA::Object_var objVar, objVarN;
  try {

  	// initialize the ORB

  orb = CORBA::ORB_init (argc, argv);

 
  // Get CORBA reference of the catalog
  SALOME_NamingService NS(orb);
  CORBA::Object_var objVarN = NS.Resolve("/Kernel/ModulCatalog");

   SALOME_ModuleCatalog::ModuleCatalog_var Catalogue 
     = SALOME_ModuleCatalog::ModuleCatalog::_narrow(objVarN); 
   MESSAGE("Distant catalog of component found")

     // Get component list
   SALOME_ModuleCatalog::ListOfComponents_var list_composants 
     = Catalogue->GetComponentList();


   // Typed component list
   MESSAGE("Get Typed Component list (GEOM Type)");
   SALOME_ModuleCatalog::ListOfComponents_var list_typed_composants 
     = Catalogue->GetTypedComponentList(SALOME_ModuleCatalog::GEOM);
   for (unsigned int ind = 0; ind < list_typed_composants->length();ind++)
     MESSAGE("Component GEOM list : " << list_typed_composants[ind]);      

   MESSAGE("Get Typed Component list (SUPERV Type)");
   list_typed_composants 
     = Catalogue->GetTypedComponentList(SALOME_ModuleCatalog::SUPERV);
#ifndef WNT
   for (unsigned int ind = 0; ind < list_typed_composants->length();ind++)
#else
   for (ind = 0; ind < list_typed_composants->length();ind++)
#endif
      MESSAGE("Component SUPERV list : " << list_typed_composants[ind]);

   // Get list of couple (component name, component icone)
   SALOME_ModuleCatalog::ListOfIAPP_Affich_var list_composants_icone 
     = Catalogue->GetComponentIconeList();
#ifndef WNT
   for (unsigned int ind = 0; ind < list_composants_icone->length();ind++)
#else
   for (ind = 0; ind < list_composants_icone->length();ind++)
#endif
     {
       MESSAGE("Component name: " << list_composants_icone[ind].modulename);
       MESSAGE("Component icone: " << list_composants_icone[ind].moduleicone);
     }
  
   // obtain a component (specified as parameter of the client)
   SALOME_ModuleCatalog::Acomponent_ptr Geom = Catalogue->GetComponent("Geometry");
   if (CORBA::is_nil (Geom)) 
   {
     INFOS("Catalog Error : Component Geometry not found in the catalog")
      exit (-1);
   }
 
   PrintComponent(Geom);

     // Obtain another component
   SALOME_ModuleCatalog::Acomponent_ptr Superv = Catalogue->GetComponent("Supervision");
   if (CORBA::is_nil (Superv)) 
   {
     INFOS("Catalog Error : Component Supervision not found in the catalog")
      exit (-1);
   }
   PrintComponent(Superv);

     // obtain prefix path for a computer
   char* path;
   path =Superv->GetPathPrefix("omote");
   MESSAGE("Path prefix pour omote : " << path);

   // obtain prefix path for a computer
   path =Geom->GetPathPrefix("eri");
   MESSAGE("Path prefix pour eri : " << path);

    }
  catch(SALOME_ModuleCatalog::NotFound &ex){
    INFOS("SALOME_ModuleCatalog::NotFound")
      cerr << ex.what << endl;
  }
    catch(CORBA::SystemException&) {
      INFOS("Caught CORBA::SystemException.")
  }
    catch (CosNaming::NamingContext::CannotProceed &) {
      INFOS("CosNaming::NamingContext::CannotProceed")
  }
    catch (CosNaming::NamingContext::NotFound &) {
      INFOS("CosNaming::NamingContext::NotFound")
  }
    catch (CosNaming::NamingContext::InvalidName &) {
      INFOS("CosNaming::NamingContext::InvalidName")
  }
    catch (CosNaming::NamingContext::AlreadyBound &) {
      INFOS("CosNaming::NamingContext::AlreadyBound")
  }
    catch (CosNaming::NamingContext::NotEmpty &) {
      INFOS("CosNaming::NamingContext::NotEmpty")
  }

  catch(CORBA::Exception &sysEx) {
    INFOS("Caught CORBA::Exception.")
  }


  return 0;
}

void PrintComponent(SALOME_ModuleCatalog::Acomponent_ptr C)
{
  const char *_name = C->componentname();

  MESSAGE("Name : " <<  C->componentname());
  MESSAGE("Type : " << C->component_type() << " multistudy : " << C->multistudy());
  MESSAGE("Constraint : " << C->constraint());
  MESSAGE("Icon : " << C->component_icone());

  // obtain interfaces list of the component

  SALOME_ModuleCatalog::ListOfInterfaces_var _list = C->GetInterfaceList();
  for (unsigned int i = 0; i < _list->length();i++) {
    const char * s =  _list[i];
    PrintInterface(C, s);
  }
}


void PrintInterface(SALOME_ModuleCatalog::Acomponent_ptr C,
		    const string & InterfaceName)
{
  unsigned int i, n;
   	
   SALOME_ModuleCatalog::DefinitionInterface_var _interf 
     = C->GetInterface(InterfaceName.c_str());
   MESSAGE ("Interface : " << _interf->interfacename);

   SALOME_ModuleCatalog::ListOfInterfaceService S = _interf->interfaceservicelist;
   n = S.length();
   for (i = 0; i < n; i++) {
     const char * _S = S[i].ServiceName;
     PrintService(C, InterfaceName, _S);
   }
}

void PrintService(SALOME_ModuleCatalog::Acomponent_ptr C,
		  const string & InterfaceName,
		  const string & ServiceName)
{
  int i, n;

   SALOME_ModuleCatalog::Service_var Service 
     = (ServiceName.compare("") == 0)
     ? C->GetDefaultService(InterfaceName.c_str())
     : C->GetService(InterfaceName.c_str(), ServiceName.c_str());

   MESSAGE("Service : " << Service->ServiceName);
   
   MESSAGE("In Parameter(s):");
   n = Service->ServiceinParameter.length();
   for (i = 0; i<n; i++)
     {
       MESSAGE("  Parameter       " 
	       << Service->ServiceinParameter[i].Parametername);
       MESSAGE("  Type          : "
	       << Service->ServiceinParameter[i].Parametertype);
     }
   
   MESSAGE("Out Parameter(s):");
   n = Service->ServiceoutParameter.length();
   for (i = 0; i<n; i++)
     {
       MESSAGE("  Parameter       " 
	       << Service->ServiceoutParameter[i].Parametername);
       MESSAGE("  Type          : "
	       << Service->ServiceoutParameter[i].Parametertype);
     }
   
   MESSAGE("In DataStreamParameter(s):");
   n = Service->ServiceinDataStreamParameter.length();
   for (i = 0; i<n; i++)
     {
       MESSAGE("  Parameter " 
	       << Service->ServiceinDataStreamParameter[i].Parametername);
       MESSAGE("  Type          : "
	       << Service->ServiceinDataStreamParameter[i].Parametertype);
       MESSAGE("  Dependency    : "
	       << Service->ServiceinDataStreamParameter[i].Parametertype);
     }
   
   MESSAGE("Out DataStreamParameter(s):");
   n = Service->ServiceoutDataStreamParameter.length();
   for (i = 0; i<n; i++)
     {
       MESSAGE("  Parameter " 
	       << Service->ServiceoutDataStreamParameter[i].Parametername);
       MESSAGE("  Type          : "
	       << Service->ServiceoutDataStreamParameter[i].Parametertype);
       MESSAGE("  Dependency    : "
	       << Service->ServiceoutDataStreamParameter[i].Parametertype);
     }
   

}



