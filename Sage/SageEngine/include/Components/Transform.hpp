/* Start Header ************************************************************************/
/*!
\file		Transform.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class Transform that overrides the virtual functions of the
			base class Component to do transform specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"
#include "Vector3.h"

class Transform : public Component
{
private:
	float positions[3]{};
	float rotations[3]{};
	float scale[3]{};
	bool is_UI_Element{ false };

public:
	ToastBox::Vec3 position{};
	ToastBox::Vec3 rotation{};
	ToastBox::Vec3 scaling{};

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
