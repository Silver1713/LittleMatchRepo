/* Start Header ************************************************************************/
/*!
\file		Component.h
\title		
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265
\par		b.muhammadhafiz@digipen.edu
\date		12 September 2024
\brief		

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
	BOXCOLLIDER2D,
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

