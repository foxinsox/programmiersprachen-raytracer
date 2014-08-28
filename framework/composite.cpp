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
	
//alle childs durchgehen und das niedrigste T verwenden...
//koordinaten umrechnen

	auto ray = world_to_object_ * r;



	float min_t = 9999.0f;  //TODO: automatisieren bzw. globalisieren
	Intersection i;
	for (auto const& child: children) {
		//if (child->intersect_bbox(ray)) {
		auto current_i = child->intersect_with(ray);
		if (current_i.hit && current_i.ray_parameter > 0 && current_i.ray_parameter < min_t) {
			i = current_i;
			min_t = current_i.ray_parameter;
		}
		//}
	}
	if (i.hit) {
		//Normale vor Rückgabe in weltkoordinaten zurückrechnen
		i.point = glm::normalize(world_to_object_T_ * i.point);
	}

	return i;
}