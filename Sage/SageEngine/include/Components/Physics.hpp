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

class Physics : public Component
{
private:
	float velocity{};
	float cur_velocity{};
	//add whatever member properties u want for physics

public:
	Physics();
	Physics(float _velocity);

	void Init(GameObject* _parent) override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;

	//add whatever declarations of getters/setters u need for physics
};