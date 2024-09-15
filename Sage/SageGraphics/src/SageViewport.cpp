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
	vp_xform = { 2 / size.x, 0,0,0,2 / size.y,0,0,0,1 };

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
	glViewport(static_cast<GLsizei>(position.x), position.y, size.x, size.y);
}







