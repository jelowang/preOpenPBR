
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Renderer From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "point.h"
#include "vector.h"
#include "geometry.h"

int main(int argc, char* argv[])
{
#if 0
	float t0 ;
	float t1 ;
	float radius = 30.1 ;
	Ray ray( Point(0.0,-50.0,0.0) , Normalize(Vector(1.0,0.0,0.0)) , 0.0 ) ;
	float A = ray.d.x*ray.d.x + ray.d.y*ray.d.y + ray.d.z*ray.d.z ;
	float B = 2.0f * ( ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z ) ;
	float C = ray.o.x*ray.o.x + ray.o.y*ray.o.y + ray.o.z*ray.o.z - radius*radius ;

	Quadratic(A,B,C,&t0,&t1) ;
#endif

	return 0;
}

