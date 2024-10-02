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

/*!*****************************************************************************
  \brief
	Default constructor for Sprite2D
*******************************************************************************/
Sprite2D::Sprite2D() {}
/*!*****************************************************************************
  \brief
	Constructor for Sprite2D that takes in what texture you want the sprite to have
	along with what color to add on top of it

  \param _texture_ID
	What texture the sprite will use

  \param _colour
	what color the sprite should be
*******************************************************************************/
Sprite2D::Sprite2D(std::string const& _texture_ID, float const* _colour, std::string const& _object_shape) : sprite_texture_ID{ _texture_ID }, colour{ *_colour, *(_colour + 1),*(_colour + 2),*(_colour + 3) }, object_shape{ _object_shape } {}
/*!*****************************************************************************
  \brief
	Override for the constructor for Sprite2D that takes in what texture you want the sprite to have
	along with what color to add on top of it

  \param _texture_ID
	What texture the sprite will use

  \param _colour
	what color the sprite should be
*******************************************************************************/
Sprite2D::Sprite2D(std::string const& _texture_ID, std::initializer_list<float> const& _colour, std::string const& _object_shape) : Sprite2D(_texture_ID, _colour.begin(), _object_shape) {}

/*!*****************************************************************************
  \brief
	This function initializes the component along with any Sprite2D specific
	members that need initializing

  \param _parent
	the gameobject that created this component
*******************************************************************************/
void Sprite2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
	//gets transform component
	transform = dynamic_cast<Transform*>(_parent->Get_Component(TRANSFORM));

	//create sageobject
	if (object_shape == "Rect")
	{
		SageObjectManager::CreatePrimitiveObject(Get_Parent()->Get_ID().c_str(), PRIMITIVE_OBJECT_RECT,
			{ transform->Get_Positions()[0],transform->Get_Positions()[1] },
			{ transform->Get_Scale()[0],transform->Get_Scale()[1] },
			{ transform->Get_Rotations()[0],transform->Get_Rotations()[1] },
			{ colour[0],colour[1],colour[2],colour[3] });
	}
	else if (object_shape == "Circle")
	{
		SageObjectManager::CreatePrimitiveObject(Get_Parent()->Get_ID().c_str(), PRIMITIVE_OBJECT_CIRCLE,
			{ transform->Get_Positions()[0],transform->Get_Positions()[1] },
			{ transform->Get_Scale()[0],transform->Get_Scale()[1] },
			{ transform->Get_Rotations()[0],transform->Get_Rotations()[1] },
			{ colour[0],colour[1],colour[2],colour[3] });
	}


	//keep track of create sageobject
	obj = &SageObjectManager::objects[Get_Parent()->Get_ID().c_str()];

	//if has texture, assign it to the sageobject
	if (sprite_texture_ID != "")
	{
		obj->GetMaterial().enable_texture = true;
		SageTexture* texture = &Assets::Textures::Get_Texture(sprite_texture_ID);
		obj->attach_texture(texture);
	}
}

/*!*****************************************************************************
  \brief
	Updates the sprite's transforms to match its transform component
*******************************************************************************/
void Sprite2D::Update()
{
	//updates the sageobject with the current transforms of the Transform component
	obj->transform.position[0] = transform->Get_Positions()[0];
	obj->transform.position[1] = transform->Get_Positions()[1];
	obj->transform.scale[0] = transform->Get_Scale()[0];
	obj->transform.scale[1] = transform->Get_Scale()[1];
	obj->transform.orientation[0] = transform->Get_Rotations()[0];
	obj->transform.orientation[1] = transform->Get_Rotations()[1];
	obj->update();
}
/*!*****************************************************************************
  \brief
	Calls the function responsible for drawing the sageobject
*******************************************************************************/
void Sprite2D::Draw()
{
	//if sageobject exists, draw it 
	if (obj)
	{
		SageRenderer::Draw_Filled(*obj, {
		SageRenderer::SAGE_ENABLE_ALPHA | SageRenderer::SAGE_ENABLE_TEXTURE | SageRenderer::SAGE_ENABLE_CAMERA
		});
	}

	BoxCollider2D* collider = dynamic_cast<BoxCollider2D*>(Get_Parent()->Get_Component(BOXCOLLIDER2D));
	if (collider && collider->Get_Debug())
	{
		SageRenderer::Set_Option_On(SageRenderer::SAGE_ENABLE_CAMERA);
		collider->aabb.calculate_model_matrix(Get_Parent());
		auto& aabb = collider->aabb;
		SageRenderer::Draw_Line(aabb.min, aabb.min + ToastBox::Vec2{ aabb.scale.x ,0 }, { 0,1,0,1 }, 1.f);
		SageRenderer::Draw_Line(aabb.min, aabb.min + ToastBox::Vec2{ 0,aabb.scale.y }, { 0,1,0,1 }, 1.f);
		SageRenderer::Draw_Line(aabb.max, aabb.max - ToastBox::Vec2{ aabb.scale.x ,0 }, { 0,1,0,1 }, 1.f);
		SageRenderer::Draw_Line(aabb.max, aabb.max - ToastBox::Vec2{ 0,aabb.scale.y }, { 0,1,0,1 }, 1.f);

		SageRenderer::Set_Option_Off(SageRenderer::SAGE_ENABLE_CAMERA);
	}
}
/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Sprite2D::Exit() 
{
}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Sprite2D::Get_Component_Type() { return SPRITE2D; }

/*!*****************************************************************************
  \brief
	This function changes the texture ID

  \param _ID
	the ID of the replacing texture
*******************************************************************************/
void Sprite2D::Set_Texture_ID(std::string const& _ID)
{
	sprite_texture_ID = _ID;
}

/*!*****************************************************************************
  \brief
	This function changes the color of the sprite

  \param _new_col
	the ID of the replacing texture
*******************************************************************************/
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

/*!*****************************************************************************
  \brief
	Override for the function that changes the color of the sprite

  \param _new_col
	the ID of the replacing texture
*******************************************************************************/
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

/*!*****************************************************************************
  \brief
	This function changes the transparency of the sprite

  \param _a
	the replacing alpha
*******************************************************************************/
void Sprite2D::Set_Transparency(float _a)
{
	colour[3] = _a;
	if (obj)
	{
		obj->set_alpha(_a);
	}
}