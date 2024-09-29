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
#include <string>
#include <initializer_list>

class GameObject;
class SageObject;

typedef enum {
	COMPONENT,
	TRANSFORM,
	SPRITE2D,
	PHYSICS,
	BOXCOLLIDER2D,
	RIGIDBODY2D,
	AUDIO,
	NUM_OF_TYPES_OF_COMPONENTS
} ComponentType;

class Component
{
private:
	GameObject* parent{ nullptr };

public:
	virtual ~Component() = default;
	virtual void Init(GameObject* _parent);
	virtual void Update();
	virtual void Draw();
	virtual void Exit();
	virtual ComponentType Get_Component_Type();

	GameObject* Get_Parent();
	void Set_Parent(GameObject* const _parent);
};

