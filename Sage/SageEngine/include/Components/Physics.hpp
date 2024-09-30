/* Start Header ************************************************************************/
/*!
\file		Physics.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		20 September 2024
\brief		Contains the derived class Physics that overrides the virtual functions of the
			base class Component to do functions specific to physics specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"
#include "Vector2.h"

class Physics : public Component
{
private:
	ToastBox::Vec2 velocity;
	ToastBox::Vec2 curr_velocity;

	//add whatever member properties u want for physics
	bool is_static; // disable physics
	float mass;
	float gravity;


public:
	Physics();
	Physics(ToastBox::Vec2 _velocity);

	void Init(GameObject* _parent) override;
	
	void Update() override;
	void Exit() override;
	ToastBox::Vec2& Get_Velocity();
	ComponentType Get_Component_Type() override;

	//add whatever declarations of getters/setters u need for physics

	void set_static(bool _is_static);
};