 
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "parameter.h" 

Parameter::Parameter () {}
Parameter::~Parameter () {}

void Parameter::addFloat ( const char* name , float value ) 
{
	std::map < const char* , float >::iterator it ;
	it = this->floatMap.find ( name ) ;
	if ( it != this->floatMap.end() ) {
		this->floatMap.erase ( name ) ;
	}
	this->floatMap[name] = value ;
}

float Parameter::getFloat ( const char* name , float value ) 
{
	float ret = value ;
	std::map < const char* , float >::iterator it ;
	it = this->floatMap.find ( name ) ;
	if ( it != this->floatMap.end() ) {
		ret = it->second ;
	}
	return ret ;
}