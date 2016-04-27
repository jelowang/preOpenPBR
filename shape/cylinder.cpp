
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "cylinder.h"

Cylinder::Cylinder ( const Transform* o2w , const Transform* w2o , bool ro , float rad , float z0 , float z1 , float pmax ) : Shape(o2w, w2o, ro){
	this->radius = rad ;
	this->zmin = min ( z0 , z1 ) ;
	this->zmax = max ( z0 , z1 ) ;
	this->phiMax = toRadian ( Clamp ( pmax , 0.0f , 360.0f) ) ; 
}

Cylinder::~Cylinder () {
}

Cylinder* Cylinder::Create ( const Transform* o2w , const Transform* w2o , bool reverseOrientation , Parameter* params ) {
	Cylinder* cylinder = 0 ;
	float rad = params->getFloat("radius", 1.0f );
    float z0 = params->getFloat("zmin", -1.0f );
    float z1 = params->getFloat("zmax", 1.0f );
    float pmax = params->getFloat("phimax", 360.0f );
	cylinder = new Cylinder ( o2w , w2o , reverseOrientation , rad , z0 , z1 , pmax ) ;
    return cylinder ;
}

BBox Cylinder::ObjectBound () const {
    Point p1 = Point( -radius , -radius , zmin ) ;
    Point p2 = Point( radius ,  radius , zmax ) ;
	BBox box( p1 , p2 ) ;
	return box ;
}

bool Cylinder::Intersect ( const Ray& r , float* tHit , float* rayEpsilon , DifferentialGeometry* dg ) const {
    float phi;
    Point phit;
    Ray ray;
    (*WorldToObject)(r, &ray);

    float A = ray.d.x*ray.d.x + ray.d.y*ray.d.y;
    float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y);
    float C = ray.o.x*ray.o.x + ray.o.y*ray.o.y - radius*radius;

    float t0, t1;
    if (!Quadratic(A, B, C, &t0, &t1))
        return false;

    if (t0 > ray.maxt || t1 < ray.mint)
        return false;
    float thit = t0;
    if (t0 < ray.mint) {
        thit = t1;
        if (thit > ray.maxt) return false;
    }

    phit = ray(thit);
    phi = atan2f(phit.y, phit.x);
    if (phi < 0.) phi += 2.f*M_PI;

    if (phit.z < zmin || phit.z > zmax || phi > phiMax) {
        if (thit == t1) return false;
        thit = t1;
        if (t1 > ray.maxt) return false;
        phit = ray(thit);
        phi = atan2f(phit.y, phit.x);
        if (phi < 0.) phi += 2.f*M_PI;
        if (phit.z < zmin || phit.z > zmax || phi > phiMax)
            return false;
    }

    float u = phi / phiMax;
    float v = (phit.z - zmin) / (zmax - zmin);

    Vector dpdu(-phiMax * phit.y, phiMax * phit.x, 0);
    Vector dpdv(0, 0, zmax - zmin);

 
    Vector d2Pduu = -phiMax * phiMax * Vector(phit.x, phit.y, 0);
    Vector d2Pduv(0, 0, 0), d2Pdvv(0, 0, 0);

    float E = Dot(dpdu, dpdu);
    float F = Dot(dpdu, dpdv);
    float G = Dot(dpdv, dpdv);
    Vector N = Normalize(Cross(dpdu, dpdv));
    float e = Dot(N, d2Pduu);
    float f = Dot(N, d2Pduv);
    float g = Dot(N, d2Pdvv);

    float invEGF2 = 1.f / (E*G - F*F);
    Normal dndu = Normal((f*F - e*G) * invEGF2 * dpdu +
                         (e*F - f*E) * invEGF2 * dpdv);
    Normal dndv = Normal((g*F - f*G) * invEGF2 * dpdu +
                         (f*F - g*E) * invEGF2 * dpdv);

    const Transform &o2w = *ObjectToWorld;
    *dg = DifferentialGeometry(o2w(phit), o2w(dpdu), o2w(dpdv),
                               o2w(dndu), o2w(dndv), u, v, this);

    *tHit = thit;

    *rayEpsilon = 5e-4f * *tHit;
    return true;
}

bool Cylinder::IntersectP ( const Ray& r ) const {
    float phi;
    Point phit;
    Ray ray;
    (*WorldToObject)(r, &ray);

    float A = ray.d.x*ray.d.x + ray.d.y*ray.d.y;
    float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y);
    float C = ray.o.x*ray.o.x + ray.o.y*ray.o.y - radius*radius;

    float t0, t1;
    if (!Quadratic(A, B, C, &t0, &t1))
        return false;

    if (t0 > ray.maxt || t1 < ray.mint)
        return false;
    float thit = t0;
    if (t0 < ray.mint) {
        thit = t1;
        if (thit > ray.maxt) return false;
    }

    phit = ray(thit);
    phi = atan2f(phit.y, phit.x);
    if (phi < 0.) phi += 2.f*M_PI;

    if (phit.z < zmin || phit.z > zmax || phi > phiMax) {
        if (thit == t1) return false;
        thit = t1;
        if (t1 > ray.maxt) return false;

        phit = ray(thit);
        phi = atan2f(phit.y, phit.x);
        if (phi < 0.) phi += 2.f*M_PI;
        if (phit.z < zmin || phit.z > zmax || phi > phiMax)
            return false;
    }
    return true;
}

float Cylinder::Area () const {
    return (zmax-zmin) * phiMax * radius ;
}

Point Cylinder::Sample ( float u1 , float u2 , Normal* normal ) const {
    float z = Lerp(u1, zmin, zmax);
    float t = u2 * phiMax;
    Point p = Point(radius * cosf(t), radius * sinf(t), z);
    *normal = Normalize((*ObjectToWorld)(Normal(p.x, p.y, 0.)));
    if (reverseOrientation) *normal *= -1.f ;
    return (*ObjectToWorld)(p);
}