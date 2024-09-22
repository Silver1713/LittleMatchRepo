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

	ToastBox::Matrix3x3 get_projection_view_matrix();
	ToastBox::Vec2 GetPosition();
	ToastBox::Vec2 GetViewRectSize();


	void MoveCamera(ToastBox::Vec2 _move_vector, float speed);

	void* GetCamera();
};

#endif


