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
/*!*****************************************************************************
	\brief
		Encapsulate a PIMPL camera object that calls the internal camera
		class.
*******************************************************************************/
class SageCamera::SageCameraImpl
{
	SageCameraInternal2D camera; //!< The internal camera object.

public:
	/*!*****************************************************************************
	\brief
		Request the internal class to be constructed.
	*******************************************************************************/
	SageCameraImpl();
	/*!*****************************************************************************
	\brief
		Request the internal class to be constructed with the given inputs from
		the public interface.
	\param _position
		The position of the camera
	\param _view_rect_size
		The view size
	\param _orientation
		The orientation of the camera
	\param _camera_type
		The camera type.
	*******************************************************************************/
	SageCameraImpl(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, int _camera_type);

	/*!*****************************************************************************
	\brief
		Get the vew projection matrix from the internal camera object.
		This function retrieve the view projection matrix from the camera object. It is
		calculated by concatenating the view matrix and the projection matrix.
		(view * projection)
	\return
		(float*) The pointer to an array containing the data for the projection
		view matrix.

	*******************************************************************************/
	float const* Get_Projection_View() const;
	/*!*****************************************************************************
	\brief
		Get the position of the internal camera object in world space coordinates.
	\return
		(Vec2) The position of the camera object in world space coordinates.

	*******************************************************************************/
	ToastBox::Vec2 Get_Position() const;
	/*!*****************************************************************************
	\brief
		Get the scale of the  internal camera view rectangle in world space coordinates.
	\return
		(Vec2) The view rectangle scale in world space.

	*******************************************************************************/
	ToastBox::Vec2 Get_View_Rect_Size() const;
	/*!*****************************************************************************
	\brief
		Moves the camera
		This function given the move vector and speed will translate the current
		camera object in the given vector by the given speed.
	\param _move_vector
		The vector to move the camera by.
	\param _speed
			The speed at which the camera will move.


	*******************************************************************************/
	void Move_Camera(ToastBox::Vec2 _move_vector, float _speed);
	/*!*****************************************************************************
	\brief
		Camera update's loop
		This function will update the camera object and it is called every frame in
		the game loop.

	*******************************************************************************/
	void Update();
	/*!*****************************************************************************
	\brief
		Initialize the camera object with the given parameters.
		This function will initalize the camera defining the data members with the
		values given in the parameters. This allow existing camera to be reinitialized
		with new values.
	\note This initialize the PIMPL class that will delegates calls to the
	internal class.
	\param _position
		The position of the camera in the game world.
	\param _view_rect_size
		The size of the camera view rectangle.
	\param _orientation
		The orientation of the camera in the game world.
	\param _camera_type
		The type of camera to be created. Default is SageCameraType::I_SAGE_ORTHO.
	*******************************************************************************/
	void Init(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, ToastBox::Vec2 _orientation, SageCameraInternal2D::InternalSageCameraType _camera_type);
	/*!*****************************************************************************
	\brief
		Get the pointer to the camera object.
	\return
		(void*) A typeless void pointer to the camera object.
	*******************************************************************************/
	void* Get_Cam();
};

#endif