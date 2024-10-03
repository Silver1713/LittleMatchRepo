/* Start Header ************************************************************************/
/*!
\file		SageCamera.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The public interface containing the SageCamera class that contains methods and
			data to facilitate creation and manipulation of a camera object.


			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#ifndef SAGE_CAMERA_HPP
#define SAGE_CAMERA_HPP
#include <memory>
#include "Matrix3x3.h"
#include "Vector2.h"



/*!*****************************************************************************
	\brief
		Encapsulate a camera object in the rendering engine. Allowing for manipulation
		and creation of camera object in the game world.
*******************************************************************************/
class SageCamera {

	//!< Camera position and size.
	ToastBox::Vec2 position, rect_size;

	float aspect_ratio; //!< Aspect ratio
	ToastBox::Matrix3x3 view_matrix, //!< View matrix
		projection_matrix, //!< Projection matrix
		view_projection_matrix; //!< View projection matrix

	class SageCameraImpl; //!< Forward declaration of the implementation class
	std::unique_ptr<SageCameraImpl> impl; //!< Pointer to the implementation class

public:
	/*!*****************************************************************************
	\brief
		An enum class that represent the type of camera that can be created.
	*******************************************************************************/
	enum class SageCameraType
	{
		SAGE_ORTHO, //!< Orthographic camera
		SAGE_PERSP //!< Perspective camera, this is not implemented.
	};
	float zoom; //!< Zoom level
	float orientation; //!< Orientation of the camera


	/*!*****************************************************************************
	\brief
		Default Constructor for the camera object.
		This constructor intialize the camera object with default values.
	
	*******************************************************************************/
	SageCamera();
	/*!*****************************************************************************
	\brief
		Overloaded Constructor for the camera object.
		This function initialize the camera object with the given parameters. The
		last parameter is optional and defaults to SageCameraType::SAGE_ORTHO.

	\param _position
		The position of the camera in the game world.

	\param _view_rect_size
		The size of the camera view rectangle.
	\param _orientation
		The orientation of the camera in the game world.
	\param _camera_type
		The type of camera to be created. Default is SageCameraType::SAGE_ORTHO.

	*******************************************************************************/
	SageCamera(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, SageCameraType _camera_type = SageCameraType::SAGE_ORTHO);

	/*!*****************************************************************************
	\brief
		Copy Constructor for the camera object.
		This constructor allow for the creation of a new camera object from an existing
		camera object.
	\param _camera
		The camera object to be copied.

	*******************************************************************************/
	SageCamera(const SageCamera&);

	/*!*****************************************************************************
	\brief
		Move Constructor for the camera object.
		The move constructor will move the pointer to the implementation class from the
		input class to the curent object.
	\param _camera
		The camera object to be moved.

	*******************************************************************************/
	SageCamera(SageCamera&&) noexcept;
	/*!*****************************************************************************
	\brief
		Destructor for the camera class
		This ensures that the memory allocated for the camera object is deallocated

	*******************************************************************************/
	~SageCamera();

	/*!*****************************************************************************
	\brief
		Initialize the camera object with the given parameters.
		This function will initalize the camera defining the data members with the
		values given in the parameters. This allow existing camera to be reinitialized
		with new values.
	\param _position
		The position of the camera in the game world.
	\param _view_rect_size
		The size of the camera view rectangle.
	\param _orientation
		The orientation of the camera in the game world.
	\param _camera_type
		The type of camera to be created. Default is SageCameraType::SAGE_ORTHO.

	*******************************************************************************/
	void init(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, SageCameraType _camera_type = SageCameraType::SAGE_ORTHO);

	/*!*****************************************************************************
	\brief
		Camera update's loop
		This function will update the camera object and it is called every frame in
		the game loop.

	*******************************************************************************/
	void update();

	/*!*****************************************************************************
	\brief
		Get the vew projection matrix from the current camera object.
		This function retrieve the view projection matrix from the camera object. It is
		calculated by concatenating the view matrix and the projection matrix.
		(view * projection)
	\return
		(Matrix3x3) The view projection matrix of the camera object.

	*******************************************************************************/
	ToastBox::Matrix3x3 Get_Projection_View_Matrix();
	/*!*****************************************************************************
	\brief
		Get the position of the camera object in world space coordinates.
	\return
		(Vec2) The position of the camera object in world space coordinates.

	*******************************************************************************/
	ToastBox::Vec2 Get_Position();
	/*!*****************************************************************************
	\brief
		Get the scale of the camera view rectangle in world space coordinates.
	\return
		(Vec2) The view rectangle scale in world space.

	*******************************************************************************/
	ToastBox::Vec2 Get_View_Rect_Size();

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
		Get the pointer to the camera object.
	\return
		(void*) A typeless void pointer to the camera object.

	*******************************************************************************/
	void* Get_Camera();


	/*!*****************************************************************************
	\brief
		Convert the given world space coordinate to the screen
		space coordinate.
	\param _world_position
		The world space coordinate to be converted.
	\return
		(Vec2) The given input in screen space coordinates.

	*******************************************************************************/
	ToastBox::Vec2 World_To_Screen(ToastBox::Vec2 _world_position);
	/*!*****************************************************************************
	\brief
		Convert the given screen space coordinate to the
		world coordinate.
	\param _screen_position
		The screen space coordinate to be converted.
	\return
		(Vec2) The given input in world space coordinates.

	*******************************************************************************/
	ToastBox::Vec2 Screen_To_World(ToastBox::Vec2 _screen_position);

};

#endif


