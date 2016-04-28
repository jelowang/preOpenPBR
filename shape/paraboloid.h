
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once

#endif
#ifndef Paraboloid_H
#define Paraboloid_H

#include "shape.h"

class Paraboloid : public Shape
{
public :
	Paraboloid ( const Transform* o2w , const Transform* w2o , bool ro , float rad , float z0 , float z1 , float tm ) ;
	~Paraboloid () ;
	static Paraboloid* Create ( const Transform* o2w , const Transform* w2o , bool reverseOrientation , Parameter* params ) ;
	BBox ObjectBound () const ;
	bool Intersect ( const Ray& ray , float* tHit , float* rayEpsilon , DifferentialGeometry* dg ) const ;
	bool IntersectP ( const Ray& ray ) const ;
	float Area () const ;

protected :
    float radius ;
    float zmin ;
	float zmax ;
    float phiMax ;

} ;

#endif