
/*

	+	H3Matrix.cpp
	+	QDL

	+	hello3d
	+	realtime 3d engine


	+	(C) Quantum Dynamics Lab.
			Leyoo Co.,Ltd.
	+

*/

#include "matrix.h"

Matrix4x4::Matrix4x4 () {
	memset(this->m , 0 , sizeof(this->m)) ;
	Identify () ;
}

Matrix4x4::~Matrix4x4 () {
}

Matrix4x4::Matrix4x4 (float mat[4][4]) {
    memcpy(m, mat, 16*sizeof(float)) ;
}


Matrix4x4::Matrix4x4 (float t00, float t01, float t02, float t03,
                     float t10, float t11, float t12, float t13,
                     float t20, float t21, float t22, float t23,
                     float t30, float t31, float t32, float t33) {

    m[0][0] = t00; m[0][1] = t01; m[0][2] = t02; m[0][3] = t03 ;
    m[1][0] = t10; m[1][1] = t11; m[1][2] = t12; m[1][3] = t13 ;
    m[2][0] = t20; m[2][1] = t21; m[2][2] = t22; m[2][3] = t23 ;
    m[3][0] = t30; m[3][1] = t31; m[3][2] = t32; m[3][3] = t33 ;
															   
}

void Matrix4x4::Identify () {

	m[0][0] = 1.0f ;	m[0][1] = 0 ;		m[0][2] = 0 ;		m[0][3] = 0 ;
	m[1][0] = 0 ;		m[1][1] = 1.0f ;	m[1][2] = 0 ;		m[1][3] = 0 ;
	m[2][0] = 0 ;		m[2][1] = 0 ;		m[2][2] = 1.0f ;	m[2][3] = 0 ;
	m[3][0] = 0 ;		m[3][1] = 0 ;		m[3][2] = 0 ;		m[3][3] = 1.0f ;

}

Matrix4x4 Matrix4x4::Mul ( float scalar ) {
	Matrix4x4 mat ;

	mat.m[0][0] = m[0][0] * scalar ;				
	mat.m[1][0] = m[1][0] * scalar ;				
	mat.m[2][0] = m[2][0] * scalar ;				
	mat.m[3][0] = m[3][0] * scalar ;				
				  		   
	mat.m[0][1] = m[0][1] * scalar ;	
	mat.m[1][1] = m[1][1] * scalar ;	
	mat.m[2][1] = m[2][1] * scalar ;	
	mat.m[3][1] = m[3][1] * scalar ;	
				  		   
	mat.m[0][2] = m[0][2] * scalar ;	
	mat.m[1][2] = m[1][2] * scalar ;	
	mat.m[2][2] = m[2][2] * scalar ;	
	mat.m[3][2] = m[3][2] * scalar ;	
				  		   
	mat.m[0][3] = m[0][3] * scalar ;
	mat.m[1][3] = m[1][3] * scalar ;
	mat.m[2][3] = m[2][3] * scalar ;
	mat.m[3][3] = m[3][3] * scalar ;

	return mat ;					  
}

