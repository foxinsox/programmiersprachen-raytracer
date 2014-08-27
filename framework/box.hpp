#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"

class Box : public Shape{

public:

Box(glm::vec3 const& pMinimum, glm::vec3 const& pMaximum)
:pMin_(pMinimum),pMax_(pMaximum){}

glm::vec3 const pMin();
void pMin(glm::vec3 const& p);
glm::vec3 const pMax();
void pMax(glm::vec3 const& p);

Intersection intersect_with(Ray const& r) const override;


private:
glm::vec3 pMin_;
glm::vec3 pMax_;


};

#endif //BUW_BOX_HPP