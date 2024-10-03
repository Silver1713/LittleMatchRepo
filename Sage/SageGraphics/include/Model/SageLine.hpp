
/* Start Header ************************************************************************/
/*!
\file		SageLine.hpp
\title		Little Match
\author		Jay Lim Jun Xiang, jayjunxiang.lim, 2301335 (100%)
\par		jayjunxiang.lim@digipen.edu
\date		03 October 2024
\brief		This file defines the SageLine class, which represents a 2D line in the Little Match game. 
			The class includes functionality for specifying the line's start and end points, color, 
			and width. It also manages the transformation matrix for rendering the line appropriately 
			in the game world.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#pragma once

#include "SageModel.hpp"

#include "glm/glm.hpp"

class SageModel;

struct SageLine
{
	//starting point of line
	glm::vec2 start;
	//end point of line
	glm::vec2 end;
	//colour of line
	glm::vec4 color;
	//width of line
	float width;
	//pointer to sagemodel
	SageModel* line;

	glm::mat3 transformation_matrix;

	/*!*****************************************************************************

	  \brief
		Default constructor for the SageLine class.

	*******************************************************************************/
	SageLine();

	/*!*****************************************************************************

	  \brief
		 This constructor initializes the line's start and end points, color, and
		 width with the provided parameters.

	  \param _start
		A glm::vec2 representing the starting point of the line.

	  \param _end
		A glm::vec2 representing the ending point of the line.

	  \param _color
		A glm::vec4 representing the color of the line.

	  \param _width
		A float representing the width of the line.

	*******************************************************************************/
	SageLine(glm::vec2 _start, glm::vec2 _end, glm::vec4 _color = { 0,0,0,1 }, float _width=15.f);

	/*!*****************************************************************************

	  \brief
		Updates the line's transformation matrix by recalculating it.

	  This function calls the Calculate_Matrix method to update the transformation
	  matrix whenever the line needs to be updated.

	*******************************************************************************/
	void Update();

	/*!*****************************************************************************

	  \brief
		Calculates the transformation matrix for the line.

	*******************************************************************************/
	void Calculate_Matrix();

	/*!*****************************************************************************

	  \brief
		Updates the starting and ending points of the line and refreshes the vertex data.

	  \param _start
		A glm::vec2 representing the new starting point of the line.

	  \param _end
		A glm::vec2 representing the new ending point of the line.

	  This function updates the line's start and end points with the new values
	  and updates the corresponding vertex positions in the associated SageModel.
	  It also refreshes the vertex buffer in the GPU to reflect these changes.

	*******************************************************************************/
	void Update_Dist(glm::vec2 _start, glm::vec2 _end);
};
