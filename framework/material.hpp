#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

struct Material{


Material()
:ambient_color_(),diffuse_color_(),specular_color_(),specular_exp_(200.0f){}

Material(Color const& ambient, Color const& diffuse, Color const& specular, float const specular_exponent)
: ambient_color_(ambient), diffuse_color_(diffuse),specular_color_(specular), specular_exp_(specular_exponent){} 

Color ambient_color_;
Color diffuse_color_;
Color specular_color_;
float specular_exp_;

};

#endif //BUW_MATERIAL_HPP