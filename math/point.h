
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef Point_H
#define Point_H

#include "pbr.h"
#include "pmath.h"
#include "vector.h"

class Point
{
public :
	Point() {
		this->x = 0 ;
		this->y = 0 ;
		this->z = 0 ;
	}
	Point( float x , float y , float z ) {
		this->x = x ;
		this->y = y ;
		this->z = z ;
	}
	~Point() {}

	inline bool HasNaNs() const { 
		return _isnan(x) || _isnan(y) || _isnan(z) ; 
	}

	inline void operator = (const Point& v) {
		this->x = v.x ;
		this->y = v.y ;
		this->z = v.z ;
	}

	inline Point operator + (const Vector& v) { 
		Point r ( 
			this->x + v.x ,
			this->y + v.y , 
			this->z + v.z) ;

		return r ;
	}

	inline Point operator + (const Vector& v) const { 
		Point r ( 
			this->x + v.x ,
			this->y + v.y , 
			this->z + v.z) ;

		return r ;
	}

	inline Point operator + (const Point& v) { 
		Point r ( 
			this->x + v.x ,
			this->y + v.y , 
			this->z + v.z) ;

		return r ;
	}

	inline Point operator - (const Point& v) { 
		Point r ( 
			this->x - v.x ,
			this->y - v.y , 
			this->z - v.z) ;
		return r ;
	}

    inline Vector operator - (const Point &p) const {
        assert(!p.HasNaNs());
        return Vector(x - p.x, y - p.y, z - p.z);
    }

	inline Point operator * (float scale) { 
		Point r ( 
			this->x * scale ,
			this->y * scale , 
			this->z * scale) ;
		return r ;
	}

	inline Point operator / (float scale) { 		
		
		assert( scale != 0 ) ;
		scale = 1.0f / scale ;

		Point r ( 
			this->x * scale ,
			this->y * scale , 
			this->z * scale) ;

		return r ;

	}

	inline float Dot ( const Point& v ) {
		float r = 0.0f ;
		r = this->x*v.x + 
			this->y*v.y + 
			this->z*v.z ;
		return r ;
	}

	inline Point Cross ( const Point& v ) {

		Point r (
			this->y*v.z - this->z*v.y , 
			this->z*v.x - this->x*v.z , 
			this->x*v.y - this->y*v.x  
			) ; 

		return r ;

	}

	inline float Mag () {
		float r = 0.0f ;
		r = sqrtf( 
			this->x*this->x + 
			this->y*this->y + 
			this->z*this->z ) ;

		return r ;
	}

	inline void Normalize () {
		float mg = this->Mag () ;
		if ( mg == 0 ) {
			return ;
		}
		*this = *this / mg ;
	}

	inline float Distance ( const Point& v ) {
		float distance ; 
		Point r = *this - v ;

		distance =  
			this->x*this->x + 
			this->y*this->y + 
			this->z*this->z ;

		return distance ;
	}

	inline float DistanceSquared ( const Point& v ) {
		float distance ; 
		Point r = *this - v ;
		distance = r.Mag () ;
		return distance ;
	}

    inline float operator[](int i) const {
        assert(i >= 0 && i <= 2);
        return (&x)[i];
    }
    
    inline float &operator[](int i) {
        assert(i >= 0 && i <= 2);
        return (&x)[i];
    }

	float x ;
	float y ;
	float z ;

} ;

#endif