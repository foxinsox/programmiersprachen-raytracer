#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <glm/glm.hpp>
#include "intersection.hpp"
#include "material.hpp"

class Shape{

public:
	Shape();

	virtual Intersection intersect_with(Ray const& r) const = 0;

	glm::vec3 object_to_world (glm::vec3 const& object_vector) const;
	glm::vec3 world_to_object (glm::vec3 const& world_vector) const;

	void translate(glm::vec3 const& translationVector);
	void rotate(double const radians, glm::vec3 const& axisVector);
	void scale(glm::vec3 const& scalingVector);

	bool is_branch() const;

	void material(std::shared_ptr<Material> const mat);
	std::shared_ptr<Material> material() const;

private:
	glm::mat4 world_to_object_;
	glm::mat4 object_to_world_;
	Material material_;

protected:
	bool is_branch_;

};

#endif //BUW_SHAPE_HPP