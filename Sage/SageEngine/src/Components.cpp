#include "Components.hpp"

#include <iostream>
//here to include everything that all components need to function so this script will
// be the only one to be dependent on all other systems

#pragma region Transform
void Transform::Init()
{
	std::cout << "Transform::Init() Successful" << "\n";
}
void Transform::Update()
{

}
void Transform::Exit()
{

}
#pragma endregion

#pragma region Sprite2D
void Sprite2D::Init()
{
	std::cout << "Sprite2D::Init() Successful" << "\n";
}
void Sprite2D::Update()
{

}
void Sprite2D::Exit()
{

}
#pragma endregion

#pragma Collision2D
void Collision2D::Init()
{
	std::cout << "Collision2D::Init() Successful" << "\n";
}
void Collision2D::Update()
{

}
void Collision2D::Exit()
{

}
#pragma endregion

#pragma Audio
void Audio::Init()
{
	std::cout << "Audio::Init() Successful" << "\n";
}
void Audio::Update()
{

}
void Audio::Exit()
{

}
#pragma endregion

