
/* Start Header ************************************************************************/
/*!
\file		SagePoint.hpp
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

#pragma once
#include <glm/glm.hpp>

class SageModel;

struct SagePoint
{
	//pos of point
	glm::vec2 position;
	//colour of point
	glm::vec4 color;
	//size of point
	float size;

	// transformation matrix for positioning and scaling
	glm::mat3 transformation_matrix;

	//pointer to sagemodel instance
	SageModel* point;

	/*!*****************************************************************************
	  \brief
		Default constructor for the SagePoint class.
	*******************************************************************************/
	SagePoint();

	/*!*****************************************************************************
	  \brief
		constructor for the SagePoint class.

	  \param _position
		A glm::vec2 representing the initial position of the point.

	  \param _color
		A glm::vec4 representing the color of the point (RGBA).

	  \param _size
		A float representing the size of the point.

	*******************************************************************************/
	SagePoint(glm::vec2 _position, glm::vec4 _color = { 0,0,0,1 }, float _size = 15.f);

	/*!*****************************************************************************
	  \brief
		Calculates the transformation matrix for the point based on its position and size..
	*******************************************************************************/
	void Calculate_Transform();
};
