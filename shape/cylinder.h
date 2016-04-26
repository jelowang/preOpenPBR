
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Renderer From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once

#endif
#ifndef Cylinder_H
#define Cylinder_H

#include "shape.h"

class Cylinder : public Shape
{
public :
	Cylinder ( const Transform* o2w , const Transform* w2o , bool ro , float rad , float z0 , float z1 , float pmax ) ;
	~Cylinder () ;
	static Cylinder* Create ( const Transform* o2w , const Transform* w2o , bool reverseOrientation , Parameter* params ) ;
	BBox ObjectBound () const ;
	bool Intersect ( const Ray& ray , float* tHit , float* rayEpsilon , DifferentialGeometry* dg ) const ;
	bool IntersectP ( const Ray& ray ) const ;
	float Area () const ;
	Point Sample ( float u1 , float u2 , Normal* normal ) const ;
protected :
	float radius ;
	float zmin ;
	float zmax ;
	float phiMax ;

} ;

#endif