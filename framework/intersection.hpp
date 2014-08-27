#ifndef BUW_INTERSECTION_HPP
#define BUW_INTERSECTION_HPP

#include "material.hpp"

struct intersection{

Intersection(glm::vec3 p, glm::vec3 n)
: point(p),normal(n){}


glm::vec3 point;
glm::vec3 normal;

//TODO: pointer auf material einfügen


float t;
bool hit;


};

#endif //BUW_INTERSECTION_HPP