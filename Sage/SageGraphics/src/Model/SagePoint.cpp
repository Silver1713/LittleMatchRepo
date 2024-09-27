#include "SagePoint.hpp"


SagePoint::SagePoint() : position(), color(), size(0), point(nullptr), transformation_matrix()
{
}

SagePoint::SagePoint(glm::vec2 position, glm::vec4 color, float size)
{
	this->position = position;
	this->color = color;
	this->size = size;
	this->point = nullptr;
	this->transformation_matrix = glm::mat3(1.f);
}

void SagePoint::calculate_transform()
{
	glm::mat3 scaling = {
		size, 0, 0,
		0, size, 0,
		0, 0, 1
	};

	glm::mat3 translation = {
		1, 0, 0,
		0, 1, 0,
		position.x, position.y, 1
	};

	transformation_matrix = translation * scaling;
}

