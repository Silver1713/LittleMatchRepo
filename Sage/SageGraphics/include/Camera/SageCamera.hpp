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
class SageCamera {

	ToastBox::Vec2 position, rect_size;
	
	float aspect_ratio;
	ToastBox::Matrix3x3 view_matrix,
		projection_matrix,
		view_projection_matrix;

	class SageCameraImpl;
	std::unique_ptr<SageCameraImpl> impl;
		
public:
	enum class SageCameraType
	{
		SAGE_ORTHO, // 2D
		SAGE_PERSP // 3D - Unimplemented
	};
	float zoom;
	float orientation;

	SageCamera();
	SageCamera(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, SageCameraType _camera_type = SageCameraType::SAGE_ORTHO);

	SageCamera(const SageCamera&);

	//Move
	SageCamera(SageCamera&&) noexcept;

	~SageCamera();


	void init(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, SageCameraType _camera_type = SageCameraType::SAGE_ORTHO);

	void update();

	ToastBox::Matrix3x3 Get_Projection_View_Matrix();
	ToastBox::Vec2 GetPosition();
	ToastBox::Vec2 GetViewRectSize();


	void MoveCamera(ToastBox::Vec2 _move_vector, float _speed);

	void* GetCamera();

	ToastBox::Vec2 World_To_Screen(ToastBox::Vec2 _world_position);
	ToastBox::Vec2 Screen_To_World(ToastBox::Vec2 _world_position);

};

#endif


