/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to do Collision specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"

class BoxCollider2D : public Component
{
	struct AABB
	{
		float pos_x, pos_y; // Center position of the collider in the object's local space
		float min_x, min_y; // Minimum extents of the collider in the object's local space
		float max_x, max_y; // Maximum extents of the collider in the object's local space
	};

public:
	AABB aabb;

	void Init(GameObject* _parent) override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
};