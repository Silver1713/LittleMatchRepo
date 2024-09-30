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
#include "Components/Transform.hpp"
#include "GameObjects.hpp"
#include "Vector2.h"

/*!*****************************************************************************
  \brief
	This function initializes the component along with any BoxCollider specific
	members that need initializing

  \param _parent
	the gameobject that created this component
*******************************************************************************/
void BoxCollider2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
	Transform* transform = dynamic_cast<Transform*>(_parent->Get_Component(ComponentType::TRANSFORM));

	float const* scale = transform->Get_Scale();
	aabb.min_x = -scale[0] / 2;
	aabb.max_x = scale[0] / 2;
	aabb.min_y = -scale[1] / 2;
	aabb.max_y = scale[1] / 2;
}

/*!*****************************************************************************
  \brief
	Space for calls to collision implementation
*******************************************************************************/
void BoxCollider2D::Update()
{
	GameObject* p = Get_Parent();
	Transform* transform = dynamic_cast<Transform*>(Get_Parent()->Get_Component(ComponentType::TRANSFORM));
	aabb.pos_x = transform->Get_Positions()[0];
	aabb.pos_y = transform->Get_Positions()[1];
	float const* scale = transform->Get_Scale();
	aabb.min_x = -scale[0] / 2;
	aabb.max_x = scale[0] / 2;
	aabb.min_y = -scale[1] / 2;
	aabb.max_y = scale[1] / 2;

	aabb.calculate_model_matrix(Get_Parent());


	

}


/*!*****************************************************************************
  \brief
	Frees and unload any members that needs it
*******************************************************************************/
void BoxCollider2D::Exit() {}


ComponentType BoxCollider2D::Get_Component_Type() { return BOXCOLLIDER2D; }


void BoxCollider2D::Register_Collision_Callback(std::function<void(GameObject*)> _callback)
{
	collision_callback = _callback;
}

void BoxCollider2D::onCollide()
{
	if (collision_callback)
	{
		collision_callback(Get_Parent());
		
	}
}



void BoxCollider2D::AABB::calculate_model_matrix(GameObject* _parent)
{
	ToastBox::Vec2 pos = { pos_x, pos_y };
	ToastBox::Vec2 scale = { max_x - min_x, max_y - min_y };

	ToastBox::Matrix3x3 scale_matrix;
	scale_matrix.Matrix3Scale(scale.x, scale.y);

	ToastBox::Matrix3x3 translation_matrix;
	translation_matrix.Matrix3Translate(pos.x, pos.y);


	

	ToastBox::Matrix3x3 model = ~translation_matrix * ~scale_matrix;
	Transform* transform = dynamic_cast<Transform*>(_parent->Get_Component(ComponentType::TRANSFORM));
	
	if (transform)
	{
		model = ~transform->Get_Model_Matrix() * ~model;

	}
	model_matrix = model;
}


bool BoxCollider2D::Get_Debug()
{
	return Debug_Mode;
}


void BoxCollider2D::Set_Debug(bool _debug)
{
	Debug_Mode = _debug;
}
