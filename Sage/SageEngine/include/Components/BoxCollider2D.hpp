/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.hpp
\title		Little Match
\author		Jay Lim Jun Xiang, jayjunxiang.lim, 2301335 (50%)
			Edwin Lee Zirui, edwinzirui.lee, 2301299 (50%)
\par		jayjunxiang.lim@digipen.edu
			edwinzirui.lee@digipen.edu
\date		03 October 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to perform collision-specific tasks. The class handles
			initialization, updating, collision detection using AABB (Axis-Aligned Bounding Box)
			with swept tests, and processing collision responses. It utilizes Transform components
			for positioning and Physics components for velocity.

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
	std::function<void(GameObject*)> collision_callback{};  // Callback function for handling collisions
	bool Debug_Mode{ false };  // Boolean to enable/disable debug mode
	struct AABB
	{
		

		ToastBox::Vec2 center; // Center of the AABB

		ToastBox::Vec2 min; // Minimum corner
		ToastBox::Vec2 max; // Maximum corner

		ToastBox::Matrix3x3 model_matrix{};
		ToastBox::Vec2 scale;


		void Calculate_Model_Matrix(GameObject* _parent);
	};

public:
	AABB aabb;

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
	void Update(float _delta_time);

	/*!*****************************************************************************
	  \brief
		A basic update function that only transforms the AABB and calculates the model matrix.
	*******************************************************************************/
	void Update() override;

	/*!*****************************************************************************
	  \brief
		Frees and unloads any members that need it.
	*******************************************************************************/
	void Exit() override;

	/*!*****************************************************************************
	  \brief
		Calls the registered collision callback function when a collision occurs on itself.
	*******************************************************************************/
	void On_Collide();

	/*!*****************************************************************************
	  \brief
		Calls the registered collision callback function when a collision with
		another BoxCollider2D occurs.

	  \param _collide
		The other BoxCollider2D that this collider collided with.
	*******************************************************************************/
	void On_Collide(BoxCollider2D* _collide);

	/*!*****************************************************************************
	  \brief
		Registers a collision callback function for the BoxCollider2D.

	  \param _callback
		A function that will be called when the collider detects a collision.
	*******************************************************************************/
	void Register_Collision_Callback(std::function<void(GameObject*)> _callback);

	/*!*****************************************************************************
	  \brief
		Sets the debug mode for the BoxCollider2D.

	  \param _debug
		Boolean value to enable or disable debug mode.
	*******************************************************************************/
	void Set_Debug(bool _debug);

	/*!*****************************************************************************
	  \brief
		Gets whether the BoxCollider2D is in debug mode.

	  \return
		A boolean indicating whether debug mode is enabled.
	*******************************************************************************/
	bool Get_Debug();

	/*!*****************************************************************************
	  \brief
		Gets overriden based on what component this is

	  \return
		The enum representing what component this is.
	*******************************************************************************/
	ComponentType Get_Component_Type() override;

	/*!****************************************************************************
	  \brief
		Checks for collisions with other BoxCollider2D instances using Swept AABB.
	  \param deltaTime
		Time step for collision detection.
	*******************************************************************************/
	void Check_Collisions(float _delta_time);

	/*!*****************************************************************************
	  \brief
		Handles the response when a collision is detected.
	  \param other
		The other GameObject involved in the collision.
	*******************************************************************************/
	void Handle_Collision(GameObject* _other);

	/*!*****************************************************************************
	  \brief
		Checks if there is a collision with another BoxCollider2D using the AABB method.

	  \param other
		The other BoxCollider2D to check collision with.

	  \return
		True if there is a collision, false otherwise.
	*******************************************************************************/
	bool Check_Swept_Collision(const BoxCollider2D::AABB& _swept_AABB, const BoxCollider2D& _other) const;



	/*!****************************************************************************
	  \brief
		Transforms the AABB based on the object's position and scale.

	  \return
		A pair of Vec2 representing the transformed AABB's min and max corners.
	*******************************************************************************/
	void Transform_AABB();


	/*!****************************************************************************
	  \brief
		Sets the AABB with new min and max values.

	  \param min
		The minimum corner of the AABB.

	  \param max
		The maximum corner of the AABB.
	*******************************************************************************/
	void Set_AABB(const ToastBox::Vec2& _min, const ToastBox::Vec2& _max);


	/*!****************************************************************************
	  \brief
		Gets the current AABB.

	  \return
		A const reference to the AABB representing the min and max corners of the AABB.
	*******************************************************************************/
	const AABB& Get_AABB() const;

	/*!****************************************************************************
	  \brief
		Performs collision detection between two AABBs using relative velocity.
		Determines if two AABBs will collide and calculates the time of collision.

	  \param _aabb1
		The first AABB.
	  \param _vel1
		The velocity of the first AABB.
	  \param _aabb2
		The second AABB.
	  \param _vel2
		The velocity of the second AABB.
	  \param _t_first
		The calculated first time of collision, if any.

	  \return
		True if the AABBs will collide, false otherwise.
	*******************************************************************************/
	bool Collision_Intersection_Rect_Rect(const AABB& _aabb1,          //Input
		const ToastBox::Vec2& _vel1,         //Input 
		const AABB& _aabb2,          //Input 
		const ToastBox::Vec2& _vel2,         //Input
		float& _t_first); //_first_time_of_collision
	
};
