//  SALOME NOTIFICATION_SWIG : wrapping of Notification sevices in order to be available in Python
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
//  File   : NOTIFICATION_Swig.hxx
//  Author : Francis KLOSS
//  Module : SALOME

#include "NOTIFICATION.hxx"
#include "SALOME_NOTIFICATION_SWIG.hxx"

class NOTIFICATION_SWIG_EXPORT NOTIFICATION_Supplier_Swig {
  public:
    NOTIFICATION_Supplier_Swig(const char* instanceName, bool notif);
    ~NOTIFICATION_Supplier_Swig();
    void Send(const char* graph, const char* node, const char* type, const char* message);

  private:
    NOTIFICATION_Supplier* _supplier;
};

class NOTIFICATION_SWIG_EXPORT NOTIFICATION_Consumer_Swig {
  public:
    NOTIFICATION_Consumer_Swig();
    ~NOTIFICATION_Consumer_Swig();
    bool Receive(char** graph, char** node, char** type, char** message, char** sender, long* counter, char** date, long* stamp);

  private:
    NOTIFICATION_Consumer* _consumer;
};
