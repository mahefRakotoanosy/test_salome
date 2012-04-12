// Copyright (C) 2007-2012  CEA/DEN, EDF R&D, OPEN CASCADE
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

/*!
 * Check all methods of SALOMEDS_AttributePixMap
 * Use code of SALOMEDS_AttributePixMap.cxx
 */
void SALOMEDSTest::testAttributePixMap()
{
  //Create or find the Study manager
  _PTR(StudyManager) sm ( new SALOMEDS_StudyManager(_sm) );

  CPPUNIT_ASSERT(sm);

  //Create a new study
  _PTR(Study) study = sm->NewStudy("Test");

  CPPUNIT_ASSERT(study);

  //Create Study Builder
  _PTR(StudyBuilder) studyBuilder = study->NewBuilder();

  CPPUNIT_ASSERT(studyBuilder);

  //Create a SObject with entry 0:1:1
  _PTR(SObject) so = study->CreateObjectID("0:1:1");

  CPPUNIT_ASSERT(so);

  //Create an attribute AttributePixMap
  _PTR(AttributePixMap) _attr = studyBuilder->FindOrCreateAttribute(so, "AttributePixMap");

  //Check the attribute creation
  CPPUNIT_ASSERT(_attr);

  //Check method HasPixMap
  CPPUNIT_ASSERT(!_attr->HasPixMap());

  //Check method SetPixMap
  std::string pixmap = "something";
  _attr->SetPixMap(pixmap);

  CPPUNIT_ASSERT(_attr->HasPixMap());

  //Check method GetPixMap
  CPPUNIT_ASSERT(_attr->GetPixMap() == pixmap);

  //Check empty PixMap assigning and retreival
  _attr->SetPixMap("");
  CPPUNIT_ASSERT(_attr->GetPixMap() == "");


  sm->Close(study);
}



