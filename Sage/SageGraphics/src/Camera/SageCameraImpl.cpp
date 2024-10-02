#include "SageCameraImpl.hpp"
#include "SageCamera.hpp"
#include "glm/gtc/type_ptr.inl"

SageCamera::SageCameraImpl::SageCameraImpl() : camera() {}

SageCamera::SageCameraImpl::SageCameraImpl(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, int _camera_type) :
camera({ _position.getX(), _position.getY() }, { _view_rect_size.getX(),_view_rect_size.getY() }, 
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

void SageCamera::SageCameraImpl::MoveCamera(ToastBox::Vec2 _move_vector, float _speed)
{
	camera.Move_Camera({ _move_vector.getX(), _move_vector.getY() }, _speed);
}

void SageCamera::SageCameraImpl::Update()
{
	camera.Update();
}


void SageCamera::SageCameraImpl::Init(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, ToastBox::Vec2 _orientation, SageCameraInternal2D::InternalSageCameraType _camera_type)
{
	camera.Init({ _position.getX(), _position.getY() }, { _view_rect_size.getX(),_view_rect_size.getY() }, 
		{ _orientation.getX(),_orientation.getY() }, _camera_type);

}

void* SageCamera::SageCameraImpl::GetCam()
{
	return camera.Get_Camera();
}