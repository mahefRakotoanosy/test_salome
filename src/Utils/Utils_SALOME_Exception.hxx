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
//  File   : Utils_SALOME_Exception.hxx
//  Author : Antoine YESSAYAN, EDF
//  Module : SALOME
//  $Header$

#if !defined( __Utils_SALOME_Exception_hxx__ )
#define __Utils_SALOME_Exception_hxx__

# include <exception>
# include <iostream>

# define LOCALIZED(message) #message , __FILE__ , __LINE__

#if defined UTILS_EXPORTS
#if defined WIN32
#define UTILS_EXPORT __declspec( dllexport )
#else
#define UTILS_EXPORT
#endif
#else
#if defined WNT
#define UTILS_EXPORT __declspec( dllimport )
#else
#define UTILS_EXPORT
#endif
#endif

class UTILS_EXPORT SALOME_Exception : public std::exception
{

private :
	SALOME_Exception( void );

protected :
	const char* _text ;	// non constant pointer but read only char variable

public :
	SALOME_Exception( const char *text, const char *fileName=0, const unsigned int lineNumber=0 );
	SALOME_Exception( const SALOME_Exception &ex );
	~SALOME_Exception() throw ();
	friend std::ostream & operator<<( std::ostream &os , const SALOME_Exception &ex );
	virtual const char *what( void ) const throw () ;
} ;


#endif		/* #if !defined( __Utils_SALOME_Exception_hxx__ ) */
