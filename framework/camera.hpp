#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Camera{

public:
	Camera();
	Camera(glm::vec3 const& eye_, glm::vec3 const& direction_, glm::vec3 const& up_, float fov_);
	Ray generate_ray_at(glm::ivec2 const& screen_coord, int depth)const;

private:

	
	glm::vec4 camera_to_world(glm::vec4 const& camera_vec)const;
	glm::mat4 camera_to_world_;
	glm::mat4 world_to_camera_;
	glm::vec3 eye;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec2 fov;
	float depth;
	void calculate_transformation(glm::vec3 const& eye, glm::vec3 const& direction, glm::vec3 const& up);
};

#endif //BUW_CAMERA_HPP