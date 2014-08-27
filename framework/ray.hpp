#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/glm.hpp>

struct Ray{

	Ray(glm::vec4 dir, glm::vec4 orig, int d)
	:direction(dir),origin(orig),depth(d){}

	glm::vec4 direction;
	glm::vec4 origin;
	int depth;

	glm::vec4 point_at(float t)const{

	}
};

#endif //BUW_RAY_HPP