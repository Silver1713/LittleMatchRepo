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

typedef enum {
	COMPONENT,
	TRANSFORM,
	SPRITE2D,
	COLLISION2D,
	AUDIO,
	NUM_OF_TYPES_OF_COMPONENTS
} ComponentType;

class Component
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Exit();
	virtual ComponentType Get_Component_Type();
};

class Transform : public Component
{
private:
	float positions[3]{};
	float rotations[3]{};

public:
	Transform();
	Transform(float const _new_pos[3], float const _new_rot[3]);

	void Init() override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;

	void Set_Positions(float const _new_pos[3]);
	float const* Get_Positions();
	void Set_Rotations(float const _new_rot[3]);
	float const* Get_Rotations();
};

class Sprite2D : public Component
{
private:
	std::string sprite_texture_ID{};

public:
	Sprite2D();
	Sprite2D(std::string _texture_ID);

	void Init() override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
	void Set_Texture_ID(std::string _ID);
};

class Collision2D : public Component
{
	void Init() override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
};

class Audio : public Component
{
	void Init() override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
};

