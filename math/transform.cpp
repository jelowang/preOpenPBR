
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "transform.h"

Transform Transform::Translate ( const Vector& delta ) {
    Matrix4x4 m ( 1 , 0 , 0 , delta.x ,
                  0 , 1 , 0 , delta.y ,
                  0 , 0 , 1 , delta.z ,
                  0 , 0 , 0 ,       1 ) ;
					   
    Matrix4x4 minv ( 1 , 0 , 0 , -delta.x ,
                     0 , 1 , 0 , -delta.y ,
                     0 , 0 , 1 , -delta.z ,
                     0 , 0 , 0 ,        1 ) ;

    return Transform ( m , minv ) ;

}

Transform Transform::Scale ( float x , float y , float z ) {

    Matrix4x4 m ( x , 0 , 0 , 0 ,
                  0 , y , 0 , 0 ,
                  0 , 0 , z , 0 ,
                  0 , 0 , 0 , 1 ) ;
						  
    Matrix4x4 minv ( 1.f/x ,     0 ,     0 ,     0 ,
                     0 ,     1.f/y ,     0 ,     0 ,
                     0 ,         0 ,     1.f/z , 0 ,
                     0 ,         0 ,     0 ,     1 ) ;

    return Transform ( m , minv ) ;

}

bool Transform::HasScale() const {
	float la2 = (*this)(Vector(1,0,0)).lengthSquared() ;
	float lb2 = (*this)(Vector(0,1,0)).lengthSquared() ;
	float lc2 = (*this)(Vector(0,0,1)).lengthSquared() ;

#define NOT_ONE(x) ((x) < .999f || (x) > 1.001f)
	return (NOT_ONE(la2) || NOT_ONE(lb2) || NOT_ONE(lc2)) ;
#undef NOT_ONE

}

bool Transform::SwapsHandedness() const {
    float det = ((m.m[0][0] *
                  (m.m[1][1] * m.m[2][2] -
                   m.m[1][2] * m.m[2][1])) -
                 (m.m[0][1] *
                  (m.m[1][0] * m.m[2][2] -
                   m.m[1][2] * m.m[2][0])) +
                 (m.m[0][2] *
                  (m.m[1][0] * m.m[2][1] -
                   m.m[1][1] * m.m[2][0])));
    return det < 0.f;
}

Transform Transform::RotateX ( float angle ) {

    float sin_t = sinf(toRadian(angle)) ;
    float cos_t = cosf(toRadian(angle)) ;

    Matrix4x4 m(1 ,     0 ,      0 , 0 ,
                0 , cos_t , -sin_t , 0 ,
                0 , sin_t ,  cos_t , 0 ,
                0 ,     0 ,      0 , 1 ) ;
						 
    return Transform(m , m.Transpose()) ;


}

Transform Transform::RotateY ( float angle ) {

    float sin_t = sinf(toRadian(angle)) ;
    float cos_t = cosf(toRadian(angle)) ;

    Matrix4x4 m( cos_t , 0 , sin_t , 0 ,
                 0 ,   1 , 0, 0 ,
                -sin_t , 0 , cos_t , 0 ,
                 0 ,   0 , 0 , 1) ;

    return Transform(m, m.Transpose());
}



Transform Transform::RotateZ ( float angle ) {

    float sin_t = sinf(toRadian(angle)) ;
    float cos_t = cosf(toRadian(angle)) ;

    Matrix4x4 m(cos_t, -sin_t, 0, 0,
                sin_t,  cos_t, 0, 0,
                0,      0, 1, 0,
                0,      0, 0, 1);

    return Transform(m, m.Transpose()) ;
}


