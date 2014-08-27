#include "shape.hpp"

Shape::Shape()
:world_to_object_(),object_to_world_(),material_(),is_branch_(false){}

glm::vec3 Shape::object_to_world (glm::vec3 const& object_vector) const
{
	return glm::normalize(object_to_world_T_ * object_vector);
}

glm::vec3 Shape::world_to_object (glm::vec3 const& world_vector) const
{
	return glm::normalize(world_to_object_T_ * world_vector);
}

void Shape::translate(glm::vec3 const& translationVector){
  // TODO: translation
}

void Shape::rotate(double const radians, glm::vec3 const& axisVector){
  // TODO: rotation around axis
}

void Shape::scale(glm::vec3 const& scalingVector){
  // TODO: scale
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

