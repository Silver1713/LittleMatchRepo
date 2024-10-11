
/* Start Header ************************************************************************/
/*!
\file		SagePoint.cpp
\title		Little Match
\author		Jay Lim Jun Xiang, jayjunxiang.lim, 2301335 (100%)
\par		jayjunxiang.lim@digipen.edu
\date		03 October 2024
\brief		This header file defines the SagePoint structure, which represents a
			point in a 2D rendering context. The structure includes attributes
			such as position, color, size, and a transformation matrix for
			rendering the point accurately within the viewport. It also contains
			a pointer to a SageModel, enabling association with a model for
			additional functionality.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "SagePoint.hpp"


SagePoint::SagePoint() : position(), color(), size(0), point(nullptr), transformation_matrix()
{
}

SagePoint::SagePoint(glm::vec2 _position, glm::vec4 _color, float _size)
{
	this->position = _position;
	this->color = _color;
	this->size = _size;
	this->point = nullptr;
	this->transformation_matrix = glm::mat3(1.f);
}

void SagePoint::Calculate_Transform()
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

