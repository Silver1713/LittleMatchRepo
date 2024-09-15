#include "Components.hpp"
#include "GameObjects.hpp"
#include "SageEngine.hpp"
#include "AssetLoader.hpp"

#include <iostream>
#include <initializer_list>
//here to include everything that all components need to function so this script will
// be the only one to be dependent on all other systems

#pragma region Component
void Component::Init(GameObject* _parent)
{
	parent = _parent;
}
void Component::Update() {}
void Component::Draw() {}
void Component::Exit() {}
ComponentType Component::Get_Component_Type() { return COMPONENT; }

GameObject* Component::Get_Parent() { return parent; }
void Component::Set_Parent(GameObject* const _parent)
{
	parent = _parent;
}

#pragma region Transform
Transform::Transform() {}
Transform::Transform(float const* _pos, float const* _rot, float const* _scale, bool _is_UI_element) : positions{ *_pos,*(_pos + 1),*(_pos+2)}, rotations{*_rot, *(_rot+1), *(_rot+2)}, scale{*_scale, *(_scale+1), *(_scale+2)} {}
Transform::Transform(std::initializer_list<float> const& _pos, std::initializer_list<float> const& _rot, std::initializer_list<float> const& _scale) : Transform(_pos.begin(), _rot.begin(), _scale.begin()) {}

void Transform::Init(GameObject* _parent)
{
	Component::Init(_parent);
	//for (unsigned int i{}; i < 3; i++)
	//{
	//	std::cout << "Positions[" << i << "] = " << positions[i] << "\n";
	//}
	//
	//for (unsigned int i{}; i < 3; i++)
	//{
	//	std::cout << "Rotations[" << i << "] = " << rotations[i] << "\n";
	//}

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
float const* Transform::Get_Positions()
{
	return positions;
}
void Transform::Set_Rotations(float const* _new_rot)
{
	*rotations = *_new_rot;
}
float const* Transform::Get_Rotations()
{
	return rotations;
}

void Transform::Set_Scale(float const* _new_scale)
{
	*scale = *_new_scale;
}
float const* Transform::Get_Scale()
{
	return scale;
}

bool& Transform::Is_UI_Element()
{
	return is_UI_Element;
}

#pragma endregion

#pragma region Sprite2D
Sprite2D::Sprite2D() {}
Sprite2D::Sprite2D(std::string const& _texture_ID, float const* _colour) : sprite_texture_ID{ _texture_ID }, colour{ *_colour, *(_colour + 1),*(_colour + 2),*(_colour + 3) }{}
Sprite2D::Sprite2D(std::string const& _texture_ID, std::initializer_list<float> const& _colour) : Sprite2D(_texture_ID, _colour.begin()) {}

void Sprite2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
	transform = dynamic_cast<Transform*>(_parent->Get_Component(TRANSFORM).get());

	SageObjectManager::CreatePrimitiveObject((std::to_string(Get_Parent()->Get_ID())).c_str(), PRIMITIVE_OBJECT_RECT,
		{ transform->Get_Positions()[0],transform->Get_Positions()[1] },
		{ transform->Get_Scale()[0],transform->Get_Scale()[1] },
		{ transform->Get_Rotations()[0],transform->Get_Rotations()[1] },
		{ colour[0],colour[1],colour[2],colour[3] });

	std::cout << std::endl;
	obj = &SageObjectManager::objects[std::to_string(Get_Parent()->Get_ID())];
	
	if (sprite_texture_ID != "")
	{
		obj->GetMaterial().enable_texture = true;
		SageTexture* texture = &Assets::Textures::Get_Texture(sprite_texture_ID);
		obj->attach_texture(texture);
	}
}
void Sprite2D::Update() {}
void Sprite2D::Draw() {}
void Sprite2D::Exit() {}

ComponentType Sprite2D::Get_Component_Type() { return SPRITE2D; }

void Sprite2D::Set_Texture_ID(std::string _ID)
{
	sprite_texture_ID = _ID;
}

void Sprite2D::Set_Transparency(float& _a) 
{
	colour[3] = _a;
	obj->set_alpha(_a);
}
#pragma endregion

#pragma region Collision2D
void Collision2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void Collision2D::Update(){}
void Collision2D::Exit(){}
ComponentType Collision2D::Get_Component_Type() { return COLLISION2D; }
#pragma endregion

#pragma region Audio
void Audio::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void Audio::Update()
{

}
void Audio::Exit()
{

}
ComponentType Audio::Get_Component_Type() { return AUDIO; }
#pragma endregion

