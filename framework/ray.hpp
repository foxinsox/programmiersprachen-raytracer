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
};

#endif //BUW_RAY_HPP