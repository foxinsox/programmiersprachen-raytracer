#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include "intersection.hpp"
#include "shape.hpp"

class Sphere : public Shape{

public:
	Sphere(std::shared_ptr<Material> const& material);
	Intersection intersect_with(Ray const& r) const override;

	//center und radius werden einheitlich festgelegt und dann per scaling und translation angepasst.
};

#endif //BUW_SPHERE_HPP