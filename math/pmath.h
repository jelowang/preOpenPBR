
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef Math_H
#define Math_H

#include <math.h>
#include <assert.h>
#include <algorithm>

using std::min ;
using std::max ;
using std::swap ;

#define tolerance 2e-37f
#define epsino 0.000001
#define zero(x) (-epsino <= x && x <= epsino)
#ifdef M_PI
#undef M_PI
#else
#define M_PI 3.14159265358979323846f
#endif
#define M_2PI 2.0f * M_PI 
#define OverPi 1.0f / M_PI 
#define Over2Pi 1.0f / Pi2
#define INFINITY DBL_MAX

#define cosf(__RADIAN__) cosf(__RADIAN__)
#define sinf(__RADIAN__) sinf(__RADIAN__)
#define toDegree(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180
#define toRadian(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180
#define MIN(a,b) (a<b) ? a : b 
#define MAX(a,b) (a>b) ? a : b

inline float Clamp ( float val , float low , float high ) {

    if (val < low) 
		return low ;
    else if (val > high) 
		return high ;
    else 
		return val ;

}

inline float Lerp(float t, float v1, float v2) {
    return ( 1.0f - t ) * v1 + t * v2 ;
}

inline bool Quadratic ( float A, float B , float C , float* t0 , float* t1 ) {

	float q = 0.0f ;

    float discrim = B * B - 4.f * A * C ;
    
	if ( 0.0f > discrim )
		return false ;
    
	float rootDiscrim = sqrtf(discrim) ;

	if ( 0 > B )
		q = -.5f * (B - rootDiscrim) ;
    else       
		q = -.5f * (B + rootDiscrim) ;
    
	*t0 = q / A ;
    *t1 = C / q ;

	if (*t0 > *t1) 
		swap( *t0 , *t1 ) ;

    return true ;
}

#endif