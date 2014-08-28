#include "shape.hpp"

Shape::Shape()
:world_to_object_(),object_to_world_(),material_(),is_branch_(false){}

Shape::Shape(std::shared_ptr<Material> const& mat)
:world_to_object_(),object_to_world_(),material_(mat),is_branch_(false){}

glm::vec3 Shape::object_to_world (glm::vec3 const& object_vector) const
{
	return glm::normalize(object_to_world_T_ * object_vector);
}

glm::vec3 Shape::world_to_object (glm::vec3 const& world_vector) const
{
	return glm::normalize(world_to_object_T_ * world_vector);
}

void Shape::translate(glm::vec3 const& translationVector){
	auto m = glm::translate(glm::mat4(), translationVector);
	auto m_inv = glm::translate(glm::mat4(), -translationVector);
	object_to_world_ = m * object_to_world_;
	world_to_object_ = world_to_object_ * m_inv;
	object_to_world_T_ = glm::transpose(glm::mat3(object_to_world_));
	world_to_object_T_ = glm::transpose(glm::mat3(world_to_object_));
}

void Shape::rotate(float const radians, glm::vec3 const& axisVector){
	auto m = glm::rotate(glm::mat4(), radians, axisVector);
	auto m_inv = glm::rotate(glm::mat4(), -radians, axisVector);
	object_to_world_ = m * object_to_world_;
	world_to_object_ = world_to_object_ * m_inv;
	object_to_world_T_ = glm::transpose(glm::mat3(object_to_world_));
	world_to_object_T_ = glm::transpose(glm::mat3(world_to_object_));
}	


void Shape::scale(glm::vec3 const& scalingVector){
	auto m = glm::scale(glm::mat4(), scalingVector);
	auto m_inv = glm::scale(glm::mat4(), glm::vec3(1.0f / scalingVector.x, 1.0f / scalingVector.y, 1.0f / scalingVector.z));
	object_to_world_ = m * object_to_world_;
	world_to_object_ = world_to_object_ * m_inv;
	object_to_world_T_ = glm::transpose(glm::mat3(object_to_world_));
	world_to_object_T_ = glm::transpose(glm::mat3(world_to_object_));
}	


bool Shape::is_branch() const{
	return is_branch_;
}

void Shape::material(std::shared_ptr<Material> const& mat){
	material_ = mat;
}

std::shared_ptr<Material> Shape::material()const{
	return material_;
}

