#include "Components/Component.hpp"
#include "Components/Transform.hpp"

Transform::Transform() {}
Transform::Transform(float const* _pos, float const* _rot, float const* _scale, bool _is_UI_element) : positions{ *_pos,*(_pos + 1),*(_pos + 2) }, rotations{ *_rot, *(_rot + 1), *(_rot + 2) }, scale{ *_scale, *(_scale + 1), *(_scale + 2) } {}
Transform::Transform(std::initializer_list<float> const& _pos, std::initializer_list<float> const& _rot, std::initializer_list<float> const& _scale) : Transform(_pos.begin(), _rot.begin(), _scale.begin()) {}

void Transform::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void Transform::Update()
{

}
void Transform::Exit()
{

}

ComponentType Transform::Get_Component_Type() { return TRANSFORM; }
void Transform::Set_Positions(float const* _new_pos)
{
	*positions = *_new_pos;
}
void Transform::Set_Positions(std::initializer_list<float> const& _new_pos)
{
	for (unsigned int i{}; i < 3; i++)
	{
		positions[i] = *(_new_pos.begin() + i);
	}
}
float const* Transform::Get_Positions()
{
	return positions;
}
void Transform::Set_Rotations(float const* _new_rot)
{
	*rotations = *_new_rot;
}
void Transform::Set_Rotations(std::initializer_list<float> const& _new_rot)
{
	for (unsigned int i{}; i < 3; i++)
	{
		rotations[i] = *(_new_rot.begin() + i);
	}
}
float const* Transform::Get_Rotations()
{
	return rotations;
}

void Transform::Set_Scale(float const* _new_scale)
{
	*scale = *_new_scale;
}
void Transform::Set_Scale(std::initializer_list<float> const& _new_scale)
{
	for (unsigned int i{}; i < 3; i++)
	{
		scale[i] = *(_new_scale.begin() + i);
	}
}
float const* Transform::Get_Scale()
{
	return scale;
}

void Transform::Translate(float const* _delta_pos)
{
	*positions = *_delta_pos;
}
void Transform::Translate(std::initializer_list<float> const& _delta_pos)
{
	for (unsigned int i{}; i < 3; i++)
	{
		positions[i] += *(_delta_pos.begin() + i);
	}
}
void Transform::Rotate(float const* _delta_rot)
{
	*rotations = *_delta_rot;
}
void Transform::Rotate(std::initializer_list<float> const& _delta_rot)
{
	for (unsigned int i{}; i < 3; i++)
	{
		rotations[i] += *(_delta_rot.begin() + i);
	}
}
void Transform::Scale(float const* _delta_scale)
{
	*scale = *_delta_scale;
}
void Transform::Scale(std::initializer_list<float> const& _delta_scale)
{
	for (unsigned int i{}; i < 3; i++)
	{
		scale[i] += *(_delta_scale.begin() + i);
	}
}

bool& Transform::Is_UI_Element()
{
	return is_UI_Element;
}