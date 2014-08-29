#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

#include "color.hpp"

struct Material{


	Material()
	:ambient_color_(),diffuse_color_(),specular_color_(),specular_exp_(200.0f){}

	Material(Color const& ambient, Color const& diffuse, Color const& specular, float const specular_exponent)
	: ambient_color_(ambient), diffuse_color_(diffuse),specular_color_(specular), specular_exp_(specular_exponent){} 

	Color ambient_color_;
	Color diffuse_color_;
	Color specular_color_;
	float specular_exp_;

	friend std::ostream& operator<<(std::ostream& os, Material const& m)
	{
		os << "  ambient color: (" << m.ambient_color_.r << "," << m.ambient_color_.g << "," << m.ambient_color_.b<<")";
		os << "  diffuse color: (" << m.diffuse_color_.r << "," << m.diffuse_color_.g << "," << m.diffuse_color_.b<<")";
		os << "  specular color: (" << m.specular_color_.r << "," << m.specular_color_.g << "," << m.specular_color_.b<<")";
		os << "  specular exponent: "<< m.specular_exp_;
		return os;
	}

};

#endif //BUW_MATERIAL_HPP