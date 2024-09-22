#ifndef SAGE_LINE_HPP
#define SAGE_LINE_HPP

#include "SageModel.hpp"

#include "glm/glm.hpp"

class SageModel;

struct SageLine
{
	glm::vec2 start;
	glm::vec2 end;
	glm::vec4 color;

	float width;

	SageModel* line;

	glm::mat3 transformation_matrix;

	SageLine();
	SageLine(glm::vec2 start, glm::vec2 end, glm::vec4 color = { 0,0,0,1 }, float width=15.f);

	void update();

	void calculate_matrix();
};





#endif