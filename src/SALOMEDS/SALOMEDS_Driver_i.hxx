// Copyright (C) 2007-2011  CEA/DEN, EDF R&D, OPEN CASCADE
//
// Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
// CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//

#ifndef __SALOMEDS_DRIVER_I_H__
#define __SALOMEDS_DRIVER_I_H__

#include <SALOMEconfig.h>

#include <omniORB4/CORBA.h>
#include "SALOMEDSImpl_Driver.hxx"
#include "SALOMEDSImpl_SComponent.hxx"
#include "SALOMEDSImpl_SObject.hxx"

#include CORBA_SERVER_HEADER(SALOMEDS) 
#include CORBA_SERVER_HEADER(SALOME_Component)

class Standard_EXPORT SALOMEDS_Driver_i :  public virtual SALOMEDSImpl_Driver 
{
protected:
  SALOMEDS::Driver_var _driver;
  CORBA::ORB_var _orb;

public:

  SALOMEDS_Driver_i(SALOMEDS::Driver_ptr theDriver, CORBA::ORB_ptr theORB) 
    {
      _driver = SALOMEDS::Driver::_duplicate(theDriver);
      _orb = CORBA::ORB::_duplicate(theORB);        
    }

  ~SALOMEDS_Driver_i();

  virtual std::string GetIOR() 
    {
      CORBA::String_var ior = _orb->object_to_string(_driver);
      return std::string(ior);
    }

  virtual SALOMEDSImpl_TMPFile* Save(const SALOMEDSImpl_SComponent& theComponent,
                                     const std::string& theURL,
                                     long& theStreamLength,
                                     bool isMultiFile);

  virtual SALOMEDSImpl_TMPFile* SaveASCII(const SALOMEDSImpl_SComponent& theComponent,
                                          const std::string& theURL,
                                          long& theStreamLength,
                                          bool isMultiFile);
  
  virtual bool Load(const SALOMEDSImpl_SComponent& theComponent,
                    const unsigned char* theStream,
                    const long theStreamLength,
                    const std::string& theURL,
                    bool isMultiFile);

  virtual bool LoadASCII(const SALOMEDSImpl_SComponent& theComponent,
                         const unsigned char* theStream,
                         const long theStreamLength,
                         const std::string& theURL,
                         bool isMultiFile);

  virtual void Close(const SALOMEDSImpl_SComponent& theComponent);
 
  virtual std::string ComponentDataType() 
    {
      CORBA::String_var ior = _driver->ComponentDataType();
      return std::string(ior);
    }


  virtual std::string IORToLocalPersistentID(const SALOMEDSImpl_SObject& theSObject,
                                             const std::string& IORString,
                                             bool isMultiFile,
                                             bool isASCII);

  virtual std::string LocalPersistentIDToIOR(const SALOMEDSImpl_SObject& theSObject,
                                             const std::string& aLocalPersistentID,
                                             bool isMultiFile,
                                             bool isASCII);

  virtual bool CanCopy(const SALOMEDSImpl_SObject& theObject);

  virtual SALOMEDSImpl_TMPFile* CopyFrom(const SALOMEDSImpl_SObject& theObject, 
                                         int& theObjectID,
                                         long& theStreamLength);
  
  virtual bool CanPaste(const std::string& theComponentName, int theObjectID);

  virtual std::string PasteInto(const unsigned char* theStream,
                                const long theStreamLength,
                                int theObjectID,
                                const SALOMEDSImpl_SObject& theObject);

  virtual SALOMEDSImpl_TMPFile* DumpPython(SALOMEDSImpl_Study* theStudy, 
                                           bool isPublished, 
                                           bool isMultiFile,
                                           bool& isValidScript,
                                           long& theStreamLength);
};

#include "SALOME_NamingService.hxx"
#include "SALOME_LifeCycleCORBA.hxx"

class SALOMEDS_DriverFactory_i : public virtual SALOMEDSImpl_DriverFactory 
{
protected:  
  CORBA::ORB_var        _orb;
  SALOME_NamingService* _name_service;

public:
  
  SALOMEDS_DriverFactory_i(CORBA::ORB_ptr theORB) 
    {
      _orb = CORBA::ORB::_duplicate(theORB);
      _name_service = new SALOME_NamingService(_orb);
    }


  ~SALOMEDS_DriverFactory_i() 
  {
    delete _name_service;
  }
   
  virtual SALOMEDSImpl_Driver* GetDriverByType(const std::string& theComponentType);

  virtual SALOMEDSImpl_Driver* GetDriverByIOR(const std::string& theIOR);
};

#endif 
