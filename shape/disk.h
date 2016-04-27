
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once

#endif
#ifndef Disk_H
#define Disk_H

#include "shape.h"

class Disk : public Shape
{
public :
	Disk ( const Transform* o2w , const Transform* w2o , bool ro , float ht, float r, float ri, float pmax ) ;
	static Disk* Create ( const Transform* o2w , const Transform* w2o , bool reverseOrientation , Parameter* params ) ;
	BBox ObjectBound () const ;
	bool Intersect ( const Ray& ray , float* tHit , float* rayEpsilon , DifferentialGeometry* dg ) const ;
	bool IntersectP ( const Ray& ray ) const ;
	float Area () const ;
	Point Sample ( float u1 , float u2 , Normal* normal ) const ;
protected :
	float height ;
	float radius ;
	float innerRadius ;
	float phiMax ;

} ;

#endif