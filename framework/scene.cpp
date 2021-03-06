#include "scene.hpp"

Scene::Scene()
:camera_(),root_(),lights_(){}



void Scene::camera(std::shared_ptr<Camera> const& camera){
	camera_ = camera;
};

std::shared_ptr<Camera>const& Scene::camera() {
	return camera_;
}

void Scene::add_light(Light const& light){
	lights_.push_back(light);
}
std::vector<Light> const& Scene::lights()const{
	return lights_;
}

void Scene::add_shape(std::shared_ptr<Shape> const& shape){
	root_.add_child(shape);
}
Composite const& Scene::root()const{
	return root_;
}