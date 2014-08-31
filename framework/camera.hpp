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

	friend std::ostream& operator<< (std::ostream& os, glm::vec3 const& vec) {
		os << "{" 
		<< vec.x << " " << vec.y << " "<< vec.z 
		<< "}";
		return os;
	}

	friend std::ostream& operator<< (std::ostream& os, glm::vec2 const& vec) {
		os << "{" 
		<< vec.x << " " << vec.y
		<< "}";
		return os;
	}

	// friend std::ostream& operator<< (std::ostream& os, glm::mat4 const& m) {
	// 	os <<m[0][0]<<","<<m[0][1]<<","<<m[0][2]<<","<<m[0][3]<<"\n";
	// 	os <<m[1][0]<<","<<m[1][1]<<","<<m[1][2]<<","<<m[1][3]<<"\n";
	// 	os <<m[2][0]<<","<<m[2][1]<<","<<m[2][2]<<","<<m[2][3]<<"\n";
	// 	os <<m[3][0]<<","<<m[3][1]<<","<<m[3][2]<<","<<m[3][3]<<"\n";
	// 	return os;
	// }
	
};

#endif //BUW_CAMERA_HPP