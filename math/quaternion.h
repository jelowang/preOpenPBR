
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __PBR_QUATERNION__H
#define __PBR_QUATERNION__H

#include "pbr.h"
#include "Vector.h"
#include "Point.h"
#include "Matrix.h"
#include "geometry.h"

class Transform ;

class Quaternion
{
public :
	Quaternion () {
		v = Vector ( 0.f , 0.f , 0.f ) ;
		w = 1.f ;
	}
	~Quaternion () {}

	Quaternion ( const Transform& t ) ;

	Transform Convert2Transform () const ;

    Quaternion& operator += ( const Quaternion& q ) {
        v = v + q.v ;
        w += q.w ; 
        return *this;
    }

    friend Quaternion operator + ( const Quaternion& q1 , const Quaternion& q2 ) {
        Quaternion ret = q1 ;
        return ret += q2 ;
    }

    Quaternion &operator -= ( const Quaternion& q ) {
        v = v - q.v ;
        w -= q.w ;
        return *this ;
    }

    friend Quaternion operator - ( const Quaternion& q1 , const Quaternion& q2 ) {
        Quaternion ret = q1 ;
        return ret -= q2 ;
    }

    Quaternion& operator *= (float f) {
        v = v * f ;
        w *= f ;
        return *this ;
    }

    Quaternion operator * (float f) const {
        Quaternion ret = *this ;
        ret.v = ret.v * f ;
        ret.w *= f ;
        return ret ;
    }

    Quaternion& operator /= (float f) {
        v = v / f ;
        w /= f ;
        return *this ;
    }

    Quaternion operator / (float f) const {
        Quaternion ret = *this ;
        ret.v = ret.v / f ;
        ret.w /= f ;
        return ret ;
    } 

	Vector v ;
	float w ;

} ;

inline Quaternion operator * ( float f , const Quaternion& q ) {
    return q * f ;
}


inline float Dot (const Quaternion &q1, const Quaternion &q2) {
    return Dot(q1.v, q2.v) + q1.w * q2.w ;
}


inline Quaternion Normalize ( const Quaternion& q ) {
    return q / sqrtf ( Dot(q,q) ) ;
}

extern Quaternion Slerp ( float t , const Quaternion& q1 , const Quaternion& q2 ) ;

#endif