#ifndef SAGE_POINT_HPP
#define SAGE_POINT_HPP
#include <glm/glm.hpp>

class SageModel;

struct SagePoint
{
	glm::vec2 position;
	glm::vec4 color;
	float size;

	glm::mat3 transformation_matrix;

	SageModel* point;


	SagePoint();
	SagePoint(glm::vec2 position, glm::vec4 color = { 0,0,0,1 }, float size = 15.f);

	void calculate_transform();
};

#endif 