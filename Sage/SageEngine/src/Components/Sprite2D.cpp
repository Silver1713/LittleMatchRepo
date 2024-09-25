/* Start Header ************************************************************************/
/*!
\file		Sprite2D.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		11 September 2024
\brief		Contains the derived class Sprite2D that overrides the virtual functions of the
			base class Component to do sprite specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "GameObjects.hpp"
#include "Components/Transform.hpp"
#include "Components/Sprite2D.hpp"
#include "SageObjectManager.hpp"

#include <iostream>

Sprite2D::Sprite2D() {}
Sprite2D::Sprite2D(std::string const& _texture_ID, float const* _colour) : sprite_texture_ID{ _texture_ID }, colour{ *_colour, *(_colour + 1),*(_colour + 2),*(_colour + 3) } {}
Sprite2D::Sprite2D(std::string const& _texture_ID, std::initializer_list<float> const& _colour) : Sprite2D(_texture_ID, _colour.begin()) {}

void Sprite2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
	transform = dynamic_cast<Transform*>(_parent->Get_Component(TRANSFORM));

	SageObjectManager::CreatePrimitiveObject(Get_Parent()->Get_ID().c_str(), PRIMITIVE_OBJECT_RECT,
		{ transform->Get_Positions()[0],transform->Get_Positions()[1] },
		{ transform->Get_Scale()[0],transform->Get_Scale()[1] },
		{ transform->Get_Rotations()[0],transform->Get_Rotations()[1] },
		{ colour[0],colour[1],colour[2],colour[3] });

	obj = &SageObjectManager::objects[Get_Parent()->Get_ID().c_str()];

	if (sprite_texture_ID != "")
	{
		obj->GetMaterial().enable_texture = true;
		SageTexture* texture = &Assets::Textures::Get_Texture(sprite_texture_ID);
		obj->attach_texture(texture);
	}
}
void Sprite2D::Update()
{
	obj->transform.position[0] = transform->Get_Positions()[0];
	obj->transform.position[1] = transform->Get_Positions()[1];
	obj->transform.scale[0] = transform->Get_Scale()[0];
	obj->transform.scale[1] = transform->Get_Scale()[1];
	obj->transform.orientation[0] = transform->Get_Rotations()[0];
	obj->transform.orientation[1] = transform->Get_Rotations()[1];
	obj->update();
}
void Sprite2D::Draw()
{
	if (obj)
	{
		SageRenderer::DrawFilled(*obj, {
		SageRenderer::SAGE_ENABLE_ALPHA | SageRenderer::SAGE_ENABLE_TEXTURE | SageRenderer::SAGE_ENABLE_CAMERA });
	}
}
void Sprite2D::Exit() 
{
}

ComponentType Sprite2D::Get_Component_Type() { return SPRITE2D; }

void Sprite2D::Set_Texture_ID(std::string const& _ID)
{
	sprite_texture_ID = _ID;
}
void Sprite2D::Set_Colour(float const* _new_col)
{

	*colour = *_new_col;
	for (unsigned int i{}; i < 3; i++)
	{
		if (obj)
		{
			obj->GetMaterial().color[i] = colour[i];
		}		
	}

}
void Sprite2D::Set_Colour(std::initializer_list<float> const& _new_col)
{
	for (unsigned int i{}; i < 3; i++)
	{
		colour[i] = *(_new_col.begin() + i);
		if (obj)
		{
			obj->GetMaterial().color[i] = colour[i];
		}	
	}
}
void Sprite2D::Set_Transparency(float _a)
{
	colour[3] = _a;
	if (obj)
	{
		obj->set_alpha(_a);
	}
}