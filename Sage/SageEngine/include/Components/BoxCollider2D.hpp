/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to do Collision specific tasks

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"
#include <functional>

#include "Matrix3x3.h"


class BoxCollider2D : public Component
{
	std::function<void(GameObject*)> collision_callback{};
	bool Debug_Mode{ false };
	struct AABB
	{
		float pos_x, pos_y; // Center position of the collider in the object's local space
		float min_x, min_y; // Minimum extents of the collider in the object's local space
		float max_x, max_y; // Maximum extents of the collider in the object's local space

		ToastBox::Matrix3x3 model_matrix{};

		void calculate_model_matrix(GameObject* _parent);
	};

public:
	AABB aabb;
	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any BoxCollider specific
		members that need initializing

	  \param _parent
		the gameobject that created this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;


	void Update() override;

	void onCollide();
	void onCollide(BoxCollider2D* collide);
	void Register_Collision_Callback(std::function<void(GameObject*)> _callback);
	/*!*****************************************************************************
	  \brief
		Frees and unload any members that needs it
	*******************************************************************************/
	void Exit() override;

	void Set_Debug(bool _debug);
	bool Get_Debug();

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		the enum representating what component this is
	*******************************************************************************/
	ComponentType Get_Component_Type() override;


	bool Calculate_AABB_Collision(BoxCollider2D* _other);
};
