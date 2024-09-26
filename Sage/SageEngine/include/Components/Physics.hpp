/* Start Header ************************************************************************/
/*!
\file		Component.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the class Component that declares the base class that is to be polymorphed
			into the various types of components as defined by ComponentType depending on the
			need of a gameobject.

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