/* Start Header ************************************************************************/
/*!
\file		SageCameraInternal.cpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The source file containing the definition of the internal class that
			manage the camera, and provide function for creation and manipulation of the view.

			It interact with low level API such as GLFW.


			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "SageCameraInternal.hpp"

#include <iostream>
#include <ostream>


#include "SageHelper.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


void SageCameraInternal2D::Init(glm::vec2 _position, glm::vec2 _view_rect_size, glm::vec2 _orientation, InternalSageCameraType _camera_type)
{
	(_camera_type);
	position = _position;
	view_rect_size = _view_rect_size;
	orientation = _orientation;
	zoom = 1.0f;

	

	
	
	Calculate_Camera_Matrix();
}

void SageCameraInternal2D::Calculate_Camera_Matrix()
{
	// Calculate the up and right vectors
	up_vec = glm::vec2(-glm::sin(orientation.x), glm::cos(orientation.x));
	right_vec = glm::vec2(glm::cos(orientation.x), glm::sin(orientation.x));

	// Calculate the view matrix
	view_matrix = {
	right_vec.x, up_vec.x, 0.f,
	right_vec.y,    up_vec.y,    0.f,
	glm::dot(-right_vec, position),glm::dot(-up_vec, position),1
	};


	

	// Calculate the projection matrix


	float r, l, t, b;
	r = position.x + view_rect_size.x / 2.f;
	l = position.x -view_rect_size.x/2.f;
	t = position.y +view_rect_size.y/2.f;
	b = position.y -view_rect_size.y/2.f;

	projection_matrix = {
		2.f / (r - l), 0.f, 0.f,
		0, 2.f / (t - b), 0.f,
		-(r + l) / (r - l), -(t + b) / (t - b), 1.f
	};

	
	

	// Calculate the view projection matrix
	view_projection_matrix = projection_matrix * view_matrix;
	
}


void SageCameraInternal2D::Move_Camera(glm::vec2 _move_vector, float speed)
{
	position += _move_vector * (speed * static_cast<float>(SageHelper::delta_time));
	std::cout << "camera: "  << position.x << " " << position.y << std::endl;
}

void SageCameraInternal2D::Set_Position(glm::vec2 _position)
{
	position = _position;
}


void SageCameraInternal2D::Set_View_Rect_Size(glm::vec2 _view_rect_size)
{
	view_rect_size = _view_rect_size;
}

void SageCameraInternal2D::Set_Orientation(glm::vec2 _orientation)
{
	orientation = _orientation;
}

void SageCameraInternal2D::Exit()
{
	std::cout << "Exiting Camera" << std::endl;
}

void SageCameraInternal2D::Update()
{
	Calculate_Camera_Matrix();
}


SageCameraInternal2D::SageCameraInternal2D() : position({ 0,0 }), view_rect_size({ 0,0 }), orientation({ 0,0 }), zoom(1.0f), up_vec{1,0}, right_vec{0,1}
{
	aspect_ratio = static_cast<float>(SageHelper::WINDOW_WIDTH) / static_cast<float>(SageHelper::WINDOW_HEIGHT);
	
}


SageCameraInternal2D::SageCameraInternal2D(glm::vec2 _position, glm::vec2 _view_rect_size, glm::vec2 _orientation, InternalSageCameraType _camera_type)
{
	Init(_position, _view_rect_size, _orientation, _camera_type);
}


glm::vec2 SageCameraInternal2D::Get_Orientation() const
{
	return orientation;
}

glm::vec2 SageCameraInternal2D::Get_Position() const
{
	return position;
}

glm::mat3 SageCameraInternal2D::Get_Projection_Matrix() const
{
	return projection_matrix;
}

glm::mat3 SageCameraInternal2D::Get_View_Matrix() const
{
	return view_matrix;
}

glm::mat3 const& SageCameraInternal2D::Get_View_Projection_Matrix() const
{
	return view_projection_matrix;
}

glm::vec2 SageCameraInternal2D::Get_View_Rect_Size() const
{
	return view_rect_size;
}
void* SageCameraInternal2D::Get_Camera()
{
	return this;
}