Matrix4x4 Matrix4x4::Mul ( const Matrix4x4& a ) {

	Matrix4x4 r ;

	r.m[0][0] = a.m[0][0]*m[0][0] + a.m[1][0]*m[0][1] + a.m[2][0]*m[0][2] + a.m[3][0]*m[0][3] ; r.m[0][1] = a.m[0][1]*m[0][0] + a.m[1][1]*m[0][1] + a.m[2][1]*m[0][2] + a.m[3][1]*m[0][3] ; r.m[0][2] = a.m[0][2]*m[0][0] + a.m[1][2]*m[0][1] + a.m[2][2]*m[0][2] + a.m[3][2]*m[0][3] ; r.m[0][3] = a.m[0][3]*m[0][0] + a.m[1][3]*m[0][1] + a.m[2][3]*m[0][2] + a.m[3][3]*m[0][3] ;
	r.m[1][0] = a.m[0][0]*m[1][0] + a.m[1][0]*m[1][1] + a.m[2][0]*m[1][2] + a.m[3][0]*m[1][3] ; r.m[1][1] = a.m[0][1]*m[1][0] + a.m[1][1]*m[1][1] + a.m[2][1]*m[1][2] + a.m[3][1]*m[1][3] ; r.m[1][2] = a.m[0][2]*m[1][0] + a.m[1][2]*m[1][1] + a.m[2][2]*m[1][2] + a.m[3][2]*m[1][3] ; r.m[1][3] = a.m[0][3]*m[1][0] + a.m[1][3]*m[1][1] + a.m[2][3]*m[1][2] + a.m[3][3]*m[1][3] ;
	r.m[2][0] = a.m[0][0]*m[2][0] + a.m[1][0]*m[2][1] + a.m[2][0]*m[2][2] + a.m[3][0]*m[2][3] ; r.m[2][1] = a.m[0][1]*m[2][0] + a.m[1][1]*m[2][1] + a.m[2][1]*m[2][2] + a.m[3][1]*m[2][3] ; r.m[2][2] = a.m[0][2]*m[2][0] + a.m[1][2]*m[2][1] + a.m[2][2]*m[2][2] + a.m[3][2]*m[2][3] ; r.m[2][3] = a.m[0][3]*m[2][0] + a.m[1][3]*m[2][1] + a.m[2][3]*m[2][2] + a.m[3][3]*m[2][3] ;
	r.m[3][0] = a.m[0][0]*m[3][0] + a.m[1][0]*m[3][1] + a.m[2][0]*m[3][2] + a.m[3][0]*m[3][3] ; r.m[3][1] = a.m[0][1]*m[3][0] + a.m[1][1]*m[3][1] + a.m[2][1]*m[3][2] + a.m[3][1]*m[3][3] ; r.m[3][2] = a.m[0][2]*m[3][0] + a.m[1][2]*m[3][1] + a.m[2][2]*m[3][2] + a.m[3][2]*m[3][3] ; r.m[3][3] = a.m[0][3]*m[3][0] + a.m[1][3]*m[3][1] + a.m[2][3]*m[3][2] + a.m[3][3]*m[3][3] ;

	return r ;

}

float Matrix4x4::Determinant () {

	float value = 0.0f ;

    float a0 = m[0][0] * m[1][1] - m[1][0] * m[0][1] ;
    float a1 = m[0][0] * m[2][1] - m[2][0] * m[0][1] ;
    float a2 = m[0][0] * m[3][1] - m[3][0] * m[0][1] ;
    float a3 = m[1][0] * m[2][1] - m[2][0] * m[1][1] ;
    float a4 = m[1][0] * m[3][1] - m[3][0] * m[1][1] ;
    float a5 = m[2][0] * m[3][1] - m[3][0] * m[2][1] ;
    float b0 = m[0][2] * m[1][3] - m[1][2] * m[0][3] ;
    float b1 = m[0][2] * m[2][3] - m[2][2] * m[0][3] ;
    float b2 = m[0][2] * m[3][3] - m[3][2] * m[0][3] ;
    float b3 = m[1][2] * m[2][3] - m[2][2] * m[1][3] ;
    float b4 = m[1][2] * m[3][3] - m[3][2] * m[1][3] ;
    float b5 = m[2][2] * m[3][3] - m[3][2] * m[2][3] ;

    value = (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0) ; 

	return value ;

}

