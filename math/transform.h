
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Renderer From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __PBR_TRANSFORM__H
#define __PBR_TRANSFORM__H

#include "pbr.h"
#include "vector.h"
#include "point.h"
#include "matrix.h"
#include "geometry.h"
#include "quaternion.h"

class Transform
{
public :
	Transform () {}
	~Transform () {}
	Transform ( const float mat[4][4] ) {
        m = Matrix4x4 ( mat[0][0] , mat[0][1] , mat[0][2] , mat[0][3] ,
                        mat[1][0] , mat[1][1] , mat[1][2] , mat[1][3] ,
                        mat[2][0] , mat[2][1] , mat[2][2] , mat[2][3] ,
                        mat[3][0] , mat[3][1] , mat[3][2] , mat[3][3] ) ;
		inv = m.Inverse () ;	 		   			    		    
	}						    

	Transform ( const Matrix4x4& mat ) {
		m = mat ;
		inv = m.Inverse () ;
	}
	
    Transform ( const Matrix4x4 &mat , const Matrix4x4 &minv )
       : m(mat), inv(minv) {
    }

	Transform Translate ( const Vector& delta ) ;

	Transform Scale ( float x , float y , float z ) ;

	bool HasScale() const ;

	bool SwapsHandedness() const ;

	Transform RotateX ( float angle ) ;
	
	Transform RotateY ( float angle ) ;
	
	Transform RotateZ ( float angle ) ;
	
	Transform Rotate ( float angle , const Vector &axis ) ;
	
	Transform LookAt ( const Point& pos , const Point& look , const Vector& up ) ;
	
	bool SolveLinearSystem2x2 ( const float A[2][2] , const float B[2] ,float *x0 , float *x1 ) ;
	
	Transform Orthographic ( float znear, float zfar) ;
	
	Transform Perspective ( float fov, float znear, float zfar ) ;

	/*
	 brief : inline functions
	*/ 
    inline Transform Inverse ( const Transform& t ){
		return Transform ( t.inv , t.m ) ;
	}

    inline Transform Transpose ( Transform t ) {
		return Transform ( t.m.Transpose () , t.inv.Transpose () ) ;
	}

	inline Transform operator * (const Transform& t2) const {
		Matrix4x4 m1 = Matrix4x4::Mul(m, t2.m) ;
		Matrix4x4 m2 = Matrix4x4::Mul(t2.inv, inv) ;
		return Transform(m1, m2) ;
	}

    inline bool operator == (Transform t) const {
        return t.m == m && t.inv == inv ;
    }
    
	inline bool operator != ( Transform& t ) const {
        return t.m != m || t.inv != inv ;
    }

    inline bool operator < (const Transform &t2) const {
        for (unsigned int i = 0; i < 4; ++i)
            for (unsigned int j = 0; j < 4; ++j) {
                if (m.m[i][j] < t2.m.m[i][j]) return true ;
                if (m.m[i][j] > t2.m.m[i][j]) return false ;
            }
        return false ;
    }

	inline Point operator ()( const Point& pt ) const {

		float x = pt.x, y = pt.y, z = pt.z;

		float xp = m.m[0][0]*x + m.m[0][1]*y + m.m[0][2]*z + m.m[0][3] ;
		float yp = m.m[1][0]*x + m.m[1][1]*y + m.m[1][2]*z + m.m[1][3] ;
		float zp = m.m[2][0]*x + m.m[2][1]*y + m.m[2][2]*z + m.m[2][3] ;
		float wp = m.m[3][0]*x + m.m[3][1]*y + m.m[3][2]*z + m.m[3][3] ;
		assert(wp != 0);											   

		if (wp == 1.) 
			return Point(xp, yp, zp) ;
		else          
			return Point(xp, yp, zp)/wp ;
	}

	inline void operator ()( const Point &pt , Point *ptrans ) const {
		
		float x = pt.x, y = pt.y, z = pt.z ;
		ptrans->x = m.m[0][0]*x + m.m[0][1]*y + m.m[0][2]*z + m.m[0][3] ;
		ptrans->y = m.m[1][0]*x + m.m[1][1]*y + m.m[1][2]*z + m.m[1][3] ;
		ptrans->z = m.m[2][0]*x + m.m[2][1]*y + m.m[2][2]*z + m.m[2][3] ;
		float w   = m.m[3][0]*x + m.m[3][1]*y + m.m[3][2]*z + m.m[3][3] ;
		
		if (w != 1.) {
			*ptrans = *ptrans / w ;
		}

	}

	inline Vector operator ()( const Vector& v ) const {
	  float x = v.x , y = v.y , z = v.z ;
	  return Vector ( m.m[0][0]*x + m.m[0][1]*y + m.m[0][2]*z ,
					  m.m[1][0]*x + m.m[1][1]*y + m.m[1][2]*z ,
					  m.m[2][0]*x + m.m[2][1]*y + m.m[2][2]*z ) ;
	}


