#include "camera.hpp"


Camera::Camara()
: depth(1),camera_to_world_(),world_to_camera_(){}

Camera::Camera(glm::vec3 const& eye_, glm::vec3 const& direction_, glm::vec3 const& up_, float fov_degrees)
: depth(1.0f / (2.0f * std::tan(fov_degrees / 360.0f * M_PI))),camera_to_world_(),world_to_camera_(){}
{
	calculate_transformationMatrix(eye_,direction_,up_);
}

void Camera::calculate_transformationMatrix(glm::vec3 const& eye_, glm::vec3 const& direction_, glm::vec3 const& up_){
	auto u = glm::normalize(glm::cross(direction_, up_));
	auto v = glm::normalize(glm::cross(u, direction_));
	auto n = glm::normalize(direction_);
	camera_to_world_[0] = glm::vec4(u, 0.0f);
	camera_to_world_[1] = glm::vec4(v, 0.0f);
	camera_to_world_[2] = glm::vec4(-n, 0.0f);
	camera_to_world_[3] = glm::vec4(eye_, 1.0f);
	world_to_camera_ = glm::inverse(camera_to_world_);
};


Ray Camera::generate_ray(glm::ivec2 const& screen_coord, int rayDepth) const{
	glm::vec3 origin(0.0f, 0.0f, 0.0f);
	glm::vec3 direction(glm::vec3(screen_coord.x - 0.5, screen_coord.y - 0.5, -depth) - origin);
	Ray r = camera_to_world_ * Ray(origin, direction, rayDepth);
	r.direction = glm::normalize(r.direction);
	return r;
}

void Camera::translate(glm::vec3 const& translationVector){
	auto m = glm::translate(glm::mat4(), translationVector);
	camera_to_world_ = m * camera_to_world_;
	world_to_camera_ = world_to_camera_ * m;
}

void Camera::rotate(float degrees, glm::vec3 const& axis){
	//von grad in rad umrechnen:
	float rad = (degrees / 360.0f * M_PI);

	auto m = glm::rotate(glm::mat4(), rad, axis);
	camera_to_world_ = m * camera_to_world_;
	world_to_camera_ = world_to_camera_ * m;
}