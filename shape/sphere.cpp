
//	'OpenPBR' prototype
//	A Light-Weighted Implementation of 
//	'Physically Based Renderer' According to <Physically Based Rendering From Theory to Implementation>
//	(C) Quantum Dynamics Lab.
//	Jelo 2016
//	http://tok.cc

#include "Sphere.h"

Sphere::Sphere(const Transform *o2w, const Transform *w2o, bool ro,
               float rad, float z0, float z1, float pm)
    : Shape(o2w, w2o, ro) {

    radius = rad;
    zmin = Clamp(min(z0, z1), -radius, radius) ;
    zmax = Clamp(max(z0, z1), -radius, radius) ;
    thetaMin = acosf(Clamp(zmin/radius, -1.f, 1.f)) ;
    thetaMax = acosf(Clamp(zmax/radius, -1.f, 1.f)) ;
    phiMax = toRadian(Clamp(pm, 0.0f, 360.0f)) ;

}

BBox Sphere::objectBound () const {
    return BBox(Point(-radius, -radius, zmin),
                Point( radius,  radius, zmax));
}

bool Sphere::Intersect ( const Ray& r , float *tHit , float* rayEpsilon , DifferentialGeometry* dg ) const {

	float phi ;
	Point phit ;
	Ray ray ;
	(*WorldToObject)(r,&ray) ;

	float A = ray.d.x*ray.d.x + ray.d.y*ray.d.y + ray.d.z*ray.d.z ;
	float B = 2.0f * ( ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z ) ;
	float C = ray.o.x*ray.o.x + ray.o.y*ray.o.y + ray.o.z*ray.o.z - radius*radius ;

    float t0, t1;

    if (!Quadratic ( A , B , C , &t0 , &t1 ) )
        return false ;

    if (t0 > ray.maxt || t1 < ray.mint)
        return false ;

    float thit = t0 ;
    if (t0 < ray.mint) {
        thit = t1 ;
        if (thit > ray.maxt) 
			return false ;
	}

    phit = ray(thit);
    if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius ;
    phi = atan2f(phit.y, phit.x) ;
    if (phi < 0.) phi += 2.f*M_PI ;

    if ((zmin > -radius && phit.z < zmin) ||
        (zmax <  radius && phit.z > zmax) || phi > phiMax) {
        if (thit == t1) return false;
        if (t1 > ray.maxt) return false;
        thit = t1;

        phit = ray(thit);
        if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius;
        phi = atan2f(phit.y, phit.x);
        if (phi < 0.) phi += 2.f*M_PI;
        if ((zmin > -radius && phit.z < zmin) ||
            (zmax <  radius && phit.z > zmax) || phi > phiMax)
            return false;
    }

    float u = phi / phiMax;
    float theta = acosf(Clamp(phit.z / radius, -1.f, 1.f));
    float v = (theta - thetaMin) / (thetaMax - thetaMin);

    float zradius = sqrtf(phit.x*phit.x + phit.y*phit.y);
    float invzradius = 1.f / zradius;
    float cosphi = phit.x * invzradius;
    float sinphi = phit.y * invzradius;
    Vector dpdu(-phiMax * phit.y, phiMax * phit.x, 0);
    Vector dpdv = Vector(phit.z * cosphi, phit.z * sinphi, -radius * sinf(theta)) * (thetaMax-thetaMin) ;

    Vector d2Pduu = Vector(phit.x, phit.y, 0) * -phiMax * phiMax ;
    Vector d2Pduv = Vector(-sinphi, cosphi, 0.) * (thetaMax - thetaMin) * phit.z * phiMax ;
    Vector d2Pdvv = Vector(phit.x, phit.y, phit.z) * -(thetaMax - thetaMin) * (thetaMax - thetaMin) ;

    float E = Dot(dpdu, dpdu);
    float F = Dot(dpdu, dpdv);
    float G = Dot(dpdv, dpdv);
    Vector N = Normalize(Cross(dpdu, dpdv));
    float e = Dot(N, d2Pduu);
    float f = Dot(N, d2Pduv);
    float g = Dot(N, d2Pdvv);

    float invEGF2 = 1.f / (E*G - F*F);
    Normal dndu = Normal(dpdu * (f*F - e*G) * invEGF2 + dpdv * (e*F - f*E) * invEGF2 );
    Normal dndv = Normal(dpdu * (g*F - f*G) * invEGF2 + dpdv * (f*F - g*E) * invEGF2 );

	const Transform &o2w = *ObjectToWorld ;
    *dg = DifferentialGeometry(o2w(phit), o2w(dpdu), o2w(dpdv),
                               o2w(dndu), o2w(dndv), u, v, this);

	*tHit = thit;

    *rayEpsilon = 5e-4f * *tHit;
    return true;

}

bool Sphere::IntersectP ( const Ray& r ) const {

    float phi;
    Point phit;

    Ray ray;
    (*WorldToObject)(r, &ray);

    float A = ray.d.x*ray.d.x + ray.d.y*ray.d.y + ray.d.z*ray.d.z;
    float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z);
    float C = ray.o.x*ray.o.x + ray.o.y*ray.o.y +
              ray.o.z*ray.o.z - radius*radius;

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
    if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius;
    phi = atan2f(phit.y, phit.x);
    if (phi < 0.) phi += 2.f*M_PI;

    if ((zmin > -radius && phit.z < zmin) ||
        (zmax <  radius && phit.z > zmax) || phi > phiMax) {
        if (thit == t1) return false;
        if (t1 > ray.maxt) return false;
        thit = t1;

        phit = ray(thit);
        if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius;
        phi = atan2f(phit.y, phit.x);
        if (phi < 0.) phi += 2.f*M_PI;
        if ((zmin > -radius && phit.z < zmin) ||
            (zmax <  radius && phit.z > zmax) || phi > phiMax)
            return false;
    }

    return true;

}

float Sphere::Area() const {
    return phiMax * radius * (zmax-zmin) ;
}