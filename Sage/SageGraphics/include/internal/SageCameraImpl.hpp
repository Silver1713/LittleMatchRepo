/* Start Header ************************************************************************/
/*!
\file		SageCameraImpl.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The PIMPL implementation of the SageCamera class that is used to facilitate calls to the
			private interface that implements the camera.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/


#ifndef SAGE_CAMERA_IMPL_HPP
#define SAGE_CAMERA_IMPL_HPP
#include "SageCamera.hpp"
#include "SageCameraInternal.hpp"
class SageCamera::SageCameraImpl
{
	SageCameraInternal2D camera;

public:
	SageCameraImpl();

	SageCameraImpl(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, int _camera_type);


	float const* Get_Projection_View() const;

	ToastBox::Vec2 Get_Position() const;

	ToastBox::Vec2 Get_View_Rect_Size() const;

	void MoveCamera(ToastBox::Vec2 _move_vector, float _speed);

	void Update();

	void Init(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, ToastBox::Vec2 _orientation, SageCameraInternal2D::InternalSageCameraType _camera_type);

	void* GetCam();
};

#endif