/* Start Header ************************************************************************/
/*!
\file		SageShader.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		This interface

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#ifndef SageViewport_HPP
#define SageViewport_HPP
#include <glm/fwd.hpp>
#include <glm/glm.hpp>


class SageViewport
{
	glm::vec2 position;
	glm::vec2 size;

	float default_world_bounds{ 10000.f };
	glm::mat3 vp_xform; // world to ndc

	


public:
	// Constructor
	SageViewport() : position(0.f), size(1.f), vp_xform(1.f) {}
	SageViewport(glm::vec2 pos, glm::vec2 size) : position(pos), size(size), vp_xform(1.f) {}



	void set_position(glm::vec2 pos);
	void set_dims(glm::vec2 size);

	glm::vec2 get_position() const;
	glm::vec2 get_dims() const;

	void set_default_world_bounds(float bounds);
	float get_default_world_bounds() const;

	glm::mat3& calculate_viewport_xform();
	glm::mat3 get_viewport_xform() const;

	void setViewport();
};

#endif