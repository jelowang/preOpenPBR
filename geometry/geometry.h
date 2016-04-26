
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Renderer From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __PBR_GEOMETRY__H
#define __PBR_GEOMETRY__H

#include "pbr.h"
#include "pmath.h"
#include "vector.h"
#include "point.h"
#include "parameter.h"
class Shape ;

class Normal
{
public :
	explicit Normal ( const Vector& v ) : x(v.x) , y(v.y) , z(v.z) {
	}
	Normal ( float xx , float yy , float zz ) {
		this->x = xx ;
		this->y = yy ;
		this->z = zz ;
	}
	Normal () {}
	~Normal () {}

	inline Normal FaceForward ( const Normal& n , const Vector& v ) {
		Normal normal(n) ;
		Vector v2 ( n.x , n.y , n.z ) ;
		if ( v2.Dot ( v ) < 0.0f ) {
			normal.x = normal.x * -1.0f ;
			normal.x = normal.x * -1.0f ;
			normal.x = normal.x * -1.0f ;
		}
		return normal ;
	}

	inline float length ()
	{
		return sqrtf(x*x+y*y+z*z) ;
	}

    Normal operator/(float f) const {
        assert(f != 0);
        float inv = 1.f/f;
        return Normal(x * inv, y * inv, z * inv);
    }

    Normal &operator*=(float f) {
        x *= f; y *= f; z *= f;
        return *this;
    }

    Normal &operator=(const Normal &n) {
        assert(!n.HasNaNs());
        x = n.x; y = n.y; z = n.z;
        return *this;
    }

	inline bool HasNaNs() const { 
		return _isnan(x) || _isnan(y) || _isnan(z) ; 
	}

	float x ;
	float y ;
	float z ;
} ;

class Ray 
{
public :

	Ray() : mint(.0f) , maxt(INFINITY) , time(.0f) , depth(0) {}
	Ray ( const Point& origin , const Vector& direction , 
		float start , float end = INFINITY , float t = .0f , int d = 0 ) :
	o(origin) , d(direction) , mint(start) , maxt(end) , time(t) , depth(d) {}
	
	Ray( const Point& origin , const Vector& direction ,
		const Ray& parent , float start , float end = INFINITY ) :
	o(origin) , d(direction) , mint(start) , maxt(end) , time(parent.time) , depth(parent.depth+1) {}

	inline Point operator()(float t ) {
		return o + d * t ;
	}

	mutable float mint ;
	mutable float maxt ;
	float time ;
	int depth ;
	Point o ;
	Vector d ;

} ;

class RayDifferential : public Ray 
{
public :
	RayDifferential() { hasDifferentials = false ; }
	RayDifferential ( const Point& origin , const Vector& direction , 
		float start , float end = INFINITY , float t = .0f , int d = 0 ) :
	Ray( origin , direction , start , end , t , d ) {
		hasDifferentials = false ;
	}

	RayDifferential( const Point& origin , const Vector& direction ,
		const Ray& parent , float start , float end = INFINITY ) :
	Ray( origin , direction , parent.time , parent.depth + 1 ) {
		hasDifferentials = false ;
	}

	explicit RayDifferential ( const Ray& ray ) : Ray(ray) {
		hasDifferentials = false ;
	}

	inline void ScaleDifferntials ( float scale ) {
		rxOrigin = o + (rxOrigin-o) * scale ;
		ryOrigin = o + (ryOrigin-o) * scale ;
		rxDirection = d + (rxDirection-d) * scale ;
		ryDirection = d + (ryDirection-d) * scale ;
	}
	
	bool hasDifferentials ;
	Point rxOrigin ;
	Point ryOrigin ;
	Vector rxDirection ;
	Vector ryDirection ;

} ;

class BBox
{
public :
	BBox () {
		min = Point ( INFINITY , INFINITY , INFINITY )  ;
		max = Point ( -INFINITY , -INFINITY , -INFINITY )  ;
	}

	BBox ( const Point& point ) : min(point) , max(point) {}

    BBox(const Point &p1, const Point &p2) {
        min = Point(MIN(p1.x, p2.x), MIN(p1.y, p2.y), MIN(p1.z, p2.z));
        max = Point(MAX(p1.x, p2.x), MAX(p1.y, p2.y), MAX(p1.z, p2.z));
    }

	inline BBox Union ( const BBox& b , const BBox& b2 ) {
		BBox ret;
		ret.min.x = MIN( b.min.x , b2.min.x );
		ret.min.y = MIN( b.min.y , b2.min.y );
		ret.min.z = MIN( b.min.z , b2.min.z );
		ret.max.x = MAX( b.max.x , b2.max.x );
		ret.max.y = MAX( b.max.y , b2.max.y );
		ret.max.z = MAX( b.max.z , b2.max.z );
		return ret;						    
	}

