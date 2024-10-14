/* Start Header ************************************************************************/
/*!
\file		Sprite2D.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		11 September 2024
\brief		Contains the derived class Sprite2D that overrides the virtual functions of the
			base class Component to do sprite specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"

class Sprite2D : public Component
{
private:
	std::string sprite_texture_ID{ "" };
	std::string object_shape{"Rect"};
	ToastBox::Vec4 colour{};
	Transform* transform{ nullptr };
	SageObject* obj{ nullptr };

public:

	/*!*****************************************************************************
	  \brief
		Default constructor for Sprite2D
	*******************************************************************************/
	Sprite2D();

	/*!*****************************************************************************
	  \brief
		Constructor for Sprite2D that takes in what texture you want the sprite to have
		along with what color to add on top of it

	  \param _texture_ID
		What texture the sprite will use

	  \param _colour
		what color the sprite should be
	*******************************************************************************/
	Sprite2D(std::string const& _texture_ID, ToastBox::Vec4 const& _colour, std::string const& _object_shape = "Rect");

	/*!*****************************************************************************
	  \brief
		Override for the constructor for Sprite2D that takes in what texture you want the sprite to have
		along with what color to add on top of it

	  \param _texture_ID
		What texture the sprite will use

	  \param _colour
		what color the sprite should be
	*******************************************************************************/
	Sprite2D(std::string const& _texture_ID, std::initializer_list<float> const& _colour, std::string const& _object_shape = "Rect");

	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any Sprite2D specific
		members that need initializing

	  \param _parent
		the gameobject that created this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		Updates the sprite's transforms to match its transform component
	*******************************************************************************/
	void Update() override;

	/*!*****************************************************************************
	  \brief
		Calls the function responsible for drawing the sageobject
	*******************************************************************************/
	void Draw() override;

	/*!*****************************************************************************
	  \brief
		Provides a space if there is any unloading or freeing may be required
		per component
	*******************************************************************************/
	void Exit() override;

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	ComponentType Get_Component_Type() override;

	/*!*****************************************************************************
	  \brief
		This function changes the texture ID

	  \param _ID
		the ID of the replacing texture
	*******************************************************************************/
	void Set_Texture_ID(std::string const& _ID);

	/*!*****************************************************************************
	  \brief
		This function changes the color of the sprite

	  \param _new_col
		the ID of the replacing texture
	*******************************************************************************/
	void Set_Colour(ToastBox::Vec4 const& _new_col);

	/*!*****************************************************************************
	  \brief
		Override for the function that changes the color of the sprite

	  \param _new_col
		the ID of the replacing texture
	*******************************************************************************/
	void Set_Colour(std::initializer_list<float> const& _new_col);

	/*!*****************************************************************************
	  \brief
		This function changes the transparency of the sprite

	  \param _a
		the replacing alpha
	*******************************************************************************/
	void Set_Transparency(float _a);

	/*!*****************************************************************************
	  \brief
		Gets the sageobject

	  \return
		pointer to the pointer to the sageobject
	*******************************************************************************/
	SageObject** Get_Object();
};
