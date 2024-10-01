/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to perform collision-specific tasks.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#pragma once

#include "Components/Component.hpp"
#include <functional>
#include "Vector2.h"

#include "Matrix3x3.h"


class BoxCollider2D : public Component
{
	std::function<void(GameObject*)> collision_callback{};
	bool Debug_Mode{ false };
	struct AABB
	{
		

		ToastBox::Vec2 center; // Center of the AABB

		ToastBox::Vec2 min; // Minimum corner
		ToastBox::Vec2 max; // Maximum corner

		ToastBox::Matrix3x3 model_matrix{};
		ToastBox::Vec2 scale;
		/*AABB();
		AABB(const ToastBox::Vec2& min, const ToastBox::Vec2& max);
		AABB(const ToastBox::Vec2& pos, const ToastBox::Vec2& scale);*/


		void calculate_model_matrix(GameObject* _parent);
	};

public:
	AABB aabb;
	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any BoxCollider specific
		members that need initializing


	/*!*****************************************************************************
	  \brief
		This function initializes the component along with any BoxCollider specific
		members that need initializing.

	  \param _parent
		the gameobject that created this component
	*******************************************************************************/
	void Init(GameObject* _parent) override;


	/*!*****************************************************************************
	  \brief
		Updates the BoxCollider2D component.
	*******************************************************************************/
	void Update(float deltaTime);

	void Update() override;


	/*!*****************************************************************************
	  \brief
		Frees and unloads any members that need it.
	*******************************************************************************/
	void Exit() override;
	void onCollide();
	void onCollide(BoxCollider2D* collide);
	void Register_Collision_Callback(std::function<void(GameObject*)> _callback);


	void Set_Debug(bool _debug);
	bool Calculate_AABB_Collision(BoxCollider2D* _other);
	bool Get_Debug();

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		The enum representing what component this is.
	*******************************************************************************/
	ComponentType Get_Component_Type() override;

	void CheckCollisions(float deltaTime);

	void HandleCollision(GameObject* other);

	/*!*****************************************************************************
	  \brief
		Checks if there is a collision with another BoxCollider2D using the AABB method.

	  \param other
		The other BoxCollider2D to check collision with.

	  \return
		True if there is a collision, false otherwise.
	*******************************************************************************/
	bool CheckSweptCollision(const BoxCollider2D::AABB& sweptAABB, const BoxCollider2D& other) const;



	/*!****************************************************************************
	  \brief
		Transforms the AABB based on the object's position and scale.

	  \return
		A pair of Vec2 representing the transformed AABB's min and max corners.
	*******************************************************************************/
	void TransformAABB();


	/*!****************************************************************************
	  \brief
		Sets the AABB with new min and max values.

	  \param min
		The minimum corner of the AABB.

	  \param max
		The maximum corner of the AABB.
	*******************************************************************************/
	void SetAABB(const ToastBox::Vec2& min, const ToastBox::Vec2& max);


	/*!****************************************************************************
	  \brief
		Gets the current AABB.

	  \return
		A const reference to the AABB representing the min and max corners of the AABB.
	*******************************************************************************/
	const AABB& GetAABB() const;

	bool CollisionIntersection_RectRect(const AABB& aabb1,          //Input
		const ToastBox::Vec2& vel1,         //Input 
		const AABB& aabb2,          //Input 
		const ToastBox::Vec2& vel2,         //Input
		float& firstTimeOfCollision);
	
};


bool Calculate_AABB_Collision(BoxCollider2D * _other);
