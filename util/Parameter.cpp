 
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "parameter.h" 

Parameter::Parameter () {}
Parameter::~Parameter () {}

void Parameter::addFloat ( const char* name , float value ) {
	std::map < const char* , float >::iterator it ;
	it = this->floatMap.find ( name ) ;
	if ( it != this->floatMap.end() ) {
		this->floatMap.erase ( name ) ;
	}
	this->floatMap[name] = value ;
}

float Parameter::getFloat ( const char* name , float value ) {
	float ret = value ;
	std::map < const char* , float >::iterator it ;
	it = this->floatMap.find ( name ) ;
	if ( it != this->floatMap.end() ) {
		ret = it->second ;
	}
	return ret ;
}

void Parameter::addPoint ( const char* name , const Point& point )  {
	std::map < const char* , Point* >::iterator it ;
	it = this->pointMap.find ( name ) ;
	if ( it != this->pointMap.end() ) {
		Point* point = it->second ;
		delete point ;
		this->pointMap.erase ( name ) ;		
	}
	Point* np = new Point() ;
	*np = point ;
	this->pointMap[name] = np ;	
}

Point* Parameter::getPoint ( const char* name , const Point& point )  {

	Point* ret = (Point* )&point ;
	std::map < const char* , Point* >::iterator it ;
	it = this->pointMap.find ( name ) ;
	if ( it != this->pointMap.end() ) {
		ret = it->second ;
	}
	return ret ;

}