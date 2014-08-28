#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/glm.hpp>

struct Ray{

	Ray(glm::vec3 dir, glm::vec3 orig, int d)
	:direction(dir),origin(orig),depth(d){}

	glm::vec3 direction;
	glm::vec3 origin;
	int depth;

	glm::vec3 point_at(float t)const{
		return origin+direction*t;
	}

	//Operatorenüberladung, um glm::vec3 künftig einfacher mit mat4 verrechnen zu können.
	friend Ray operator*(glm::mat4 const& t, Ray const& ray)
	{
		return Ray(
			glm::vec3(t * glm::vec4(ray.origin, 1.0f)),
			glm::vec3(t * glm::vec4(ray.direction, 0.0f)),
			ray.depth
			);
	}
};

#endif //BUW_RAY_HPP