// Eric Fayolle - EDF R&D
// Modified by : $LastChangedBy$
// Date        : $LastChangedDate: 2007-02-28 15:26:32 +0100 (mer, 28 fév 2007) $
// Id          : $Id$

#ifndef _CALCIUM_LOGICAL_PORT_USES_HXX_
#define _CALCIUM_LOGICAL_PORT_USES_HXX_

#include "Calcium_Ports.hh"
#include "CalciumGenericUsesPort.hxx"

extern char _repository_Calcium_Logical_Port_name[];

class calcium_logical_port_uses :
  public virtual CalciumGenericUsesPort< seq_u_manipulation<Ports::Calcium_Ports::seq_boolean,
						     CORBA::Boolean >, 
				  Ports::Calcium_Ports::Calcium_Logical_Port, 
				  _repository_Calcium_Logical_Port_name 
				  >
{
  public :

  virtual ~calcium_logical_port_uses();

};

#endif
