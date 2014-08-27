#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP

class Composite : public Shape{

public:
	Composite();

	void add_child(std::shared_ptr<Shape> cld);
	void remove_child(std::shared_ptr<Shape> cld);

	void translate(glm::vec3 const& t) override;
	void scale(glm::vec3 const& s) override;
	void rotate(double const radians, glm::vec3 const& axis) override;

	Intersection intersect_with(Ray const& r) const override;

private:
	std::vector<std::shared_ptr<Shape>> children;
};

#endif //BUW_COMPOSITE_HPP