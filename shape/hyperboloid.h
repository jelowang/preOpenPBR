
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once

#endif
#ifndef Hyperboloid_H
#define Hyperboloid_H

#include "shape.h"

class Hyperboloid : public Shape
{
public :
	Hyperboloid ( const Transform* o2w , const Transform* w2o , bool ro , const Point& point1 , const Point& point2 , float tm ) ;
	~Hyperboloid () ;
	static Hyperboloid* Create ( const Transform* o2w , const Transform* w2o , bool reverseOrientation , Parameter* params ) ;
	BBox ObjectBound () const ;
	bool Intersect ( const Ray& ray , float* tHit , float* rayEpsilon , DifferentialGeometry* dg ) const ;
	bool IntersectP ( const Ray& ray ) const ;
	float Area () const ;

protected :
    Point p1 , p2 ;
    float zmin ;
	float zmax ;
    float phiMax ;
    float rmax ;
    float a ;
	float c ;

} ;

#endif