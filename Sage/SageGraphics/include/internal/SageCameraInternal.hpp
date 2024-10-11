/* Start Header ************************************************************************/
/*!
\file		SageCameraInternal.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024
\brief		The private interface containing the internal SageCamera class that contains methods and
			data to facilitate creation and manipulation of a camera object.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#ifndef SAGE_CAMERA_INTERNAL_HPP
#define SAGE_CAMERA_INTERNAL_HPP
#include <glm/glm.hpp>


/*!*****************************************************************************
\brief
	Encapsulate a camera object in the rendering engine. Allowing for manipulation
	and creation of camera object in the game world.
\note This is the private interface that interacts with OpenGL.
*******************************************************************************/
class SageCameraInternal2D
{
	float aspect_ratio; //!< Aspect Ratio
	glm::vec2 position; //!< Position of the camera
	glm::vec2 view_rect_size; //!< Size of view rect
	glm::vec2 orientation; //!< The orientation of the camera

	glm::vec2 up_vec, right_vec; //!< The up and right vectors of the camera

	glm::mat3 view_matrix; //!< world to view matrix
	glm::mat3 projection_matrix; //!< Projection matrix
	glm::mat3 view_projection_matrix; //!< view to ndc matrix

public:
	/*!*****************************************************************************
	\brief
		An enum class that represent the type of camera that the private interface
		can be in.
	*******************************************************************************/
	enum class InternalSageCameraType
	{
		INTERNAL_SAGE_ORTHOGRAPHIC, // 2D - Ortho
		INTERNAL_SAGE_PERSPECTIVE // 3D - Perspective - sUnimplemented
	};
	float zoom; //!< Zoom

	/*!*****************************************************************************
	\brief
		Default Constructor for the camera object.
		This constructor intialize the camera object with default values.

	*******************************************************************************/
	SageCameraInternal2D();
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
	SageCameraInternal2D(glm::vec2 _position, glm::vec2 _view_rect_size, glm::vec2 _orientation, InternalSageCameraType _camera_type = InternalSageCameraType::INTERNAL_SAGE_ORTHOGRAPHIC);

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
	void Init(glm::vec2 _position, glm::vec2 _view_rect_size, glm::vec2 _orientation, InternalSageCameraType _camera_type = InternalSageCameraType::INTERNAL_SAGE_ORTHOGRAPHIC);
	/*!*****************************************************************************
	\brief
		Camera update's loop
		This function will update the camera object and it is called every frame in
		the game loop.

	*******************************************************************************/
	void Update();
	void Exit();
	/*!*****************************************************************************
	\brief
		Calculate both the view and projection matrix to be used when rendering,
		given the camera position.

		This function will be called to calculate a projection and a view matrix
		which is to be used when rendering objects and models.

	*******************************************************************************/
	void Calculate_Camera_Matrix();
	/*!*****************************************************************************
	\brief
		Set the camera position.

		This function set the camera position to the given input.

	\param _posittion The new position of the camera.
	*******************************************************************************/
	void Set_Position(glm::vec2 _position);
	/*!*****************************************************************************
	\brief
		Set the camera view rect size.

		This function set the camera view size to a 2D vector in their
		respective axis

	\param _view_rect_size The view size of the camera.
	*******************************************************************************/
	void Set_View_Rect_Size(glm::vec2 _view_rect_size);
	/*!*****************************************************************************
	\brief
		Set the camera orientation.

		This function take in a 2D vector representing the camera's orientation.

	\param _orientation The orientation of the camera.
	*******************************************************************************/
	void Set_Orientation(glm::vec2 _orientation);
	/*!*****************************************************************************
	\brief
		Get the position of the camera object in world space coordinates.
	\return
		(Vec2) The position of the camera object in world space coordinates.

	*******************************************************************************/
	glm::vec2 Get_Position() const;
	/*!*****************************************************************************
	\brief
		Get the scale of the camera view rectangle in world space coordinates.
	\return
		(Vec2) The view rectangle scale in world space.

	*******************************************************************************/
	glm::vec2 Get_View_Rect_Size() const;
	/*!*****************************************************************************
	\brief
		Get orientation of the camera
	\return
		(Vec2) The orientation of the camera as 2d vector.

	*******************************************************************************/
	glm::vec2 Get_Orientation() const;
	/*!*****************************************************************************
	\brief
		Get view matrix of the camera
	\return
		(mat3) The view matrix of the camera

	*******************************************************************************/
	glm::mat3 Get_View_Matrix() const;
	/*!*****************************************************************************
	\brief
		Get projection matrix of the camera
	\return
		(mat3) The projection matrix of the camera

	*******************************************************************************/
	glm::mat3 Get_Projection_Matrix() const;
	/*!*****************************************************************************
	\brief
		Get the vew projection matrix from the current camera object.
		This function retrieve the view projection matrix from the camera object. It is
		calculated by concatenating the view matrix and the projection matrix.
		(view * projection)
	\return
		(mat3) The view projection matrix of the camera object.

	*******************************************************************************/
	glm::mat3 const& Get_View_Projection_Matrix() const;

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
	void Move_Camera(glm::vec2 _move_vector, float speed);

	/*!*****************************************************************************
	\brief
		Get the internal camera as a void pointer.
	*******************************************************************************/
	void* Get_Camera();

};
#endif