#include "SageCamera.hpp"
#include "SageCameraInternal.hpp"
#include "Vector3.h"
#include "glm/gtc/type_ptr.inl"

class SageCamera::SageCameraImpl
{
	SageCameraInternal2D camera;

public:
	SageCameraImpl() : camera() {}
	SageCameraImpl(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, int _camera_type) : camera({ _position.getX(), _position.getY() }, { _view_rect_size.getX(),_view_rect_size.getY() }, { _orientation,0 }, static_cast
		<SageCameraInternal2D::InternalSageCameraType>(_camera_type)) {}

	float const* get_projection_view() const
	{
		return glm::value_ptr(camera.GetViewProjectionMatrix());

	}


	ToastBox::Vec2 GetPosition() const
	{
		return ToastBox::Vec2{ camera.GetPosition().x, camera.GetPosition().y };
	}
	ToastBox::Vec2 GetViewRectSize() const
	{
		return ToastBox::Vec2{ camera.GetViewRectSize().x, camera.GetViewRectSize().y };
	}

	void MoveCamera(ToastBox::Vec2 _move_vector, float speed)
	{
		camera.move_camera({ _move_vector.getX(), _move_vector.getY() }, speed);
	}

	void Update()
	{
		camera.Update();

	}

	void Init(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, ToastBox::Vec2 _orientation, SageCameraInternal2D::InternalSageCameraType _camera_type)
	{
		camera.Init({ _position.getX(), _position.getY() }, { _view_rect_size.getX(),_view_rect_size.getY() }, { _orientation.getX(),_orientation.getY() }, _camera_type);
	}

	void* GetCam()
	{
		return camera.GetCamera();
	}
};


SageCamera::SageCamera() : impl(nullptr), zoom(1.0f), orientation(0.0f), position(0.0f, 0.0f), rect_size(0.0f, 0.0f), aspect_ratio(1.0f), view_matrix(), projection_matrix(), view_projection_matrix()
{
	impl = std::make_unique<SageCameraImpl>();

};


SageCamera::SageCamera(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, SageCameraType _camera_type)
{
	impl = std::make_unique<SageCameraImpl>();
	init(_position, _view_rect_size, _orientation, _camera_type);
}

ToastBox::Matrix3x3 SageCamera::get_projection_view_matrix() 
{
	view_projection_matrix = ToastBox::Matrix3x3{impl->get_projection_view()};
	return view_projection_matrix;
}


ToastBox::Vec2 SageCamera::GetPosition()
{
	position = impl->GetPosition();
	return position;
}

ToastBox::Vec2 SageCamera::GetViewRectSize()
{
	rect_size = impl->GetViewRectSize();
	return rect_size;
}

void SageCamera::MoveCamera(ToastBox::Vec2 _move_vector, float speed)
{
	impl->MoveCamera(_move_vector, speed);

	position = GetPosition();
}

void SageCamera::update()
{
	impl->Update();
}


void SageCamera::init(ToastBox::Vec2 _position, ToastBox::Vec2 _view_rect_size, float _orientation, SageCameraType _camera_type)
{
	impl->Init({ _position.getX(), _position.getY() }, { _view_rect_size.getX(),_view_rect_size.getY() }, { _orientation,0 }, static_cast
		<SageCameraInternal2D::InternalSageCameraType>(_camera_type));

	position = _position;
	rect_size = _view_rect_size;
	orientation = _orientation;
	this->aspect_ratio = static_cast<float>(_view_rect_size.getX()) / static_cast<float>(_view_rect_size.y);
	this->zoom = 1.0f;
	this->view_projection_matrix = impl->get_projection_view();

}


SageCamera::SageCamera(SageCamera&& cam) noexcept : position(cam.position), rect_size(cam.rect_size), aspect_ratio(cam.aspect_ratio), view_matrix(cam.view_matrix), projection_matrix(cam.projection_matrix), view_projection_matrix(cam.view_projection_matrix), zoom(cam.zoom), orientation(cam.orientation)
{
	impl = std::move(cam.impl);

	

}

SageCamera::SageCamera(const SageCamera& cam) : position(cam.position), rect_size(cam.rect_size), aspect_ratio(cam.aspect_ratio), view_matrix(cam.view_matrix), projection_matrix(cam.projection_matrix), view_projection_matrix(cam.view_projection_matrix), zoom(cam.zoom), orientation(cam.orientation)
{
	impl = std::make_unique<SageCameraImpl>(*cam.impl);
}

SageCamera::~SageCamera()
{
	impl->~SageCameraImpl();
}
void* SageCamera::GetCamera()
{
	return impl->GetCam();
}

ToastBox::Vec2 SageCamera::Screen_To_World(ToastBox::Vec2 screen_pos)
{
	ToastBox::Vec2 world_pos;

	world_pos.x = screen_pos.x * (1.f / (rect_size.x/2.f)) -1.f;
	world_pos.y = -(screen_pos.y * (1.f / (rect_size.y/2.f)) -1.f);

	
	ToastBox::Matrix3x3 vpm = get_projection_view_matrix();

	ToastBox::Vec3 pos{ world_pos.x, world_pos.y, 1.0f };
	ToastBox::Matrix3x3 inv = ~vpm.inverse();

	ToastBox::Vec3 result = ~inv * pos;


	world_pos.x = result.x;
	world_pos.y = result.y;

	return world_pos;

	
	
}

ToastBox::Vec2 SageCamera::World_To_Screen(ToastBox::Vec2 world_pos)
{
	ToastBox::Vec2 screen_pos;
	ToastBox::Vec3 pos{ world_pos.x, world_pos.y, 1.0f };

	ToastBox::Vec3 result = view_projection_matrix * pos;
	screen_pos.x = result.x;
	screen_pos.y = -result.y;

	screen_pos.x *= rect_size.x / 2;
	screen_pos.x += rect_size.x / 2;
	screen_pos.y *= rect_size.y / 2;
	screen_pos.y += rect_size.y / 2

	;

	return screen_pos;
}


