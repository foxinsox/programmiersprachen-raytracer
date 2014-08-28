#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "intersection.hpp"
#include "material.hpp"
#include "ray.hpp"

class Shape{

public:
	Shape();
	Shape(std::shared_ptr<Material> const& mat);

	virtual Intersection intersect_with(Ray const& r) const = 0;

	glm::vec3 object_to_world (glm::vec3 const& object_vector) const;
	glm::vec3 world_to_object (glm::vec3 const& world_vector) const;

	virtual void translate(glm::vec3 const& translationVector);
	virtual void rotate(float const radians, glm::vec3 const& axisVector);
	virtual void scale(glm::vec3 const& scalingVector);

	bool is_branch() const;

	void material(std::shared_ptr<Material> const& mat);
	std::shared_ptr<Material> material() const;

protected:
	glm::mat4 world_to_object_;
	glm::mat4 object_to_world_;
	// transposed transformations
	glm::mat3 world_to_object_T_;
	glm::mat3 object_to_world_T_;


	std::shared_ptr<Material> material_;

	bool is_branch_;

};

#endif //BUW_SHAPE_HPP