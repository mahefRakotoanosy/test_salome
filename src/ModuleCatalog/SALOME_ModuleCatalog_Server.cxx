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
//  File   : SALOME_ModuleCatalog_Server.cxx
//  Module : SALOME
/* $Header$ */

#include <iostream>
#include "SALOME_NamingService.hxx"
#include "SALOME_ModuleCatalog_impl.hxx"
#include "utilities.h"
#include "SALOMETraceCollector.hxx"
#include "Utils_SINGLETON.hxx"

#ifdef CHECKTIME
#include <Utils_Timer.hxx>
#endif
using namespace std;

int main(int argc,char **argv)
{
  // initialize the ORB
  CORBA::ORB_ptr orb = CORBA::ORB_init (argc, argv);
  SALOMETraceCollector *myThreadTrace = SALOMETraceCollector::instance(orb);
  try 
    {
      CosNaming::NamingContext_var _rootContext, catalogContext;

      // initialize POA
      //
      long TIMESleep = 500000000;
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
      int MODULE_CATALOG=0;
      const char * Env = getenv("USE_LOGGER");
      int EnvL =0;
      if ((Env!=NULL) && (strlen(Env)))
	EnvL=1;
      CosNaming::Name name;
      name.length(1);
      name[0].id=CORBA::string_dup("Logger");    
      PortableServer::POAManager_var mgr; 
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
		mgr = poa->the_POAManager();
	      if(!CORBA::is_nil(orb)) 
		theObj = orb->resolve_initial_references("NameService"); 
	    }
	  catch( CORBA::SystemException& )
	    {
	      INFOS( "Module Catalog Server: CORBA::SystemException: Unable to contact the Naming Service" );
	    }
	  if (!CORBA::is_nil(theObj))
	    {
	      inc = CosNaming::NamingContext::_narrow(theObj);
	      if(!CORBA::is_nil(inc))
		{
		  INFOS( "Module Catalog Server: Naming Service was found" );
		  if(EnvL==1)
		    {
		      CORBA::ORB_var orb1 = CORBA::ORB_init(argc,argv) ;
		      SALOME_NamingService &NS = *SINGLETON_<SALOME_NamingService>::Instance() ;
		      NS.init_orb( orb1 ) ;
		      for(int j=1; j<=NumberOfTries; j++)
			{
			  if (j!=1) 
			    a=nanosleep(&ts_req, &ts_rem);
			  try{
			    object = inc->resolve(name);}
			  catch(CosNaming::NamingContext::NotFound)
			    {
			      INFOS( "Logger Server wasn't found" );
			    }
			  catch(...)
			    {
			      INFOS( "Module Catalog Server: Unknown exception" ) ;
			    }
			  if (!CORBA::is_nil(object))
			    {
			      INFOS( "Module Catalog Server: Logger Server was found" );
			      MODULE_CATALOG=1;
			      break;
			    }
			}
		    }
		}
	    }
	  if ((MODULE_CATALOG==1)||((EnvL==0)&&(!CORBA::is_nil(inc))))
	    break;
	}
  
      // Active catalog

      SALOME_ModuleCatalogImpl Catalogue_i(argc, argv, orb);
      poa->activate_object (&Catalogue_i);

      mgr->activate();

  
      CORBA::Object_ptr myCata = Catalogue_i._this();

      // initialise Naming Service
      SALOME_NamingService *_NS;
      _NS = new SALOME_NamingService(orb);
      // register Catalog in Naming Service
      _NS->Register(myCata ,"/Kernel/ModulCatalog");

      MESSAGE("Running CatalogServer.");

#ifdef CHECKTIME
      Utils_Timer timer;
      timer.Start();
      timer.Stop();
      MESSAGE("SALOME_Registry_Server.cxx - orb->run()");
      timer.ShowAbsolute();
#endif
      orb->run();
 
      mgr->deactivate(true,true);
      poa->destroy(1,1);

    }
  catch(CORBA::SystemException&) {
    INFOS("Caught CORBA::SystemException.")
      }
  catch(CORBA::Exception&) {
    INFOS("Caught CORBA::Exception.")
      }

  delete myThreadTrace;
  return 0;
}
