//  SALOME Utils : general SALOME's definitions and tools
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
//  File   : utilities.h
//  Author : Antoine YESSAYAN, Paul RASCLE, EDF
//  Module : SALOME
//  $Header$

/* ---  Definition macros file to print informations if _DEBUG_ is defined --- */

# ifndef UTILITIES_H
# define UTILITIES_H

# include <stdlib.h>
# include <iostream>



//VRV: T2.4 - replacement macro for using special CORBA server
#include "SALOME_Trace.hxx"
//VRV: T2.4 - replacement macro for using special CORBA server

/* ---  INFOS is always defined (without _DEBUG_): to be used for warnings, with release version --- */

//VRV: T2.4 - replacement of these macros for using special CORBA server

#define INFOS(msg) { GLogger.putMessage(GLogger << __FILE__<< " [" << __LINE__ << "] : " << msg<< endl << ends ); }
#define PYSCRIPT(msg) { GLogger.putMessage(GLogger<<"---PYSCRIPT--- "<<msg<<endl<<ends ); }

//# define HEREWEARE {cout<<flush ; cerr << __FILE__ << " [" << __LINE__ << "] : " << flush ;}
//# define INFOS(chain) {HEREWEARE ; cerr << chain << endl ;}
//# define PYSCRIPT(chain) {cout<<flush ; cerr << "---PYSCRIPT--- " << chain << endl ;}

//VRV: T2.4 - replacement of these macros for using special CORBA server


/* --- To print date and time of compilation of current source on stdout --- */

# if defined ( __GNUC__ )
# define COMPILER		"g++" 
# elif defined ( __sun )
# define COMPILER		"CC" 
# elif defined ( __KCC )
# define COMPILER		"KCC" 
# elif defined ( __PGI )
# define COMPILER		"pgCC" 
# else
# define COMPILER		"undefined" 
# endif

# ifdef INFOS_COMPILATION
# error INFOS_COMPILATION already defined
# endif

//VRV: T2.4 - replacement macro for using special CORBA server
#define INFOS_COMPILATION { \
			      GLogger.putMessage(\
						 GLogger << __FILE__ << " [" << __LINE__ << "] : "\
						 << "COMPILED with " << COMPILER \
						 << ", " << __DATE__ \
						 << " at " << __TIME__ << endl << endl <<endl<<ends); }
/* # define INFOS_COMPILATION	{\ */
/* 					cerr << flush;\ */
/* 					cout << __FILE__ ;\ */
/* 					cout << " [" << __LINE__ << "] : " ;\ */
/* 					cout << "COMPILED with " << COMPILER ;\ */
/* 					cout << ", " << __DATE__ ; \ */
/* 					cout << " at " << __TIME__ << endl ;\ */
/* 					cout << "\n\n" ;\ */
/* 					cout << flush ;\ */
/* 				} */
//VRV: T2.4 - replacement macro for using special CORBA server

# ifdef _DEBUG_

/* --- the following MACROS are useful at debug time --- */

//VRV: T2.4 - replacement of these macros for using special CORBA server

#define MYTRACE GLogger << "- Trace " << __FILE__ << " [" << __LINE__ << "] : " 

#define MESSAGE(msg) { GLogger.putMessage( MYTRACE <<msg<<endl<<ends); }
#define SCRUTE(var) { GLogger.putMessage( MYTRACE << #var << "=" << var <<endl<<ends); }

#define REPERE GLogger << "   --------------" << endl 
#define BEGIN_OF(msg) {REPERE ; MYTRACE << "Begin of: " << msg << endl ; REPERE ; GLogger.putMessage(GLogger<<ends); } 
#define END_OF(msg) {REPERE ; MYTRACE << "Normal end of: " << msg << endl ; REPERE ; GLogger.putMessage(GLogger<<ends); } 

# define HERE {cout<<flush ; cerr << "- Trace " << __FILE__ << " [" << __LINE__ << "] : " << flush ;}

//VRV: T2.4 - replacement of these macros for using special CORBA server

# define INTERRUPTION(code) {HERE ; cerr << "INTERRUPTION return code= " << code << endl ; exit(code) ;}

# ifndef ASSERT
# define ASSERT(condition) if (!(condition)){ HERE ; cerr << "CONDITION " << #condition << " NOT VERIFIED"<< endl ; INTERRUPTION(1) ;}
# endif /* ASSERT */







# else /* ifdef _DEBUG_*/

#define HERE 
#define SCRUTE(var) {}
#define MESSAGE(msg) {}
#define REPERE
#define BEGIN_OF(msg) {}
#define END_OF(msg) {}

# define INTERRUPTION(code) {}

# ifndef ASSERT
# define ASSERT(condition) {}
# endif /* ASSERT */


# endif /* ifdef _DEBUG_*/

# endif /* ifndef UTILITIES_H */
