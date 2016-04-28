
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef Sphere_H
#define Sphere_H

#include "shape.h"

class Sphere : public Shape
{
public :
	Sphere ( const Transform *o2w , const Transform* w2o , bool ro , float rad , float zmin , float zmax , float phiMax ) ;
	
	virtual BBox objectBound () const ;
    virtual bool Intersect ( const Ray& ray , float *tHit , float* rayEpsilon , DifferentialGeometry* dg ) const ;
    virtual bool IntersectP ( const Ray& ray ) const ;
	virtual float Area() const ;

private :
    float radius ;
    float phiMax ;
    float zmin , zmax ;
    float thetaMin , thetaMax ;
} ;

#endif