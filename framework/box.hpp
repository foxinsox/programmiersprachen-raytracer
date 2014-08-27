#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"

class Box : public Shape{

public:

Box(std::shared_ptr<Material> const& material);
Intersection intersect_with(Ray const& r) const override;
//einheitsbox wird angelegt und dann per scaling, translation und rotation individualisiert


};

#endif //BUW_BOX_HPP