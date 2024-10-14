/* Start Header ************************************************************************/
/*!
\file		Animator.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		11 September 2024
\brief		Contains the derived class Animator that overrides the virtual functions of the
			base class Component to do animator specific tasks. Times itself to pass the
			sprites to the gameobject's rendering component to simulate an animation
			based on flags provided by the animation set

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"
#include "AssetLoader.hpp"

class Animator : public Component
{
private:
	Assets::Animation_Set::Animation_Set animation_set;

	Sprite2D* sprite{ nullptr };
	Image* image{ nullptr };
	SageObject** obj{ nullptr };

	float internal_timer{};
public:

	/*!*****************************************************************************
	  \brief
		Default constructor for Animator
	*******************************************************************************/
	Animator();

	/*!*****************************************************************************
	  \brief
		Constructor for Animator that initializes the animation set based on the
		provided ID

	  \param _animation_set_ID
		What texture the sprite will use
	*******************************************************************************/
	Animator(std::string const& _texture_ID);

	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any Animator specific
		members that need initializing

	  \param _parent
		the gameobject that created this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;

	/*!*****************************************************************************
	  \brief
		Updates the Animator's internal logic to give the correct sprite to the
		Image or Sprite2D to be drawn
	*******************************************************************************/
	void Update() override;

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
		Sets the flag _flag to bool _b for the purpose of animator conditionals

	  \param _flag
		name of the flag

	  \param _b
		the bool to set the flag to
	*******************************************************************************/
	void Set_Parameter(std::string const& _flag, bool _b);
};
