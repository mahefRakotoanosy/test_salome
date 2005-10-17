//  Copyright (C) 2004  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
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
//  File   : BaseTraceCollector.hxx
//  Author : Paul RASCLE (EDF)
//  Module : KERNEL
//  $Header$

#ifndef _BASETRACECOLLECTOR_HXX_
#define _BASETRACECOLLECTOR_HXX_

#include <pthread.h>
#include <semaphore.h>


#if defined SALOMELOCALTRACE_EXPORTS
#if defined WIN32
#define SALOMELOCALTRACE_EXPORT __declspec( dllexport )
#else
#define SALOMELOCALTRACE_EXPORT
#endif
#else
#if defined WNT
#define SALOMELOCALTRACE_EXPORT __declspec( dllimport )
#else
#define SALOMELOCALTRACE_EXPORT
#endif
#endif

//! See derived Classes in SALOMELocalTrace for usage without CORBA,
//! see derived Classes in SALOMETraceCollector for usage with CORBA.

class SALOMELOCALTRACE_EXPORT BaseTraceCollector
{
 public:
  virtual ~BaseTraceCollector();

 protected:
  BaseTraceCollector();

  static int _threadToClose;
  static BaseTraceCollector* _singleton;
  static pthread_mutex_t _singletonMutex;
  static pthread_t* _threadId;
  static sem_t _sem;
};

#endif
