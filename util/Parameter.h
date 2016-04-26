
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Renderer From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once

#endif
#ifndef Parameter_H
#define Parameter_H

#include "pbr.h"
#include <map>

using namespace std ;

class Parameter 
{
public :
	Parameter () ;
	~Parameter () ;

	void addFloat ( const char* name , float value ) ;
	float getFloat ( const char* name , float value ) ;

private :
	std::map < const char* , float > floatMap ;
} ;

#endif