#include "SageLine.hpp"
#include "glm/ext/matrix_transform.hpp"


SageLine::SageLine() : start(), end(), color(), width(0), line(nullptr), transformation_matrix()
{
}


SageLine::SageLine(glm::vec2 start, glm::vec2 end, glm::vec4 color, float width)
{
	this->start = start;
	this->end = end;
	this->color = color;
	this->width = width;
	this->line = nullptr;
	this->transformation_matrix = glm::mat3(1.f);


}

void SageLine::calculate_matrix()
{
	glm::vec2 direction = end - start;
	glm::vec2 center = (start + end) / 2.f;
	float angle = atan2(direction.y, direction.x);
	float length = glm::length(direction);

	glm::mat3 scaling = {
		length, 0, 0,
		0, 1.f,0,
		0,0,1

	};

	glm::mat3 rotation = {
		cos(angle), -sin(angle), 0,
		sin(angle), cos(angle), 0,
		0,0,1
	};

	glm::mat3 translation = {
		1,0,0,
		0,1,0,
		center.x, center.y, 1
	};

	transformation_matrix = translation * rotation * scaling;
}


void SageLine::update()
{
	calculate_matrix();
	
}








