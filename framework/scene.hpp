#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include <vector>
#include <map>
#include <memory>
#include "camera.hpp"
#include "shape.hpp"
#include "composite.hpp"
#include "material.hpp"
#include "light.hpp"

class Scene{

public:
Scene();

void add_camera(Camera const& camera);
std::map<std::string, Camera> cameras()const;
Camera get_camera(std::string const& camera_name) const;

void active_camera(std::string const& camera_name);
Camera active_camera() const;

void add_shape(std::shared_ptr<Shape> const& shape);

Composite root() const;

void add_light(Light const& light);
std::map<std::string, Light> lights()const;
Light get_light(std::string const& light_name) const;

void add_material(Material const& material);
Material get_material(std::string const& material_name) const;

std::shared_ptr<Shape> get_shape(std::string const& shape_name)const;

private:
Composite root_;
std::string active_camera_name;
std::map<std::string, Camera> cameras;
std::map<std::string, Light> lights;
std::map<std::string, Material> materials;



};

#endif //BUW_SCENE_HPP