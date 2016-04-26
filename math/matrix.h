
/*

	+	H3Matrix.cpp
	+	QDL

	+	hello3d
	+	realtime 3d engine


	+	(C) Quantum Dynamics Lab.
			Leyoo Co.,Ltd.
	+

*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __PBR_MATRIX__H
#define __PBR_MATRIX__H

#include "pbr.h"
#include "pmath.h"

class Matrix4x4
{
public :

	Matrix4x4 () ;

	~Matrix4x4 () ;

    Matrix4x4 ( float mat[4][4] ) ;
    
	Matrix4x4 ( float t00, float t01, float t02, float t03,
              float t10, float t11, float t12, float t13,
              float t20, float t21, float t22, float t23,
              float t30, float t31, float t32, float t33 ) ;


	void Identify () ;

	Matrix4x4 Mul ( float scalar ) ;
	 
	Matrix4x4 Mul ( const Matrix4x4& a ) ;

	float Determinant () ;

	Matrix4x4 Inverse () ;

	Matrix4x4 Transpose () ;

	Matrix4x4 operator * (const Matrix4x4& M) ;

	Matrix4x4 operator = (const Matrix4x4& M) ;

	bool operator == (const Matrix4x4& M) ;

	bool operator != (const Matrix4x4& M) ;

	void Display () ;

	inline void Set( int row , int col , float value ) {

		assert( row >= 0 && row <= 3 ) ;
		assert( col >= 0 && col <= 3 ) ;

		this->m[row][col] = value ;

	}

	inline void Set( float matrix[4][4] ) {
		memcpy ( this->m , matrix , 4*4*sizeof(float) ) ;
	}

    static Matrix4x4 Mul(const Matrix4x4 &m1, const Matrix4x4 &m2) {
        Matrix4x4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.m[i][j] = m1.m[i][0] * m2.m[0][j] +
                            m1.m[i][1] * m2.m[1][j] + 
                            m1.m[i][2] * m2.m[2][j] +
                            m1.m[i][3] * m2.m[3][j];
        return r;
    }

	float m[4][4] ;

} ;


#endif