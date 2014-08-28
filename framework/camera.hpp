#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Camera{

public:
	Camera();
	Camera(glm::vec3 const& eye_, glm::vec3 const& direction_, glm::vec3 const& up_, float fov_degrees);
	Ray generate_ray_at(glm::ivec2 const& screen_coord, int rayDepth)const;

	void translate(glm::vec3 const& translationVector);
	void rotate(float degrees, glm::vec3 const& axis);


private:
	void calculate_transformationMatrix(glm::vec3 const& eye_, glm::vec3 const& direction_, glm::vec3 const& up_);
	glm::mat4 camera_to_world_;
	glm::mat4 world_to_camera_;
	glm::vec2 fov;
	float depth;  //focal length. muss berechnet werden (im konstruktor?)
};

#endif //BUW_CAMERA_HPP