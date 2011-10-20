// Copyright (C) 2007-2011  CEA/DEN, EDF R&D, OPEN CASCADE
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
// Author: Guillaume Boulant (EDF/R&D) 

#include "SALOME_KernelServices.hxx"
#include "Basics_Utils.hxx"

#include <SALOMEconfig.h>
#include CORBA_CLIENT_HEADER(SALOME_TestComponent)

void TEST_corba() {
  CORBA::ORB_var orb = KERNEL::getORB();
  SALOME_NamingService *  ns  = KERNEL::getNamingService();
  SALOME_LifeCycleCORBA * lcc = KERNEL::getLifeCycleCORBA();
}

void TEST_getLifeCycleCORBA() {
  Engines::EngineComponent_var component =
    KERNEL::getLifeCycleCORBA()->FindOrLoad_Component( "FactoryServer","SalomeTestComponent" );
  
  Engines::TestComponent_var engine = Engines::TestComponent::_narrow(component);
  STDLOG(engine->Coucou(123.));
}

// TODO:
// - complete the coverture of the KernelService interface
// - provide use case for the StudyEditor

int main (int argc, char * argv[]) {
  TEST_getLifeCycleCORBA();
  return 0;
}