	inline BBox Union ( const BBox& box , const Point& point ) {
		BBox ret ;
		ret.min.x = MIN(box.min.x,point.x) ;
		ret.min.y = MIN(box.min.y,point.y) ;
		ret.min.z = MIN(box.min.z,point.z) ;
		ret.max.x = MAX(box.max.x,point.x) ;
		ret.max.y = MAX(box.max.y,point.y) ;
		ret.max.z = MAX(box.max.z,point.z) ;
		return ret ; 
	}

	inline bool Overlap ( const BBox& box ) {
		bool x = (max.x >= box.min.x ) && (min.x <= box.max.x) ;
		bool y = (max.y >= box.min.y ) && (min.y <= box.max.y) ;
		bool z = (max.z >= box.min.z ) && (min.z <= box.max.z) ;
		return ( x & y & z ) ;
	}

	inline bool Inside ( const Point& point ) {
		return ( 
			point.x >= min.x && point.x <= max.x &&
			point.y >= min.y && point.y <= max.y && 
			point.z >= min.z && point.z <= max.z ) ;
	}

	inline void Expand ( float delta ) {
		min = min - Point (delta,delta,delta) ;
		max = max + Point (delta,delta,delta) ;
	}

	inline float SurfaceArea () {
		Point point = max - min ;
		Vector d(point.x,point.y,point.z) ;
		return 2.f * (d.x*d.y + d.x*d.z + d.y*d.z) ;
	}

	inline float Volume () {
		Point point = max - min ;
		Vector d(point.x,point.y,point.z) ;
		return d.x * d.y * d.z ;
	}

	inline int MaximumExtent () {
		Point diag = max - min ;
		if ( diag.x > diag.y && diag.x > diag.z )
			return 0 ;
		else if ( diag.y > diag.z )
			return 1 ;
		return 2 ;
	}

	inline Point Lerp_ ( float tx , float ty , float tz ) {
		return Point ( 
			Lerp(tx,min.x,max.x) , 
			Lerp(ty,min.y,max.y) ,
			Lerp(tz,min.z,max.z) ) ;
	}

	inline Vector Offset ( const Point& point) {
		return Vector (
			(point.x-min.x) / (max.x-min.x) ,
			(point.y-min.y) / (max.y-min.y) ,
			(point.z-min.z) / (max.z-min.z) 
			) ; 
	}

	inline void BoundingSphere ( Point* c , float* rad ) {
		*c = min * .5f + max * .5f ;
		*rad = Inside (*c) ? c->Distance(max) : 0.f ;
	}

	Point min ;
	Point max ;
} ;

inline float Dot ( const Vector& v1 , const Vector& v2 ) {
    assert(!v1.HasNaNs() && !v2.HasNaNs());
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float Dot(const Normal &n1, const Vector &v2) {
    assert(!n1.HasNaNs() && !v2.HasNaNs());
    return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}

inline Vector Cross(const Vector &v1, const Vector &v2) {
    assert(!v1.HasNaNs() && !v2.HasNaNs());
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vector((v1y * v2z) - (v1z * v2y),
                  (v1z * v2x) - (v1x * v2z),
                  (v1x * v2y) - (v1y * v2x));
}

inline Vector Normalize ( const Vector& v ) {
	Vector r = v ;
	r = r / r.length () ;
	return r ; 
}

inline Normal Normalize ( const Normal& v ) {
	Normal r = v ;
	r = r / r.length () ;
	return r ; 
}

//(c)pbrt source code Copyright(c) 1998-2012 Matt Pharr and Greg Humphreys.
struct DifferentialGeometry {
    DifferentialGeometry() { 
        u = v = dudx = dvdx = dudy = dvdy = 0.; 
        shape = NULL; 
    }
    // DifferentialGeometry Public Methods
    DifferentialGeometry(const Point &P, const Vector &DPDU,
            const Vector &DPDV, const Normal &DNDU,
            const Normal &DNDV, float uu, float vv,
            const Shape *sh);
    void ComputeDifferentials(const RayDifferential &r) const;

    // DifferentialGeometry Public Data
    Point p;
    Normal nn;
    float u, v;
    const Shape *shape;
    Vector dpdu, dpdv;
    Normal dndu, dndv;
    mutable Vector dpdx, dpdy;
    mutable float dudx, dvdx, dudy, dvdy;
};


#endif

