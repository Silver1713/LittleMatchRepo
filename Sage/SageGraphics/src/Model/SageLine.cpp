
/* Start Header ************************************************************************/
/*!
\file		SageLine.cpp
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

#include "SageLine.hpp"
#include "glm/ext/matrix_transform.hpp"


SageLine::SageLine() : start(), end(), color(), width(0), line(nullptr), transformation_matrix()
{
}


SageLine::SageLine(glm::vec2 _start, glm::vec2 _end, glm::vec4 _color, float _width)
{
	this->start = _start;
	this->end = _end;
	this->color = _color;
	this->width = _width;
	this->line = nullptr;
	this->transformation_matrix = glm::mat3(1.f);


}

void SageLine::Calculate_Matrix()
{
	

	transformation_matrix = { 1.f };
}


void SageLine::Update()
{
	Calculate_Matrix();
	
}


void SageLine::Update_Dist(glm::vec2 _start, glm::vec2 _end)
{
	this->start = _start;
	this->end = _end;

	SageModel& model = *line;
	model.Get_Vertex_Positions()[0] = _start;
	model.Get_Vertex_Positions()[1] = _end;

	model.Update_Vtx_Buffer_GPU();

}









