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
	SageLine(glm::vec2 _start, glm::vec2 _end, glm::vec4 _color = { 0,0,0,1 }, float _width=15.f);

	void Update();

	void Calculate_Matrix();

	void Update_Dist(glm::vec2 _start, glm::vec2 _end);
};

#endif