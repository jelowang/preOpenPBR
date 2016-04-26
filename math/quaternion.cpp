
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Renderer From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "quaternion.h"
#include "transform.h"

Quaternion::Quaternion ( const Transform& t ) {
	 
    const Matrix4x4 &m = t.m;

    float trace = m.m[0][0] + m.m[1][1] + m.m[2][2];

    if (trace > 0.f) {
        // Compute w from matrix trace, then xyz
        // 4w^2 = m[0][0] + m[1][1] + m[2][2] + m[3][3] (but m[3][3] == 1)
        float s = sqrtf(trace + 1.0);
        w = s / 2.0f;
        s = 0.5f / s;
        v.x = (m.m[2][1] - m.m[1][2]) * s;
        v.y = (m.m[0][2] - m.m[2][0]) * s;
        v.z = (m.m[1][0] - m.m[0][1]) * s;
    }
    else {
        // Compute largest of $x$, $y$, or $z$, then remaining components
        const int nxt[3] = {1, 2, 0};
        float q[3];
        int i = 0;
        if (m.m[1][1] > m.m[0][0]) i = 1;
        if (m.m[2][2] > m.m[i][i]) i = 2;
        int j = nxt[i];
        int k = nxt[j];
        float s = sqrtf((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + 1.0);
        q[i] = s * 0.5f;
        if (s != 0.f) s = 0.5f / s;
        w = (m.m[k][j] - m.m[j][k]) * s;
        q[j] = (m.m[j][i] + m.m[i][j]) * s;
        q[k] = (m.m[k][i] + m.m[i][k]) * s;
        v.x = q[0];
        v.y = q[1];
        v.z = q[2];
    }

}

Transform Quaternion::Convert2Transform () const {

    float xx = v.x * v.x, yy = v.y * v.y, zz = v.z * v.z ;
    float xy = v.x * v.y, xz = v.x * v.z, yz = v.y * v.z ;
    float wx = v.x * w,   wy = v.y * w,   wz = v.z * w ;

    Matrix4x4 m ;

    m.m[0][0] = 1.f - 2.f * (yy + zz) ;
    m.m[0][1] =       2.f * (xy + wz) ;
    m.m[0][2] =       2.f * (xz - wy) ;
    m.m[1][0] =       2.f * (xy - wz) ;
    m.m[1][1] = 1.f - 2.f * (xx + zz) ;
    m.m[1][2] =       2.f * (yz + wx) ;
    m.m[2][0] =       2.f * (xz + wy) ;
    m.m[2][1] =       2.f * (yz - wx) ;
    m.m[2][2] = 1.f - 2.f * (xx + yy) ;

	return Transform ( m.Transpose() , m ) ;
}

Quaternion Slerp ( float t , const Quaternion& q1 , const Quaternion& q2 ) {

    float cosTheta = Dot ( q1 , q2) ;
    if (cosTheta > .9995f)
        return Normalize( (1.f - t) * q1 + t * q2);
    else {
        float theta = acosf(Clamp(cosTheta, -1.f, 1.f));
        float thetap = theta * t;
        Quaternion qperp = Normalize(q2 - q1 * cosTheta);
        return q1 * cosf(thetap) + qperp * sinf(thetap);
    }

}