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
//  File   : SALOMEDS_AttributeSelectable.hxx
//  Author : Sergey RUIN
//  Module : SALOME

#ifndef SALOMEDS_AttributeSelectable_HeaderFile
#define SALOMEDS_AttributeSelectable_HeaderFile

#include "SALOMEDSClient_AttributeSelectable.hxx"
#include "SALOMEDS_GenericAttribute.hxx"
#include "SALOMEDSImpl_AttributeSelectable.hxx"

// IDL headers
#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(SALOMEDS)
#include CORBA_SERVER_HEADER(SALOMEDS_Attributes)

class SALOMEDS_AttributeSelectable: public SALOMEDS_GenericAttribute, public SALOMEDSClient_AttributeSelectable
{
public:  
  SALOMEDS_AttributeSelectable(const Handle(SALOMEDSImpl_AttributeSelectable)& theAttr);
  SALOMEDS_AttributeSelectable(SALOMEDS::AttributeSelectable_ptr theAttr);
  ~SALOMEDS_AttributeSelectable();

  virtual bool IsSelectable();
  virtual void SetSelectable(bool value);
};

#endif
