//  SALOME SALOMEDS : data structure of SALOME and sources of Salome data server 
//
//  Copyright (C) 2003  CEA/DEN, EDF R&D
//
//
//
//  File   : SALOMEDS_TableOfRealAttribute.ixx
//  Author : Michael Ponikarov
//  Module : SALOME
//  $Header$

#include <SALOMEDS_TableOfRealAttribute.jxx>

#ifndef _Standard_TypeMismatch_HeaderFile
#include <Standard_TypeMismatch.hxx>
#endif

SALOMEDS_TableOfRealAttribute::~SALOMEDS_TableOfRealAttribute() {}
 


Standard_EXPORT Handle_Standard_Type& SALOMEDS_TableOfRealAttribute_Type_()
{

    static Handle_Standard_Type aType1 = STANDARD_TYPE(TDF_Attribute);
  if ( aType1.IsNull()) aType1 = STANDARD_TYPE(TDF_Attribute);
  static Handle_Standard_Type aType2 = STANDARD_TYPE(MMgt_TShared);
  if ( aType2.IsNull()) aType2 = STANDARD_TYPE(MMgt_TShared);
  static Handle_Standard_Type aType3 = STANDARD_TYPE(Standard_Transient);
  if ( aType3.IsNull()) aType3 = STANDARD_TYPE(Standard_Transient);
 

  static Handle_Standard_Transient _Ancestors[]= {aType1,aType2,aType3,NULL};
  static Handle_Standard_Type _aType = new Standard_Type("SALOMEDS_TableOfRealAttribute",
			                                 sizeof(SALOMEDS_TableOfRealAttribute),
			                                 1,
			                                 (Standard_Address)_Ancestors,
			                                 (Standard_Address)NULL);

  return _aType;
}


// DownCast method
//   allow safe downcasting
//
const Handle(SALOMEDS_TableOfRealAttribute) Handle(SALOMEDS_TableOfRealAttribute)::DownCast(const Handle(Standard_Transient)& AnObject) 
{
  Handle(SALOMEDS_TableOfRealAttribute) _anOtherObject;

  if (!AnObject.IsNull()) {
     if (AnObject->IsKind(STANDARD_TYPE(SALOMEDS_TableOfRealAttribute))) {
       _anOtherObject = Handle(SALOMEDS_TableOfRealAttribute)((Handle(SALOMEDS_TableOfRealAttribute)&)AnObject);
     }
  }

  return _anOtherObject ;
}
const Handle(Standard_Type)& SALOMEDS_TableOfRealAttribute::DynamicType() const 
{ 
  return STANDARD_TYPE(SALOMEDS_TableOfRealAttribute) ; 
}
Standard_Boolean SALOMEDS_TableOfRealAttribute::IsKind(const Handle(Standard_Type)& AType) const 
{ 
  return (STANDARD_TYPE(SALOMEDS_TableOfRealAttribute) == AType || TDF_Attribute::IsKind(AType)); 
}
Handle_SALOMEDS_TableOfRealAttribute::~Handle_SALOMEDS_TableOfRealAttribute() {}

