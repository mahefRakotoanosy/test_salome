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
//  File   : SALOMEDSImpl_AttributeIOR.hxx
//  Author : Sergey RUIN
//  Module : SALOME

#ifndef _SALOMEDSImpl_AttributeComment_HeaderFile
#define _SALOMEDSImpl_AttributeComment_HeaderFile

#include <Standard_DefineHandle.hxx>
#include <TDF_Attribute.hxx>
#include <TCollection_AsciiString.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TDF_Label.hxx> 
#include <Standard_GUID.hxx> 
#include "SALOMEDSImpl_GenericAttribute.hxx"

class Handle(TDF_Attribute);
class Handle(TDF_RelocationTable);

DEFINE_STANDARD_HANDLE( SALOMEDSImpl_AttributeComment, SALOMEDSImpl_GenericAttribute )

class SALOMEDSImpl_AttributeComment : public SALOMEDSImpl_GenericAttribute 
{
private:

 TCollection_ExtendedString myString;

public:

Standard_EXPORT static const Standard_GUID& GetID() ;

Standard_EXPORT  SALOMEDSImpl_AttributeComment() :SALOMEDSImpl_GenericAttribute("AttributeComment") {}

Standard_EXPORT  static Handle(SALOMEDSImpl_AttributeComment) Set(const TDF_Label& L, const TCollection_ExtendedString& Val); 
Standard_EXPORT  void SetValue (const TCollection_ExtendedString& S);
Standard_EXPORT  TCollection_ExtendedString Value() const { return myString; }

Standard_EXPORT  virtual TCollection_AsciiString Save() { return myString; }
Standard_EXPORT  virtual void Load(const TCollection_AsciiString& theValue) { myString = theValue; }

Standard_EXPORT  const Standard_GUID& ID() const;
Standard_EXPORT  void Restore(const Handle(TDF_Attribute)& with) ;
Standard_EXPORT  Handle_TDF_Attribute NewEmpty() const;
Standard_EXPORT  void Paste(const Handle(TDF_Attribute)& into,const Handle(TDF_RelocationTable)& RT) const;

Standard_EXPORT ~SALOMEDSImpl_AttributeComment() {}

public:
  DEFINE_STANDARD_RTTI( SALOMEDSImpl_AttributeComment )
};

#endif
