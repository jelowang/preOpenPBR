
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "disk.h"

Disk::Disk ( const Transform* o2w , const Transform* w2o , bool ro , float ht, float r, float ri, float pmax ) : Shape(o2w, w2o, ro) {
    height = ht;
    radius = r;
    innerRadius = ri;
    phiMax = toRadian(Clamp(pmax, 0.0f, 360.0f)) ;
}

Disk* Disk::Create ( const Transform* o2w , const Transform* w2o , bool reverseOrientation , Parameter* params ) {

	float height = params->getFloat ( "height" , 0.0f ) ;
    float radius = params->getFloat ( "radius" , 1.0f ) ;
    float innerRadius = params->getFloat ( "innerradius" , 0.0f ) ;
	float phimax = params->getFloat ( "phimax" , 360.0f ) ;
	Disk* disk = new Disk ( o2w , w2o , reverseOrientation , height , radius , innerRadius , phimax ) ;
	return disk ;
}

BBox Disk::ObjectBound () const {
    Point p1 = Point( -radius , -radius , height ) ;
    Point p2 = Point( radius ,  radius , height ) ;
	BBox box( p1 , p2 ) ;
	return box ;
}

bool Disk::Intersect ( const Ray& r , float* tHit , float* rayEpsilon , DifferentialGeometry* dg ) const {

    // Transform _Ray_ to object space
    Ray ray;
    (*WorldToObject)(r, &ray);

    // Compute plane intersection for disk
    if (fabsf(ray.d.z) < 1e-7) return false;
    float thit = (height - ray.o.z) / ray.d.z;
    if (thit < ray.mint || thit > ray.maxt)
        return false;

    // See if hit point is inside disk radii and $\phimax$
    Point phit = ray(thit);
    float dist2 = phit.x * phit.x + phit.y * phit.y;
    if (dist2 > radius * radius || dist2 < innerRadius * innerRadius)
        return false;

    // Test disk $\phi$ value against $\phimax$
    float phi = atan2f(phit.y, phit.x);
    if (phi < 0) phi += 2. * M_PI;
    if (phi > phiMax)
        return false;

    // Find parametric representation of disk hit
    float u = phi / phiMax;
    float R = sqrtf(dist2);
    float oneMinusV = ((R-innerRadius) /
                       (radius-innerRadius));
    float v = 1.f - oneMinusV;
    Vector dpdu(-phiMax * phit.y, phiMax * phit.x, 0.);
    Vector dpdv(phit.x, phit.y, 0.);
    dpdv = dpdv * (innerRadius - radius) / R;
    Normal dndu(0,0,0), dndv(0,0,0);

    // Initialize _DifferentialGeometry_ from parametric information
    const Transform &o2w = *ObjectToWorld;
    *dg = DifferentialGeometry(o2w(phit), o2w(dpdu), o2w(dpdv),
                               o2w(dndu), o2w(dndv), u, v, this);

    // Update _tHit_ for quadric intersection
    *tHit = thit;

    // Compute _rayEpsilon_ for quadric intersection
    *rayEpsilon = 5e-4f * *tHit;
    
	return true ;

}

bool Disk::IntersectP ( const Ray& r ) const {
    // Transform _Ray_ to object space
    Ray ray;
    (*WorldToObject)(r, &ray);

    // Compute plane intersection for disk
    if (fabsf(ray.d.z) < 1e-7) return false;
    float thit = (height - ray.o.z) / ray.d.z; 
    if (thit < ray.mint || thit > ray.maxt)
        return false;

    // See if hit point is inside disk radii and $\phimax$
    Point phit = ray(thit);
    float dist2 = phit.x * phit.x + phit.y * phit.y;
    if (dist2 > radius * radius || dist2 < innerRadius * innerRadius)
        return false;

    // Test disk $\phi$ value against $\phimax$
    float phi = atan2f(phit.y, phit.x);
    if (phi < 0) phi += 2. * M_PI;
    if (phi > phiMax)
        return false;
    return true;
}

float Disk::Area () const {
    return phiMax * 0.5f * (radius * radius - innerRadius * innerRadius) ;
}

Point Disk::Sample ( float u1 , float u2 , Normal* normal ) const {
	Point point ;
	return point ;
}