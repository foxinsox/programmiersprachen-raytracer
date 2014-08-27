#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include <vector>
#include "camera.hpp"
#include "shape.hpp"
#include "composite.hpp"
#include "light.hpp"

class Scene{

public:
	Scene();

	void camera(Camera const& camera);
	Camera const& camera() const;

	void add_light(Light const& light);
	std::vector<Light> const& lights()const;

	void add_shape(std::shared_ptr<Shape> const& shape);
	Composite const& root() const;


private:
	Camera camera_;
	Composite root_;
	std::vector<Light> lights_;
	
};

#endif //BUW_SCENE_HPP