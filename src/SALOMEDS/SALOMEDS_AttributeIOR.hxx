// Copyright (C) 2005  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
// CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either 
// version 2.1 of the License.
// 
// This library is distributed in the hope that it will be useful 
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public  
// License along with this library; if not, write to the Free Software 
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/
//
//  File   : SALOMEDS_AttributeIOR.hxx
//  Author : Sergey RUIN
//  Module : SALOME

#ifndef SALOMEDS_AttributeIOR_HeaderFile
#define SALOMEDS_AttributeIOR_HeaderFile

#include "SALOMEDSClient_AttributeIOR.hxx"
#include "SALOMEDS_GenericAttribute.hxx"
#include "SALOMEDSImpl_AttributeIOR.hxx"

// IDL headers
#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(SALOMEDS)
#include CORBA_SERVER_HEADER(SALOMEDS_Attributes)

class SALOMEDS_AttributeIOR: public SALOMEDS_GenericAttribute, public SALOMEDSClient_AttributeIOR
{
public:  
  SALOMEDS_AttributeIOR(const Handle(SALOMEDSImpl_AttributeIOR)& theAttr);
  SALOMEDS_AttributeIOR(SALOMEDS::AttributeIOR_ptr theAttr);
  ~SALOMEDS_AttributeIOR();

  virtual std::string Value();
  virtual void SetValue(const std::string& value);
};

#endif
