#include "Components.hpp"

#include <iostream>
//here to include everything that all components need to function so this script will
// be the only one to be dependent on all other systems

#pragma region Component
void Component::Init() {}
void Component::Update() {}
void Component::Exit() {}
ComponentType Component::Get_Component_Type() { return COMPONENT; }


#pragma region Transform
Transform::Transform() {}
Transform::Transform(float const _new_pos[3], float const _new_rot[3]) : positions{_new_pos[0],_new_pos[1],_new_pos[2]}, rotations{ _new_rot[0],_new_rot[1],_new_rot[2] } {}

void Transform::Init()
{
	for (unsigned int i{}; i < 3; i++)
	{
		std::cout << "Positions[" << i << "] = " << positions[i] << "\n";
	}
	
	for (unsigned int i{}; i < 3; i++)
	{
		std::cout << "Rotations[" << i << "] = " << rotations[i] << "\n";
	}

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
	for (unsigned int i{}; i < 3; i++)
	{
		positions[i] = _new_pos[i];
	}
}
float const* Transform::Get_Positions()
{
	return positions;
}
void Transform::Set_Rotations(float const* _new_rot)
{
	for (unsigned int i{}; i < 3; i++)
	{
		rotations[i] = _new_rot[i];
	}
}
float const* Transform::Get_Rotations()
{
	return rotations;
}

void Transform::Set_Scale(float const* _new_scale)
{
	for (unsigned int i{}; i < 3; i++)
	{
		scale[i] = _new_scale[i];
	}
}
float const* Transform::Get_Scale()
{
	return scale;
}

#pragma endregion

#pragma region Sprite2D
Sprite2D::Sprite2D() {}
Sprite2D::Sprite2D(std::string _texture_ID) : sprite_texture_ID{ _texture_ID } {}

void Sprite2D::Init()
{
	std::cout << "Sprite ID: " << sprite_texture_ID << "\n";
}
void Sprite2D::Update()
{

}
void Sprite2D::Exit()
{

}
ComponentType Sprite2D::Get_Component_Type() { return SPRITE2D; }

void Sprite2D::Set_Texture_ID(std::string _ID)
{
	sprite_texture_ID = _ID;
}
#pragma endregion

#pragma region Collision2D
void Collision2D::Init()
{
	std::cout << "Collision Component Reporting" << "\n";
}
void Collision2D::Update()
{
}
void Collision2D::Exit()
{

}
ComponentType Collision2D::Get_Component_Type() { return COLLISION2D; }
#pragma endregion

#pragma region Audio
void Audio::Init()
{
	std::cout << "Audio Component Reporting" << "\n";
}
void Audio::Update()
{

}
void Audio::Exit()
{

}
ComponentType Audio::Get_Component_Type() { return AUDIO; }
#pragma endregion
