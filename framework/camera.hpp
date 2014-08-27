#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Camera{

public:
	Camera();
	Camera(glm::vec3 const& eye_, glm::vec3 const& direction_, glm::vec3 const& up_, float fov_);
	Ray generate_ray_at(glm::ivec2 const& screen_coord, int depth)const;

	void translate(glm::vec3 const& translationVector);
	void rotate(float degrees, glm::vec3 const& axis);


private:
	glm::mat4 camera_to_world_;
	glm::mat4 world_to_camera_;
	glm::vec3 eye;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec2 fov;
	float depth;  //focal length. muss berechnet werden (im konstruktor?)
};

#endif //BUW_CAMERA_HPP