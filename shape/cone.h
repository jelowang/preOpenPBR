
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once

#endif
#ifndef Cone_H
#define Cone_H

#include "shape.h"

class Cone : public Shape
{
public :
	Cone ( const Transform* o2w , const Transform* w2o , bool ro , float height , float rad , float tm ) ;
	~Cone () ;
	static Cone* Create ( const Transform* o2w , const Transform* w2o , bool reverseOrientation , Parameter* params ) ;
	BBox ObjectBound () const ;
	bool Intersect ( const Ray& ray , float* tHit , float* rayEpsilon , DifferentialGeometry* dg ) const ;
	bool IntersectP ( const Ray& ray ) const ;
	float Area () const ;

protected :
	float radius ;
	float height ;
	float phiMax ;


} ;
#endif