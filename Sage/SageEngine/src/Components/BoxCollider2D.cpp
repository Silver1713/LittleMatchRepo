/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to do Collision specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include "Components/BoxCollider2D.hpp"

void BoxCollider2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void BoxCollider2D::Update() {}
void BoxCollider2D::Exit() {}
ComponentType BoxCollider2D::Get_Component_Type() { return BOXCOLLIDER2D; }