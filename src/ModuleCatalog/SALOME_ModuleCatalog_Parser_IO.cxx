
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
//  File   : SALOME_ModuleCatalog_Handler.cxx
//  Author : Estelle Deville
//  Module : SALOME
//  $Header$

#include "SALOME_ModuleCatalog_Parser_IO.hxx"
#include <string>

std::ostream & operator<< (std::ostream & f, const ParserServParam & P)
{
  f << "          name :       " << P.parserParamName << std::endl;
  f << "          type :       " << P.parserParamType << std::endl;
  return f;
}

std::ostream & operator<< (std::ostream & f, 
			   const ParserServDataStreamParam & P)
{
  f << "          name :       " << P.parserParamName << std::endl;
  f << "          type :       " << P.parserParamType << std::endl;
  f << "          dependency : " << P.parserParamDependency << std::endl;
  return f;
}

std::ostream & operator<< (std::ostream & f, 
			   const ParserService & S)
{
  int i, n;
  f << "      name :       " << S.parserServiceName << std::endl;
  f << "      default :    " << (S.parserServiceByDefault ? "yes" : "no") 
    << std::endl;

  n = S.parserServiceInParameter.size();
  f << "      in parameters : " << n << std::endl;
  for (i=0; i<n; i++)
    f << S.parserServiceInParameter[i] << std::endl;

  n = S.parserServiceInDataStreamParameter.size();
  f << "      in DataStream parameters : " << n << std::endl;
  for (i=0; i<n; i++)
    f << S.parserServiceInDataStreamParameter[i] << std::endl;

  n = S.parserServiceOutParameter.size();
  f << "      out parameters : " << n << std::endl;
  for (i=0; i<n; i++)
    f << S.parserServiceOutParameter[i] << std::endl;

  n = S.parserServiceOutDataStreamParameter.size();
  f << "      out DataStream parameters : " << n << std::endl;
  for (i=0; i<n; i++)
    f << S.parserServiceOutDataStreamParameter[i] << std::endl;

  return f;
}

std::ostream & operator<< (std::ostream & f, 
			   const ParserDefInterface & I)
{
  int j, n;
  f << "    name :       " << I.parserInterfaceName << std::endl;

  n = I.parserInterfaceServiceList.size();
  f << "    services : " << n << std::endl;
  for (j=0; j<n; j++)
    f << I.parserInterfaceServiceList[j] << std::endl;

  return f;
}

std::ostream & operator<< (std::ostream & f, 
			   const  ParserComponentType & T)
{
  std::string s;
  switch (T) {
  case GEOM :   s = "GEOM"; break;
  case MESH :   s = "MESH"; break;
  case Med  :   s = "Med"; break;
  case SOLVER : s = "SOLVER"; break;
  case DATA :   s = "DATA"; break;
  case VISU :   s = "VISU"; break;
  case SUPERV : s = "SUPERV"; break;
  default :     s = "OTHER"; break;
  }
  f << s << std::endl;
  return f;
}

std::ostream & operator<< (std::ostream & f, 
			   const ParserComponent & C)
{
  int j, n;
  f << "    name :       " << C.parserComponentName << std::endl;
  f << "    user name :  " << C.parserComponentUsername << std::endl;
  f << "    type :       " << C.parserComponentType << std::endl;
  f << "    multistudy : " << (C.parserComponentMultistudy ? "yes" : "no")
    << std::endl;
  f << "    icon :       " << C.parserComponentIcon << std::endl;
  f << "    constraint : " << C.parserConstraint << std::endl;

  n = C.parserListInterface.size();
  f << "    interfaces : " << n << std::endl;
  for (j=0; j<n; j++)
    f << C.parserListInterface[j] << std::endl;

  return f;
}


