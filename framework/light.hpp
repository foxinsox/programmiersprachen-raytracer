#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP

#include "color.hpp"

class Light{

public:
	Light(glm::vec3 pos, Color d_term, Color a_term)
	:position_(pos),diff_term_(d_term),amb_term_(a_term){}

	void position(const glm::vec3 p);
	glm::vec3 position()const;
	void diff_term(const Color c);
	Color diff_term()const;
	void amb_term(const Color c);
	Color amb_term()const;



private:

	glm::vec3 position_;
	Color diff_term_;
	Color amb_term_;

};

#endif //BUW_LIGHT_HPP