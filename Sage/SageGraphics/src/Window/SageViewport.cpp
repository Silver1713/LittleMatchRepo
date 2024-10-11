/* Start Header ************************************************************************/
/*!
\file		SageViewport.cpp
\title		Little Match
\author		Jay Lim Jun Xiang, jayjunxiang.lim, 2301335 (100%)
\par		jayjunxiang.lim@digipen.edu
\date		03 October 2024
\brief		This header file defines the SageViewport class, which manages the viewport
			for rendering graphics in a 2D space. It allows setting and retrieving the
			position and dimensions of the viewport.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "SageViewport.hpp"

#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>


void SageViewport::set_position(glm::vec2 _pos)
{
	position = _pos;

}

void SageViewport::set_dims(glm::vec2 _size)
{
	this->size = _size;
}

glm::vec2 SageViewport::get_position() const
{
	return position;
}

glm::vec2 SageViewport::get_dims() const
{
	return size;
}

glm::mat3& SageViewport::calculate_viewport_xform()
{
	// Set the viewport transformation matrix
	float r, l, t, b; //right, left, top, bottom
	r = size.x;
	l = 0.f;
	t = 0.f;
	b = size.y; 
	
	vp_xform = {
		2.f / (r - l), 0.f, 0.f,
		0, 2.f / (t - b), 0.f,
		-(r + l) / (r - l), -(t + b) / (t - b), 1.f
	};

	
	return vp_xform;

}


glm::mat3 SageViewport::get_viewport_xform() const
{
	return vp_xform;
}

void SageViewport::set_default_world_bounds(float bounds)
{
	default_world_bounds = bounds;
}

float SageViewport::get_default_world_bounds() const
{
	return default_world_bounds;
}


void SageViewport::setViewport()
{
	int x{ static_cast<int>(size.x) }, y{ static_cast<int>(size.y) };
	glViewport(static_cast<int>(position.x), static_cast<int>(position.y), x, y);
}
