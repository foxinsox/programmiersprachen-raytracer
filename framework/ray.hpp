#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/glm.hpp>
#include <iostream>

struct Ray{

	Ray(glm::vec3 dir, glm::vec3 orig, int d)
	:direction(dir),direction_reverse(1.0f / dir.x, 1.0f / dir.y, 1.0f / dir.z),origin(orig),depth(d){}

	glm::vec3 direction;
	glm::vec3 direction_reverse;
	glm::vec3 origin;
	int depth;

	glm::vec3 point_at(float t)const{
		return origin+direction*t;
	}

	//Operatorenüberladung, um glm::vec3 künftig einfacher mit mat4 verrechnen zu können.
	friend Ray operator*(glm::mat4 const& t, Ray const& ray)
	{
		return Ray(
			glm::vec3(t * glm::vec4(ray.direction, 0.0f)),
			glm::vec3(t * glm::vec4(ray.origin, 1.0f)),
			ray.depth
			);
	}

	friend std::ostream& operator<<(std::ostream& os, Ray const& r)
	{
		os << "(" << r.origin.x << "," << r.origin.y << "," << r.origin.z << ")";
		os << "(" << r.direction.x << "," << r.direction.y << "," << r.direction.z << ")\n";
		return os;
	}

};

#endif //BUW_RAY_HPP