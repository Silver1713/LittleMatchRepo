#include "Components/BoxCollider2D.hpp"

void BoxCollider2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
}
void BoxCollider2D::Update() {}
void BoxCollider2D::Exit() {}
ComponentType BoxCollider2D::Get_Component_Type() { return BOXCOLLIDER2D; }