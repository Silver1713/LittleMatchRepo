
/* Start Header ************************************************************************/
/*!
\file		SageViewport.hpp
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

#pragma once
#include <glm/fwd.hpp>
#include <glm/glm.hpp>


class SageViewport
{
	glm::vec2 position;
	glm::vec2 size;

	float default_world_bounds{ 10000.f };
	glm::mat3 vp_xform; // ortho projection matrix

	


public:
	// Constructor
	/*!*****************************************************************************
	  \brief
		Default constructor for the SageViewport class.

	  This constructor initializes the position of the viewport to (0, 0),
	  the size to (1, 1), and sets the viewport transformation matrix to the
	  identity matrix.

	*******************************************************************************/
	SageViewport() : position(0.f), size(1.f), vp_xform(1.f) {}


	/*!*****************************************************************************
	  \brief
		Parameterized constructor for the SageViewport class.

	  \param pos
		A glm::vec2 representing the initial position of the viewport.

	  \param size
		A glm::vec2 representing the initial dimensions (width and height) of the viewport.

	  This constructor initializes the position and size of the viewport with the
	  provided parameters and sets the viewport transformation matrix to the
	  identity matrix.

	*******************************************************************************/
	SageViewport(glm::vec2 pos, glm::vec2 size) : position(pos), size(size), vp_xform(1.f) {}


	/*!*****************************************************************************
	  \brief
		Sets the position of the viewport.

	  \param _pos
		A glm::vec2 representing the new position of the viewport.
	*******************************************************************************/
	void set_position(glm::vec2 pos);

	/*!*****************************************************************************
	  \brief
		Sets the dimensions of the viewport.

	  \param _size
		A glm::vec2 representing the new width and height of the viewport.
	*******************************************************************************/
	void set_dims(glm::vec2 size);

	/*!*****************************************************************************
	  \brief
		Retrieves the current position of the viewport.

	  \return
		A glm::vec2 representing the current position of the viewport.
	*******************************************************************************/
	glm::vec2 get_position() const;

	/*!*****************************************************************************
	  \brief
		Retrieves the current dimensions of the viewport.

	  \return
		A glm::vec2 representing the current width and height of the viewport.
	*******************************************************************************/
	glm::vec2 get_dims() const;

	/*!*****************************************************************************
	  \brief
		Sets the default world bounds for the viewport.

	  \param bounds
		A float representing the default bounds of the world.
	*******************************************************************************/
	void set_default_world_bounds(float bounds);

	/*!*****************************************************************************
	  \brief
		Retrieves the default world bounds for the viewport.

	  \return
		A float representing the default bounds of the world.
	*******************************************************************************/
	float get_default_world_bounds() const;

	/*!*****************************************************************************
	  \brief
		Calculates and sets the viewport transformation matrix.

	  \return
		A reference to a glm::mat3 representing the viewport transformation matrix.
	*******************************************************************************/
	glm::mat3& calculate_viewport_xform();

	/*!*****************************************************************************
	  \brief
		Retrieves the current viewport transformation matrix.

	  \return
		A glm::mat3 representing the current viewport transformation matrix.
	*******************************************************************************/
	glm::mat3 get_viewport_xform() const;

	/*!*****************************************************************************
	  \brief
		Configures the OpenGL viewport based on the current position and dimensions.

	  This function sets the OpenGL viewport to match the current position and size
	  of the viewport.
	*******************************************************************************/
	void setViewport();
};
