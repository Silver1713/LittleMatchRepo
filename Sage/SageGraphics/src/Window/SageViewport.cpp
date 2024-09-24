#include "SageViewport.hpp"

#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>


void SageViewport::set_position(glm::vec2 pos)
{
	position = pos;

}

void SageViewport::set_dims(glm::vec2 size)
{
	this->size = size;
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
	float r, l, t, b;
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







