
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __PBR_SHAPE__H
#define __PBR_SHAPE__H

#include "pbr.h"
#include "memory.h"
#include "transform.h"
#include "geometry.h"

class Shape : public ReferenceCounted
{
public :
	Shape ( const Transform* o2w , const Transform* w2o , bool ro ) 
		: ObjectToWorld(o2w) , 
		WorldToObject(w2o) , 
		reverseOrientation(ro) , 
		transformSwapsHandedness(o2w->SwapsHandedness()) , 
		shapeId(nextshapeId++) {}
	virtual ~Shape () {}
	virtual BBox ObjectBound () const = 0 ;
	virtual BBox WorldBound () const ;
	bool CanIntersect () const ;
    virtual bool Intersect ( const Ray& ray , float *tHit , float *rayEpsilon , DifferentialGeometry *dg ) const ;
	virtual bool IntersectP ( const Ray& ray ) const;
	void Refine( vector<Reference<Shape> >& refined ) const ;
    virtual void GetShadingGeometry ( const Transform& obj2world , const DifferentialGeometry& dg , DifferentialGeometry* dgShading ) const ;
	virtual float Area() const ;

public :
	const Transform* ObjectToWorld ;
	const Transform* WorldToObject ;
	const bool reverseOrientation ;
	const bool transformSwapsHandedness ;
    const unsigned int shapeId;
    static unsigned int nextshapeId;
} ;

#endif