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
	void Set_Transparency(float& _a);
};
