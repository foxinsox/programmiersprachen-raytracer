#include "sphere.hpp"


Sphere::Sphere(std::shared_ptr<Material> const& material)
: Shape(material){}

Intersection Sphere::intersect_with(Ray const& r) const{

	Intersection i;
	return i;
};