#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#import <glm/glm.hpp>
#import "ray.hpp"

class Camera{

public:
	Camera();
	Camera(glm::vec3 const& eye, glm::vec3 const& direction, glm::vec3 const& up, float fov_);
	Ray generate_ray_at(glm::ivec2 const& screen_coord, int depth)const;

private:

	void calculate_transformation(glm::vec3 const& eye, glm::vec3 const& direction, glm::vec3 const& up);
	glm::vec4 camera_to_world(glm::vec4 const& camera_vec)const;
	glm::mat4 camera_to_world;
	float depth;
};

#endif //BUW_CAMERA_HPP