#include "box.hpp"

Box::Box(std::shared_ptr<Material> const& material)
: Shape(material){}

Intersection Box::intersect_with(Ray const& r) const{


	auto ray = world_to_object_ * r;

	double tMin, tMax, tyMin, tyMax, tzMin, tzMax;
	bool hit = 1;
	float param;

	//abchecken ob strahl trifft:
	tMin = ((-1)-ray.origin[0])/ray.direction[0];
	tMax = (1-ray.origin[0])/ray.direction[0];
	if (tMin > tMax) std::swap(tMin, tMax);
	tyMin = (-1-ray.origin[1])/ray.direction[1];
	tyMax = (1-ray.origin[1])/ray.direction[1];
	if (tyMin > tyMax) std::swap(tyMin, tyMax);
	if ((tMin > tyMax) || (tyMin > tMax)){
		hit = 0;
	}
	if (tyMin > tMin) tMin = tyMin;
	if (tyMax < tMax) tMax = tyMax;
	tzMin = (-1-ray.origin[2])/ray.direction[2];
	tzMax = (1-ray.origin[2])/ray.direction[2];
	if (tzMin > tzMax) std::swap(tzMin, tzMax);
	if ((tMin > tzMax) || (tzMin > tMax)){
		hit = 0;
	}
	if (tzMin > tMin) tMin = tzMin;
	if (tzMax < tMax) tMax = tzMax;
	// only if ray contains a tMin and tMax value
	// if ((tMin > ray.tMax) || (tMax < ray.tMin)){
	// 	hit = 0;	
	// } 
	// if (tMin > ray.tMin) ray.tMin = tMin;
	// if (tMax < ray.tMax) ray.tMax = tMax;

	//für robusteren und schnelleren code siehe:
	// http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-box-intersection/

	//negative schnittpunkte ignorieren
	//TODO: So funktioniert das nicht!
	if(tMin < 0) hit = 0;

	glm::vec3 scale( tMin, tMin, tMin );
    glm::mat4 m4( 1.0 ); // construct identity matrix
    m4[0].x = scale.x;
    m4[1].y = scale.y;
    m4[2].z = scale.z;


    glm::vec4 point = ray.origin+ray.direction*m4;
    Intersection i(point,mat,tMin,hit);
    return i;
}

