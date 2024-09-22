#ifndef SAGE_CAMERA_INTERNAL_HPP
#define SAGE_CAMERA_INTERNAL_HPP
#include <glm/glm.hpp>


class SageCameraInternal2D
{
	float aspect_ratio; // Always follow the aspect ratio of the window
	glm::vec2 position; // The position of the camera
	glm::vec2 view_rect_size; // The size of the view rectangle 
	glm::vec2 orientation; // The orientation of the camera

	glm::vec2 up_vec, right_vec; // The up and right vectors of the camera

	glm::mat3 view_matrix; // world to view matrix
	glm::mat3 projection_matrix; // Projection matrix
	glm::mat3 view_projection_matrix; // view to ndc matrix

public:
	enum class InternalSageCameraType
	{
		INTERNAL_SAGE_ORTHOGRAPHIC, // 2D
		INTERNAL_SAGE_PERSPECTIVE // 3D - Unimplemented
	};
	float zoom;


	SageCameraInternal2D();
	SageCameraInternal2D(glm::vec2 _position, glm::vec2 _view_rect_size, glm::vec2 _orientation, InternalSageCameraType _camera_type = InternalSageCameraType::INTERNAL_SAGE_ORTHOGRAPHIC);

	void Init(glm::vec2 _position, glm::vec2 _view_rect_size, glm::vec2 _orientation, InternalSageCameraType _camera_type = InternalSageCameraType::INTERNAL_SAGE_ORTHOGRAPHIC);
	void Update();
	void Exit();

	void CalculateCameraMatrix();

	void set_position(glm::vec2 _position);
	void set_view_rect_size(glm::vec2 _view_rect_size);
	void set_orientation(glm::vec2 _orientation);

	glm::vec2 GetPosition() const;
	glm::vec2 GetViewRectSize() const;
	glm::vec2 GetOrientation() const;
	glm::mat3 GetViewMatrix() const;
	glm::mat3 GetProjectionMatrix() const;
	glm::mat3 GetViewProjectionMatrix() const;


	void move_camera(glm::vec2 _move_vector, float speed);


	void* GetCamera()
	{
		return this;
	}

};


#endif