	inline void operator()(const Vector& v , Vector *vt) const {
	  float x = v.x, y = v.y, z = v.z ;
	  vt->x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z ;
	  vt->y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z ;
	  vt->z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z ;
	}

	inline Normal operator ()(const Normal& n) const {
		float x = n.x, y = n.y, z = n.z ;
		return Normal(inv.m[0][0]*x + inv.m[1][0]*y + inv.m[2][0]*z ,
					  inv.m[0][1]*x + inv.m[1][1]*y + inv.m[2][1]*z ,
					  inv.m[0][2]*x + inv.m[1][2]*y + inv.m[2][2]*z ) ;
	}

	inline void operator ()(const Normal& n , Normal* nt) const {
		float x = n.x, y = n.y, z = n.z ;						    
		nt->x = inv.m[0][0] * x + inv.m[1][0] * y + inv.m[2][0] * z ;
		nt->y = inv.m[0][1] * x + inv.m[1][1] * y + inv.m[2][1] * z ;
		nt->z = inv.m[0][2] * x + inv.m[1][2] * y + inv.m[2][2] * z ;
	}															    

	inline Ray operator ()(const Ray& r) const {
		Ray ret = r;
		(*this)(ret.o, &ret.o) ;
		(*this)(ret.d, &ret.d) ;
		return ret;
	}

	inline void operator ()(const Ray& r, Ray* rt) const {
		(*this)(r.o , &rt->o) ;
		(*this)(r.d , &rt->d) ;
		if (rt != &r) {
			rt->mint = r.mint ;
			rt->maxt = r.maxt ;
			rt->time = r.time ;
			rt->depth = r.depth ;
		}
	}

	inline void operator ()(const RayDifferential& r , RayDifferential* rt) const {
		(*this)(Ray(r), rt) ;
		rt->hasDifferentials = r.hasDifferentials ;
		(*this)(r.rxOrigin , &rt->rxOrigin) ;
		(*this)(r.ryOrigin , &rt->ryOrigin) ;
		(*this)(r.rxDirection , &rt->rxDirection) ;
		(*this)(r.ryDirection , &rt->ryDirection) ;
	}

	inline RayDifferential operator ()(const RayDifferential& r) const {
		RayDifferential ret ;
		(*this)(Ray(r), &ret) ;
		ret.hasDifferentials = r.hasDifferentials ;
		(*this)(r.rxOrigin , &ret.rxOrigin) ;
		(*this)(r.ryOrigin , &ret.ryOrigin) ;
		(*this)(r.rxDirection , &ret.rxDirection) ;
		(*this)(r.ryDirection , &ret.ryDirection) ;
		return ret ;
	}

	inline BBox operator ()(const BBox& b) const {
		const Transform& M = *this;
		BBox ret( M(Point(b.min.x, b.min.y, b.min.z)) ) ;
																 
		ret = ret.Union( ret , M(Point(b.max.x, b.min.y, b.min.z)) ) ;
		ret = ret.Union( ret , M(Point(b.min.x, b.max.y, b.min.z)) ) ;
		ret = ret.Union( ret , M(Point(b.min.x, b.min.y, b.max.z)) ) ;
		ret = ret.Union( ret , M(Point(b.min.x, b.max.y, b.max.z)) ) ;
		ret = ret.Union( ret , M(Point(b.max.x, b.max.y, b.min.z)) ) ;
		ret = ret.Union( ret , M(Point(b.max.x, b.min.y, b.max.z)) ) ;
		ret = ret.Union( ret , M(Point(b.max.x, b.max.y, b.max.z)) ) ;
		return ret;										 		 
	}

	Matrix4x4 m ;
	Matrix4x4 inv ;
    friend class AnimatedTransform ;
    friend struct Quaternion ;

} ;

class AnimatedTransform 
{
public :

    AnimatedTransform ( Transform *transform1 , float time1 , Transform *transform2 , float time2 )
        : startTime(time1), endTime(time2),
          startTransform(transform1), endTransform(transform2) , actuallyAnimated(*startTransform != *endTransform) {
        Decompose(startTransform->m, &T[0], &R[0], &S[0]);
        Decompose(endTransform->m, &T[1], &R[1], &S[1]);
    }

    static void Decompose(const Matrix4x4 &m, Vector *T, Quaternion *R, Matrix4x4 *S);

    void Interpolate(float time, Transform *t) const;

    BBox MotionBounds(const BBox &b, bool useInverse) const;

    bool HasScale() const { return startTransform->HasScale() || endTransform->HasScale(); }	

    void operator()(const Ray &r, Ray *tr) const;

    void operator()(const RayDifferential &r, RayDifferential *tr) const;

    Point operator()(float time, const Point &p) const;

    Vector operator()(float time, const Vector &v) const;

    Ray operator()(const Ray &r) const;

private :

    const float startTime ;
	const float endTime ;
    Transform *startTransform ;
	Transform *endTransform ;
    const bool actuallyAnimated ;

    Vector T[2] ;
    Quaternion R[2] ;
    Matrix4x4 S[2] ;

};


#endif
