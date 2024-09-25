/* Start Header ************************************************************************/
/*!
\file		Sprite2D.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		11 September 2024
\brief		Contains the derived class Sprite2D that overrides the virtual functions of the
			base class Component to do sprite specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"

class Sprite2D : public Component
{
private:
	std::string sprite_texture_ID{ "" };
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
	void Set_Transparency(float _a);
};
