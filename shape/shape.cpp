
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "Shape.h"

unsigned int Shape::nextshapeId = 1 ;

BBox Shape::WorldBound () const {
    return (*ObjectToWorld)(ObjectBound()) ;
}

bool Shape::CanIntersect () const {
    return true ;
}

bool Shape::Intersect ( const Ray& ray , float* tHit , float* rayEpsilon , DifferentialGeometry* dg ) const {
    printf ("Unimplemented Shape::Intersect() method called") ;
    return false ;
}

bool Shape::IntersectP ( const Ray& ray ) const {
    printf ("Unimplemented Shape::IntersectP() method called") ;
    return false ;
}

void Shape::Refine( vector<Reference<Shape> >& refined ) const {
    printf ("Unimplemented Shape::Refine() method called") ;
}

void Shape::GetShadingGeometry ( const Transform& obj2world , const DifferentialGeometry& dg , DifferentialGeometry* dgShading ) const {
    *dgShading = dg ;
}

float Shape::Area () const {
    printf ("Unimplemented Shape::Area() method called") ;
    return 0. ;
}
 