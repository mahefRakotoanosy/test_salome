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
//  File   : SALOMEDSImpl_AttributeFileType.cxx
//  Author : Sergey RUIN
//  Module : SALOME

#include "SALOMEDSImpl_AttributeFileType.hxx"

using namespace std;

IMPLEMENT_STANDARD_HANDLE( SALOMEDSImpl_AttributeFileType, SALOMEDSImpl_GenericAttribute )
IMPLEMENT_STANDARD_RTTIEXT( SALOMEDSImpl_AttributeFileType, SALOMEDSImpl_GenericAttribute )

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================

const Standard_GUID& SALOMEDSImpl_AttributeFileType::GetID () 
{
  static Standard_GUID SALOMEDSImpl_AttributeFileTypeID ("0181B525-3F15-4ab2-9DE3-5E2F54B5F340");
  return SALOMEDSImpl_AttributeFileTypeID;
}



//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

Handle(SALOMEDSImpl_AttributeFileType) SALOMEDSImpl_AttributeFileType::Set (const TDF_Label& L,
									    const TCollection_ExtendedString& S) 
{

  Handle(SALOMEDSImpl_AttributeFileType) A;
  if (!L.FindAttribute(SALOMEDSImpl_AttributeFileType::GetID(),A)) {
    A = new  SALOMEDSImpl_AttributeFileType(); 
    L.AddAttribute(A);
  }
  
  A->SetValue (S); 
  return A;
}


//=======================================================================
//function : constructor
//purpose  : 
//=======================================================================
SALOMEDSImpl_AttributeFileType::SALOMEDSImpl_AttributeFileType()
:SALOMEDSImpl_GenericAttribute("AttributeFileType")
{
}

//=======================================================================
//function : SetValue
//purpose  :
//=======================================================================
void SALOMEDSImpl_AttributeFileType::SetValue (const TCollection_ExtendedString& S)
{
  CheckLocked();

  if(myString == S) return;

  Backup();

  myString = S;

  SetModifyFlag(); //SRN: Mark the study as being modified, so it could be saved 
}

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& SALOMEDSImpl_AttributeFileType::ID () const { return GetID(); }


//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) SALOMEDSImpl_AttributeFileType::NewEmpty () const
{  
  return new SALOMEDSImpl_AttributeFileType(); 
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void SALOMEDSImpl_AttributeFileType::Restore(const Handle(TDF_Attribute)& with) 
{
  myString = Handle(SALOMEDSImpl_AttributeFileType)::DownCast (with)->Value ();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void SALOMEDSImpl_AttributeFileType::Paste (const Handle(TDF_Attribute)& into,
					    const Handle(TDF_RelocationTable)& RT) const
{
  Handle(SALOMEDSImpl_AttributeFileType)::DownCast (into)->SetValue (myString);
}

