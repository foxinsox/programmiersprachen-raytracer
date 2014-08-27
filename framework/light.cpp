#include "light.hpp"

Light::Light(glm::vec3 pos, Color d_term, Color a_term)
:position_(pos),diff_term_(d_term),amb_term_(a_term){}

void Light::position(glm::vec3 const& p){
	position_ = p;
}

glm::vec3 Light::position()const{
	return position_;
}

void Light::diff_term(Color const& c){
	diff_term_ = c;
}

Color Light::diff_term()const{
	return diff_term_;
}

void Light::amb_term(Color const& c){
	amb_term_ = c;
}

Color Light::amb_term()const{
	return amb_term_;
}