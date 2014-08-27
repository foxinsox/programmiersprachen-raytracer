#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP

#include "color.hpp"
#include <glm/glm.hpp>

class Light{

public:
	Light(glm::vec3 pos, Color d_term, Color a_term);

	void position(glm::vec3 const& p);
	glm::vec3 position()const;
	void diff_term(Color const& c);
	Color diff_term()const;
	void amb_term(Color const& c);
	Color amb_term()const;



private:

	glm::vec3 position_;
	Color diff_term_;
	Color amb_term_;

};

#endif //BUW_LIGHT_HPP