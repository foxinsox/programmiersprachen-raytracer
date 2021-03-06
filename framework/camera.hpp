#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ray.hpp"
#include <iostream>

class Camera{

public:
	Camera();
	Camera(float const fov_degrees);
	Camera(float const fov_degrees,glm::vec3 const& eye_, glm::vec3 const& direction_, glm::vec3 const& up_);
	Ray generate_ray_at(glm::vec2 const& screen_coord, int const rayDepth)const;

	void translate(glm::vec3 const& translationVector);
	void rotate(float const degrees, glm::vec3 const& axis);
	



private:
	void calculate_transformationMatrix(glm::vec3 const& eye_, glm::vec3 const& direction_, glm::vec3 const& up_);
	glm::mat4 camera_to_world_;
	glm::mat4 world_to_camera_;
	glm::vec2 fov;
	float depth;  //focal length. muss berechnet werden
	friend std::ostream& operator<<(std::ostream& os, Camera const& cam){
		os << "Camera with depth = " << cam.depth <<"\n";
		return os;
	}
	
};

#endif //BUW_CAMERA_HPP