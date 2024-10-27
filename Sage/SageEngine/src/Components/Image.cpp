/* Start Header ************************************************************************/
/*!
\file		Image.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		11 September 2024
\brief		Contains the derived class Image that overrides the virtual functions of the
			base class Component to do sprite specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "GameObjects.hpp"
#include "Components/Transform.hpp"
#include "Components/Image.hpp"
#include "SageObjectManager.hpp"

#include <iostream>

/*!*****************************************************************************
  \brief
	Default constructor for Image
*******************************************************************************/
Image::Image() {}
/*!*****************************************************************************
  \brief
	Constructor for Image that takes in what texture you want the sprite to have
	along with what color to add on top of it

  \param _texture_ID
	What texture the sprite will use

  \param _colour
	what color the sprite should be
*******************************************************************************/
Image::Image(std::string const& _texture_ID, ToastBox::Vec4 const& _colour, std::string const& _object_shape) : sprite_texture_ID{ _texture_ID }, colour{ _colour }, object_shape{ _object_shape } {}
/*!*****************************************************************************
  \brief
	Override for the constructor for Image that takes in what texture you want the sprite to have
	along with what color to add on top of it

  \param _texture_ID
	What texture the sprite will use

  \param _colour
	what color the sprite should be
*******************************************************************************/
Image::Image(std::string const& _texture_ID, std::initializer_list<float> const& _colour, std::string const& _object_shape) : Image(_texture_ID,
	ToastBox::Vec4(*(_colour.begin()), *(_colour.begin() + 1), *(_colour.begin() + 2), *(_colour.begin() + 3)),
	_object_shape) {}

/*!*****************************************************************************
  \brief
	This function initializes the component along with any Image specific
	members that need initializing

  \param _parent
	the gameobject that created this component
*******************************************************************************/
void Image::Init(GameObject* _parent)
{
	Component::Init(_parent);
	//gets transform component
	transform = static_cast<UITransform*>(_parent->Get_Component<UITransform>());

	//create sageobject
	PrimitiveObject p = PRIMITIVE_OBJECT_RECT;
	if (object_shape == "Circle")
	{
		p = PRIMITIVE_OBJECT_CIRCLE;
	}

	SageObjectManager::Create_Primitive_Object(Get_Parent()->Get_ID().c_str(), p,
		{ transform->Get_Position().x,transform->Get_Position().y },
		{ transform->Get_Scale().x,transform->Get_Scale().y },
		{ transform->Get_Rotation().x,transform->Get_Rotation().y },
		{ colour[0],colour[1],colour[2],colour[3] });


	//keep track of create sageobject
	obj = &SageObjectManager::objects[Get_Parent()->Get_ID().c_str()];

	//if has texture, assign it to the sageobject
	if (sprite_texture_ID != "")
	{
		obj->GetMaterial().enable_texture = true;
		SageTexture* texture = &Assets::Textures::Get_Texture(sprite_texture_ID);
		obj->Attach_Texture(texture);
	}
}

/*!*****************************************************************************
  \brief
	Updates the sprite's transforms to match its transform component
*******************************************************************************/
void Image::Update()
{
	//updates the sageobject with the current transforms of the Transform component
	obj->transform.position.x = transform->Get_Position().x;
	obj->transform.position.y = transform->Get_Position().y;
	obj->transform.scale.x = transform->Get_Scale().x;
	obj->transform.scale.y = transform->Get_Scale().y;
	obj->transform.orientation.x = transform->Get_Rotation().x;
	obj->transform.orientation.y = transform->Get_Rotation().y;

	//need to update color also

	obj->Update();
}
/*!*****************************************************************************
  \brief
	Calls the function responsible for drawing the sageobject
*******************************************************************************/
void Image::Draw()
{
	//if sageobject exists, draw it 
	if (obj)
	{
		SageRenderer::Draw_Filled(*obj, {
		SageRenderer::SAGE_ENABLE_ALPHA | SageRenderer::SAGE_ENABLE_TEXTURE
		});
	}
}
/*!*****************************************************************************
  \brief
	Provides a space if there is any unloading or freeing may be required
	per component
*******************************************************************************/
void Image::Exit() 
{
}

/*!*****************************************************************************
  \brief
	Gets overriden based on what component this is

  \return
	the enum representating what component this is
*******************************************************************************/
ComponentType Image::Get_Component_Type() { return IMAGE; }

/*!*****************************************************************************
  \brief
	This function changes the texture ID

  \param _ID
	the ID of the replacing texture
*******************************************************************************/
void Image::Set_Texture_ID(std::string const& _ID)
{
	sprite_texture_ID = _ID;
}

/*!*****************************************************************************
  \brief
	This function changes the color of the sprite

  \param _new_col
	the ID of the replacing texture
*******************************************************************************/
void Image::Set_Colour(ToastBox::Vec4 const& _new_col)
{
	colour = _new_col;
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
void Image::Set_Colour(std::initializer_list<float> const& _new_col)
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
	Gets the colour of the images

  \return
	the colour
*******************************************************************************/
ToastBox::Vec4 const& Image::Get_Colour()
{
	return colour;
}

/*!*****************************************************************************
  \brief
	This function changes the transparency of the sprite

  \param _a
	the replacing alpha
*******************************************************************************/
void Image::Set_Transparency(float _a)
{
	colour[3] = _a;
	if (obj)
	{
		obj->Set_Alpha(_a);
	}
}

/*!*****************************************************************************
  \brief
	Gets the sageobject

  \return
	pointer to the pointer to the sageobject
*******************************************************************************/
SageObject** Image::Get_Object()
{
	return &obj;
}

/*!*****************************************************************************
  \brief
	Gets the shape of the object

  \return
	pointer the string of the shape of the object
*******************************************************************************/
std::string Image::Get_Shape()
{
	return object_shape;
}

/*!*****************************************************************************
  \brief
	Set the shape of the sageobject
*******************************************************************************/
void Image::Set_Shape(std::string _shape)
{
	object_shape = _shape;
}