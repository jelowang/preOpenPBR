
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Renderer From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef Vector_H
#define Vector_H

#include "pbr.h"
#include "pmath.h"

class Vector
{
public :
	Vector() {
		this->x = 0 ;
		this->y = 0 ;
		this->z = 0 ;
	}
	Vector( float x , float y , float z ) {
		this->x = x ;
		this->y = y ;
		this->z = z ;
	}
	~Vector() {}

	inline bool HasNaNs() const { 
		return _isnan(x) || _isnan(y) || _isnan(z) ; 
	}

	inline void operator = (const Vector& v){
		this->x = v.x ;
		this->y = v.y ;
		this->z = v.z ;
	}

	inline Vector operator + (const Vector& v) {
		Vector r ( 
			this->x + v.x ,
			this->y + v.y , 
			this->z + v.z) ;
		return r ;
	}

	inline Vector operator - (const Vector& v) { 
		Vector r ( 
			this->x - v.x ,
			this->y - v.y , 
			this->z - v.z) ;
		return r ;
	}

	inline Vector operator * (float scale) const { 
		Vector r ( 
			this->x * scale ,
			this->y * scale , 
			this->z * scale) ;
		return r ;
	}

	inline Vector operator / (float scale) { 		
		
		assert( scale != 0 ) ;
		scale = 1.0f / scale ;

		Vector r ( 
			this->x * scale ,
			this->y * scale , 
			this->z * scale) ;

		return r ;

	}

	inline float Dot ( const Vector& v ) {
		float r = 0.0f ;
		r = this->x*v.x + 
			this->y*v.y + 
			this->z*v.z ;
		return r ;
	}

	inline Vector Cross ( const Vector& v ) {

		Vector r (
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

	inline Vector Normalize () const {
		Vector r = *this ;
		float mg = r.Mag () ;
		if ( mg == 0 ) {
			return r ;
		}
		r = r / mg ;
		return r ;
	}

	inline float DistanceSquared ( const Vector& v ) {
		float distance ; 
		Vector r = *this - v ;

		distance =  
			this->x*this->x + 
			this->y*this->y + 
			this->z*this->z ;

		return distance ;
	}

	inline float distance ( const Vector& v ) {
		float distance ; 
		Vector r = *this - v ;
		distance = r.Mag () ;
		return distance ;
	}

    inline float lengthSquared() const { 
		return x*x + y*y + z*z ; 
	}

    inline float length() const { 
		return sqrtf(lengthSquared()) ; 
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

inline Vector operator * ( float f , const Vector& v ) { return v*f ; }

#endif