#include "composite.hpp"

Composite::Composite()
:Shape(),children(){}

void Composite::add_child(std::shared_ptr<Shape> const& cld){
	children.push_back(cld);
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
	
//TODO: implementieren
//alle childs durchgehen und das niedrigste T verwenden...

//koordinaten umrechnen
	auto ray = world_to_object_ * r;
	Intersection i;
	
	return i;
}