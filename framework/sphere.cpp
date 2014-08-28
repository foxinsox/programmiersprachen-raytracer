#include "sphere.hpp"


Sphere::Sphere(std::shared_ptr<Material> const& material)
: Shape(material){}

Intersection Sphere::intersect_with(Ray const& r) const{

	//koordinaten umrechnen
	auto ray = world_to_object_ * r;

// solve the square eq
	double a = glm::dot(ray.direction, ray.direction);
	double b = 2.0f * glm::dot(ray.direction, ray.origin);
	double c = glm::dot(ray.origin, ray.origin) - 1.0;
// discriminant
	double disc = b * b - 4.0f * a * c;
// no solution for negative discrimant
	if (disc < 0) {
		return Intersection();
	}
	double discSqrt = glm::sqrt(disc);
	double a_inv = 1.0f / a;
	double t0 = (-b - discSqrt) * 0.5 * a_inv;
	double t1 = (-b + discSqrt) * 0.5 * a_inv;
// t0 should be smaller than t1
	if (t0 > t1) {
		std::swap(t0, t1);
	}
// ray parameter is negative = outside the view frustrum
	if (t1 < 0) {
		return Intersection();
	}
// if t0 is negative the parameter is t1
	double t;
	if (t0 < 0) {
		t = t1;
	} else {
		t = t0;
	}
	glm::vec3 normal = ray.point_at(t);
	//Normale vor Rückgabe in weltkoordinaten zurückrechnen
	glm::vec3 world_normal = glm::normalize(world_to_object_T_ * normal);
	return Intersection(material(),world_normal,t,true);

};