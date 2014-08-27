#ifndef BUW_INTERSECTION_HPP
#define BUW_INTERSECTION_HPP

#include "material.hpp"


struct Intersection{

	Intersection()
	: point(),material(),ray_parameter(-1.0f),hit()	{}


	Intersection(std::shared_ptr<Material> const mat, glm::vec3 const& p, float t, bool hit_something)
	: point(p),material(mat),ray_parameter(t),hit(hit_something){}

	std::shared_ptr<Material> material;
	glm::vec3 point;
	float ray_parameter;
	bool hit;

};

#endif //BUW_INTERSECTION_HPP