Transform Transform::Rotate ( float angle , const Vector& axis ) {

	Vector a = Normalize (axis) ;
    float s = sinf(toRadian(angle));
    float c = cosf(toRadian(angle));
    float m[4][4];

    m[0][0] = a.x * a.x + (1.f - a.x * a.x) * c;
    m[0][1] = a.x * a.y * (1.f - c) - a.z * s;
    m[0][2] = a.x * a.z * (1.f - c) + a.y * s;
    m[0][3] = 0;

    m[1][0] = a.x * a.y * (1.f - c) + a.z * s;
    m[1][1] = a.y * a.y + (1.f - a.y * a.y) * c;
    m[1][2] = a.y * a.z * (1.f - c) - a.x * s;
    m[1][3] = 0;

    m[2][0] = a.x * a.z * (1.f - c) - a.y * s;
    m[2][1] = a.y * a.z * (1.f - c) + a.x * s;
    m[2][2] = a.z * a.z + (1.f - a.z * a.z) * c;
    m[2][3] = 0;

    m[3][0] = 0 ;
    m[3][1] = 0 ;
    m[3][2] = 0 ;
    m[3][3] = 1 ;
			    
    Matrix4x4 mat(m) ;

    return Transform(mat, mat.Transpose()) ;

}


Transform Transform::LookAt ( const Point& pos , const Point& look , const Vector& up ) {
    
	float m[4][4] ;

    // Initialize fourth column of viewing matrix
    m[0][3] = pos.x ;
    m[1][3] = pos.y ;
    m[2][3] = pos.z ;
    m[3][3] = 1.0f ;

    // Initialize first three columns of viewing matrix
	Vector lk(look.x,look.y,look.z) ;
	Vector po(pos.x,pos.y,pos.z) ;
	Vector dir = (lk - po).Normalize() ;

    if (Cross(Normalize(up), dir).length() == 0) {
        printf("\"up\" vector (%f, %f, %f) and viewing direction (%f, %f, %f) "
              "passed to LookAt are pointing in the same direction.  Using "
              "the identity transformation.", up.x, up.y, up.z, dir.x, dir.y,
              dir.z);
        return Transform();
    }
    Vector left = Normalize(Cross(Normalize(up), dir));
    Vector newUp = Cross(dir, left);
    m[0][0] = left.x;
    m[1][0] = left.y;
    m[2][0] = left.z;
    m[3][0] = 0.;
    m[0][1] = newUp.x;
    m[1][1] = newUp.y;
    m[2][1] = newUp.z;
    m[3][1] = 0.;
    m[0][2] = dir.x;
    m[1][2] = dir.y;
    m[2][2] = dir.z;
    m[3][2] = 0.;

    Matrix4x4 camToWorld(m);

    return Transform ( camToWorld.Inverse(), camToWorld );

}

Transform Transform::Orthographic(float znear, float zfar) {
    return Scale(1.f, 1.f, 1.f / (zfar-znear)) *
           Translate(Vector(0.f, 0.f, -znear)) ;
}


Transform Transform::Perspective(float fov, float n, float f) {

    // Perform projective divide
    Matrix4x4 persp = Matrix4x4( 1 , 0 ,           0 ,              0 ,
                                 0 , 1 ,           0 ,              0 ,
                                 0 , 0 , f / (f - n) , -f*n / (f - n) ,
                                 0 , 0 ,           1 ,              0) ;

    // Scale to canonical viewing volume
    float invTanAng = 1.f / tanf(toRadian(fov) / 2.f) ;

    return Scale ( invTanAng , invTanAng , 1.0f ) * Transform(persp) ; 

}