Matrix4x4 Matrix4x4::Inverse () {
	Matrix4x4 mat(*this) ;
	
	float det = mat.Determinant () ;

    float a0 = m[0][0] * m[1][1] - m[1][0] * m[0][1] ;
    float a1 = m[0][0] * m[2][1] - m[2][0] * m[0][1] ;
    float a2 = m[0][0] * m[3][1] - m[3][0] * m[0][1] ;
    float a3 = m[1][0] * m[2][1] - m[2][0] * m[1][1] ;
    float a4 = m[1][0] * m[3][1] - m[3][0] * m[1][1] ;
    float a5 = m[2][0] * m[3][1] - m[3][0] * m[2][1] ;
    float b0 = m[0][2] * m[1][3] - m[1][2] * m[0][3] ;
    float b1 = m[0][2] * m[2][3] - m[2][2] * m[0][3] ;
    float b2 = m[0][2] * m[3][3] - m[3][2] * m[0][3] ;
    float b3 = m[1][2] * m[2][3] - m[2][2] * m[1][3] ;
    float b4 = m[1][2] * m[3][3] - m[3][2] * m[1][3] ;
    float b5 = m[2][2] * m[3][3] - m[3][2] * m[2][3] ;

    det = (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0) ; 

	if ( fabs ( det ) < tolerance ) {
		return mat ;
	}

    mat.m[0][0]  = m[1][1] * b5 - m[2][1] * b4 + m[3][1] * b3 ;
    mat.m[1][0]  = -m[1][0] * b5 + m[2][0] * b4 - m[3][0] * b3 ;
    mat.m[2][0]  = m[1][3] * a5 - m[2][3] * a4 + m[3][3] * a3 ;
    mat.m[3][0]  = -m[1][2] * a5 + m[2][2] * a4 - m[3][2] * a3 ;

    mat.m[0][1]  = -m[0][1] * b5 + m[2][1] * b2 - m[3][1] * b1 ;
    mat.m[1][1]  = m[0][0] * b5 - m[2][0] * b2 + m[3][0] * b1 ;
    mat.m[2][1]  = -m[0][3] * a5 + m[2][3] * a2 - m[3][3] * a1 ;
    mat.m[3][1]  = m[0][2] * a5 - m[2][2] * a2 + m[3][2] * a1 ;

    mat.m[0][2]  = m[0][1] * b4 - m[1][1] * b2 + m[3][1] * b0 ;
    mat.m[1][2]  = -m[0][0] * b4 + m[1][0] * b2 - m[3][0] * b0 ;
    mat.m[2][2] = m[0][3] * a4 - m[1][3] * a2 + m[3][3] * a0 ;
    mat.m[3][2] = -m[0][2] * a4 + m[1][2] * a2 - m[3][2] * a0 ;
	
    mat.m[0][3] = -m[0][1] * b3 + m[1][1] * b1 - m[2][1] * b0 ;
    mat.m[1][3] = m[0][0] * b3 - m[1][0] * b1 + m[2][0] * b0 ;
    mat.m[2][3] = -m[0][3] * a3 + m[1][3] * a1 - m[2][3] * a0 ;
    mat.m[3][3] = m[0][2] * a3 - m[1][2] * a1 + m[2][2] * a0 ;

	mat = mat.Mul ( 1.0f / det ) ;

	return mat ;
}

Matrix4x4 Matrix4x4::Transpose () {

   return Matrix4x4(m[0][0], m[1][0], m[2][0], m[3][0],
                    m[0][1], m[1][1], m[2][1], m[3][1],
                    m[0][2], m[1][2], m[2][2], m[3][2],
                    m[0][3], m[1][3], m[2][3], m[3][3]);

}

void Matrix4x4::Display () {

	printf("%1.3f|%1.3f|%1.3f|%1.3f|\n" , m[0][0] , m[0][1] , m[0][2] , m[0][3] ) ;
	printf("%1.3f|%1.3f|%1.3f|%1.3f|\n" , m[1][0] , m[1][1] , m[1][2] , m[1][3] ) ;
	printf("%1.3f|%1.3f|%1.3f|%1.3f|\n" , m[2][0] , m[2][1] , m[2][2] , m[2][3] ) ;
	printf("%1.3f|%1.3f|%1.3f|%1.3f|\n" , m[3][0] , m[3][1] , m[3][2] , m[3][3] ) ;
	printf("\n") ;

}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4& M) {
	Matrix4x4 results ;
	results = *this ;
	results = results.Mul ( M ) ;
	return results ;
}

Matrix4x4 Matrix4x4::operator = (const Matrix4x4& M) {
	memcpy ( this->m , M.m , sizeof(this->m) ) ;
	return *this ;
}

bool Matrix4x4::operator == (const Matrix4x4& M) {
	for (int i = 0; i < 4; ++i)
	    for (int j = 0; j < 4; ++j)
	        if (m[i][j] != M.m[i][j]) return false;
	return true ;
}

bool Matrix4x4::operator != (const Matrix4x4& M) {
	for (int i = 0; i < 4; ++i)
	    for (int j = 0; j < 4; ++j)
	        if (m[i][j] != M.m[i][j]) return true;
	return false;
}
