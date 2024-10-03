/* Start Header ************************************************************************/
/*!
\file		SageCameraImpl.cpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The source file containing the definition PIMPL class that delegate its
			functions to the private interface.

			It allow calls to be delegated to the private interface without exposing
			low level libraries such as GLFW.


			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "SageCameraImpl.hpp"
#include "SageCamera.hpp"
#include "glm/gtc/type_ptr.inl"

SageCamera::SageCameraImpl::SageCameraImpl() : camera() {}

SageCamera::SageCameraImpl::SageCameraImpl(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, int _camera_type) :
camera({ _position.GetX(), _position.GetY() }, { _view_rect_size.GetX(),_view_rect_size.GetY() }, 
	{ _orientation,0 }, static_cast<SageCameraInternal2D::InternalSageCameraType>(_camera_type)) {}


float const* SageCamera::SageCameraImpl::Get_Projection_View() const
{
	return glm::value_ptr(camera.Get_View_Projection_Matrix());
}

ToastBox::Vec2 SageCamera::SageCameraImpl::Get_Position() const
{
	return ToastBox::Vec2{ camera.Get_Position().x, camera.Get_Position().y };
}

ToastBox::Vec2 SageCamera::SageCameraImpl::Get_View_Rect_Size() const
{
	return ToastBox::Vec2{ camera.Get_View_Rect_Size().x, camera.Get_View_Rect_Size().y };
}

void SageCamera::SageCameraImpl::Move_Camera(ToastBox::Vec2 _move_vector, float _speed)
{
	camera.Move_Camera({ _move_vector.GetX(), _move_vector.GetY() }, _speed);
}

void SageCamera::SageCameraImpl::Update()
{
	camera.Update();
}


void SageCamera::SageCameraImpl::Init(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, ToastBox::Vec2 _orientation, SageCameraInternal2D::InternalSageCameraType _camera_type)
{
	camera.Init({ _position.GetX(), _position.GetY() }, { _view_rect_size.GetX(),_view_rect_size.GetY() }, 
		{ _orientation.GetX(),_orientation.GetY() }, _camera_type);

}

void* SageCamera::SageCameraImpl::Get_Cam()
{
	return camera.Get_Camera();
}