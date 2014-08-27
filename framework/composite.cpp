#include "composite.hpp"

Composite::Composite()
:children(){}

void Composite::add_child(std::shared_ptr<Shape> const& cld){
	children.push_back(cld);
}

void Composite::remove_child(std::shared_ptr<Shape>const& cld){
	std::vector<std::shared_ptr<Shape>>::iterator it;

	it = find (children.begin(), children.end(), cld);
	if (it != children.end()){ 
		children.erase (it);
	}
}

void Composite::translate(glm::vec3 const& t){
	Shape::translate(t);
}

void Composite::scale(glm::vec3 const& s){
	Shape::scale(s);
}

void Composite::rotate(float const radians, glm::vec3 const& axis){
	Shape::rotate(radians, axis);
}

Intersection Composite::intersect_with(Ray const& r) const{
	Intersection i;

	//TODO: implementieren!!
	return i;
}