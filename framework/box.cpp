#include "box.hpp"

Box::Box(std::shared_ptr<Material> const& material)
: Shape(material){}

Intersection Box::intersect_with(Ray const& r) const{

	//TODO: implementieren!!
	return Intersection();
}

