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
	virtual void Init(GameObject* _parent);
	virtual void Update();
	virtual void Draw();
	virtual void Exit();
	virtual ComponentType Get_Component_Type();

	GameObject* Get_Parent();
	void Set_Parent(GameObject* const _parent);
};

class Transform : public Component
{
private:
	float positions[3]{};
	float rotations[3]{};
	float scale[3]{};
	bool is_UI_Element{false};

public:
	Transform();
	Transform(float const* _pos, float const* _rot, float const* _scale, bool _is_UI_element = false);
	Transform(std::initializer_list<float> const& _pos, std::initializer_list<float> const& _rot, std::initializer_list<float> const& _scale);

	void Init(GameObject* _parent) override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;

	void Set_Positions(float const* _new_pos);
	void Set_Positions(std::initializer_list<float> const& _new_pos);
	float const* Get_Positions();
	void Set_Rotations(float const* _new_rot);
	void Set_Rotations(std::initializer_list<float> const& _new_rot);
	float const* Get_Rotations();
	void Set_Scale(float const* _new_scale);
	void Set_Scale(std::initializer_list<float> const& _new_scale);
	float const* Get_Scale();

	void Translate(float const* _delta_pos);
	void Translate(std::initializer_list<float> const& _delta_pos);
	void Rotate(float const* _delta_rot);
	void Rotate(std::initializer_list<float> const& _delta_rot);
	void Scale(float const* _delta_scale);
	void Scale(std::initializer_list<float> const& _delta_scale);

	bool& Is_UI_Element();
};

class Sprite2D : public Component
{
private:
	std::string sprite_texture_ID{""};
	float colour[4]{};
	Transform* transform{ nullptr };
	SageObject* obj{ nullptr };

public:
	Sprite2D();
	Sprite2D(std::string const& _texture_ID, float const* _colour);
	Sprite2D(std::string const& _texture_ID, std::initializer_list<float> const& _colour);

	void Init(GameObject* _parent) override;
	void Update() override;
	void Draw() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
	void Set_Texture_ID(std::string const& _ID);
	void Set_Colour(float const* _new_col);
	void Set_Colour(std::initializer_list<float> const& _new_col);
	void Set_Transparency(float& _a);
};

class BoxCollider2D : public Component
{
	void Init(GameObject* _parent) override;
	void Update() override;
	void Exit() override;
	ComponentType Get_Component_Type() override;
};

