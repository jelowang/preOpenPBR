
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once

#endif
#ifndef Parameter_H
#define Parameter_H

#include "pbr.h"
#include "point.h"
#include "vector.h"

class Parameter 
{
public :
	Parameter () ;
	~Parameter () ;

	void addFloat ( const char* name , float value ) ;
	float getFloat ( const char* name , float value ) ;

	void addPoint ( const char* name , const Point& point ) ;
	Point* getPoint ( const char* name , const Point& point ) ;

private :
	std::map < const char* , float > floatMap ;
	std::map < const char* , Point* > pointMap ;
	std::map < const char* , Vector* > vectorMap ;
} ;

#endif