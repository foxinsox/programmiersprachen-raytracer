#include "box.hpp"

Box::Box(std::shared_ptr<Material> const& material)
: Shape(material){}

Intersection Box::intersect_with(Ray const& r) const{

	//koordinaten in objektkoordinaten umrechnen
	auto ray = world_to_object_ * r;

	float tmin, tmax, tymin , tymax, tzmin, tzmax;


	//checkt t for x-Direction
	if (ray.direction.x >= 0.0f) {
		tmin = (-1.0f - ray.origin.x) * ray.direction_reverse.x;
		tmax = (1.0f - ray.origin.x) * ray.direction_reverse.x;
	} else {
		tmin = (1.0f - ray.origin.x) * ray.direction_reverse.x;
		tmax = (-1.0f - ray.origin.x) * ray.direction_reverse.x;
	}

	//check t for y-Direction
	if (ray.direction.y >= 0.0f) {
		tymin = (-1.0f - ray.origin.y) * ray.direction_reverse.y;
		tymax = (1.0f - ray.origin.y) * ray.direction_reverse.y;
	} else {
		tymin = (1.0f - ray.origin.y) * ray.direction_reverse.y;
		tymax = (-1.0f - ray.origin.y) * ray.direction_reverse.y;
	}

	//check for fail
	if ( (tmin > tymax) || (tymin > tmax) ) {
		return Intersection();
	}
	//compare t for smallest value
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	//check t for z-Direction
	if (ray.direction.z >= 0.0f) {
		tzmin = (-1.0f - ray.origin.z) * ray.direction_reverse.z;
		tzmax = (1.0f - ray.origin.z) * ray.direction_reverse.z;
	} else {
		tzmin = (1.0f - ray.origin.z) * ray.direction_reverse.z;
		tzmax = (-1.0f - ray.origin.z) * ray.direction_reverse.z;
	}
	//check for fail
	if ( (tmin > tzmax) || (tzmin > tmax) ) {
		return Intersection();
	}

	//compare t for smallest value
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	float t;
	if (tmin < 0.0f) {
		t = tmax;
	} else {
		t = tmin;
	}

	//ignore hits beyond camera view (fails)
	if (t < 0.0f) {
		return Intersection();
	}


	//calculate intersection_point
	auto p = ray.point_at(t);
	//p normalisieren
	glm::vec3 n_squared = p * p;

	//normale in schnittpunkt p berechnen;
	glm::vec3 normal;
	if (n_squared.x >= n_squared.y && n_squared.x >= n_squared.z) {
		if (p.x >= 0)
			normal = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	} else if (n_squared.y >= n_squared.x && n_squared.y >= n_squared.z) {
		if (p.y >= 0)
			normal = glm::vec3(0.0f, 1.0f, 0.0f);
		else
			normal = glm::vec3(0.0f, -1.0f, 0.0f);
	} else if (n_squared.z >= n_squared.x && n_squared.z >= n_squared.y) {
		if (p.z >= 0)
			normal = glm::vec3(0.0f, 0.0f, 1.0f);
		else
			normal = glm::vec3(0.0f, 0.0f, -1.0f);
	}

	//Normale vor Rückgabe in weltkoordinaten zurückrechnen
	glm::vec3 world_normal = glm::normalize(world_to_object_T_ * normal);
	

	return Intersection(material(),world_normal,t,true);

}