/*
 brief : AnimatedTransform
*/
void AnimatedTransform::Decompose(const Matrix4x4 &m, Vector *T , Quaternion *Rquat, Matrix4x4 *S) {

	// Extract translation _T_ from transformation matrix
    T->x = m.m[0][3];
    T->y = m.m[1][3];
    T->z = m.m[2][3];

    // Compute new transformation matrix _M_ without translation
    Matrix4x4 M = m;
    for (int i = 0; i < 3; ++i)
        M.m[i][3] = M.m[3][i] = 0.f;
    M.m[3][3] = 1.f;

    // Extract rotation _R_ from transformation matrix
    float norm;
    int count = 0;
    Matrix4x4 R = M;
    do {
        // Compute next matrix _Rnext_ in series
        Matrix4x4 Rnext;
		Matrix4x4 Rit = R.Transpose().Inverse() ;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                Rnext.m[i][j] = 0.5f * (R.m[i][j] + Rit.m[i][j]);

        // Compute norm of difference between _R_ and _Rnext_
        norm = 0.f;
        for (int i = 0; i < 3; ++i) {
            float n = fabsf(R.m[i][0] - Rnext.m[i][0]) +
                      fabsf(R.m[i][1] - Rnext.m[i][1]) +
                      fabsf(R.m[i][2] - Rnext.m[i][2]);
            norm = max(norm, n);
        }
        R = Rnext;
    } while (++count < 100 && norm > .0001f);
    // XXX TODO FIXME deal with flip...
    *Rquat = Quaternion(R);

    // Compute scale _S_ using rotation and original matrix
	*S = Matrix4x4::Mul(R.Inverse(), M);

}


void AnimatedTransform::Interpolate(float time, Transform *t) const {
    // Handle boundary conditions for matrix interpolation
    if (!actuallyAnimated || time <= startTime) {
        *t = *startTransform;
        return;
    }
    if (time >= endTime) {
        *t = *endTransform;
        return;
    }
    float dt = (time - startTime) / (endTime - startTime);
    // interpolate translation at _dt_
    Vector trans = (T[0] * (1.f - dt)) + (T[1] * dt) ;
	
    // interpolate rotation at _dt_
    Quaternion rotate = Slerp(dt, R[0], R[1]);

    // interpolate scale at _dt_
    Matrix4x4 scale;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            scale.m[i][j] = Lerp(dt, S[0].m[i][j], S[1].m[i][j]);

    // Compute interpolated matrix as product of interpolated components
    *t = t->Translate(trans) * rotate.Convert2Transform() * Transform ( scale ) ;
}

BBox AnimatedTransform::MotionBounds ( const BBox& b , bool useInverse ) const {
    
	if (!actuallyAnimated) {	
		Transform r = startTransform->Inverse(*startTransform) ;
		if ( useInverse ) {
			return (r)(b) ;
		} else {
			return (*startTransform)(b);
		}
	}
      
    BBox ret;
    const int nSteps = 128;
    for (int i = 0; i < nSteps; ++i) {
        Transform t;
        float time = Lerp(float(i)/float(nSteps-1), startTime, endTime);
        Interpolate(time, &t);
        if (useInverse) {
			t = t.Inverse(t);
		}
        ret = ret.Union(ret, t(b));
    }

    return ret;

}


void AnimatedTransform::operator()(const Ray& r, Ray* tr) const {

    if (!actuallyAnimated || r.time <= startTime)
        (*startTransform)(r, tr);
    else if (r.time >= endTime)
        (*endTransform)(r, tr);
    else {
        Transform t;
        Interpolate(r.time, &t);
        t(r, tr);
    }
    tr->time = r.time;

}


void AnimatedTransform::operator()(const RayDifferential& r , RayDifferential* tr) const {
    if (!actuallyAnimated || r.time <= startTime)
        (*startTransform)(r, tr);
    else if (r.time >= endTime)
        (*endTransform)(r, tr);
    else {
        Transform t;
        Interpolate(r.time, &t);
        t(r, tr);
    }
    tr->time = r.time;

}


Point AnimatedTransform::operator()(float time, const Point& p) const {
    if (!actuallyAnimated || time <= startTime)
        return (*startTransform)(p);
    else if (time >= endTime)
        return (*endTransform)(p);
    Transform t;
    Interpolate(time, &t);
    return t(p);
}


Vector AnimatedTransform::operator()(float time, const Vector& v) const {
    if (!actuallyAnimated || time <= startTime)
        return (*startTransform)(v);
    else if (time >= endTime)
        return (*endTransform)(v);
    Transform t;
    Interpolate(time, &t);
    return t(v);
}


Ray AnimatedTransform::operator()(const Ray& r) const {
    Ray ret;
    (*this)(r, &ret);
    return ret;
}