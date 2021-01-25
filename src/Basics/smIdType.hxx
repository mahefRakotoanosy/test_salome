// Copyright (C) 2007-2020  CEA/DEN, EDF R&D, OPEN CASCADE
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
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

//  SALOME Basics : general SALOME definitions and tools (C++ part - no CORBA)
//  File   : smIdType.hxx

#ifndef _SMIDTYPE_HXX_
#define _SMIDTYPE_HXX_

#include <cinttypes>

#ifndef SALOME_USE_64BIT_IDS
typedef std::int32_t smIdType;
#else
typedef std::int64_t smIdType;
#endif

#endif //_SMIDTYPE_HXX_
