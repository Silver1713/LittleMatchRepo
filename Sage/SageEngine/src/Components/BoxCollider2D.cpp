/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.cpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
            base class Component to perform collision-specific tasks.

            All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "Components/BoxCollider2D.hpp"
#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/Physics.hpp"
#include "GameObjects.hpp"

#include "Vector2.h"

#include "SageTimer.hpp"


#include <iostream>

// Initialization and Cleanup Functions

/*!*****************************************************************************
  \brief
    This function initializes the component along with any BoxCollider specific
    members that need initializing.

  \param _parent
    the gameobject that created this component
*******************************************************************************/
void BoxCollider2D::Init(GameObject* _parent)
{
	Component::Init(_parent);
	Transform* transform = dynamic_cast<Transform*>(_parent->Get_Component(ComponentType::TRANSFORM));

	float const* scale = transform->Get_Scale();
	aabb.min.x = -scale[0] / 2;
	aabb.max.x = scale[0] / 2;
	aabb.min.y = -scale[1] / 2;
	aabb.max.y = scale[1] / 2;
}

// Update Function

/*!*****************************************************************************
  \brief
    Updates the BoxCollider2D component.
  \param deltaTime
    Time step for the update.
*******************************************************************************/
void BoxCollider2D::Update(float deltaTime)
{
    Transform* transform = static_cast<Transform*>(Get_Parent()->Get_Component(TRANSFORM));
    if (!transform) return;

    // Transform the AABB
    TransformAABB();

    // Check for collisions with other objects
    CheckCollisions(deltaTime);
}
void BoxCollider2D::Update()
{
	GameObject* p = Get_Parent();

    TransformAABB();

	aabb.calculate_model_matrix(Get_Parent());

	

	

}


/*!*****************************************************************************
  \brief
    Frees and unloads any members that need it.
*******************************************************************************/
void BoxCollider2D::Exit() {}


/*!*****************************************************************************
  \brief
    Gets overridden based on what component this is.

  \return
    The enum representing what component this is.
*******************************************************************************/
ComponentType BoxCollider2D::Get_Component_Type()
{
    return BOXCOLLIDER2D;
}


// Collision Handling Functions

/*!****************************************************************************
  \brief
    Checks for collisions with other BoxCollider2D instances using Swept AABB.
  \param deltaTime
    Time step for collision detection.
*******************************************************************************/
void BoxCollider2D::CheckCollisions(float deltaTime)
{
    Transform* transform = static_cast<Transform*>(Get_Parent()->Get_Component(TRANSFORM));
    Physics* physics = static_cast<Physics*>(parent->Get_Component(PHYSICS));

    if (!transform || !physics) return;

    ToastBox::Vec2 velocity = physics->Get_Velocity();
    AABB sweptAABB;

	sweptAABB.min = aabb.min + velocity * deltaTime;
	sweptAABB.max = aabb.max + velocity * deltaTime;

    for (const auto& pair : Game_Objects::Get_Game_Objects())
    {
        GameObject* other = pair.second.get();
        if (other == parent) continue;

        BoxCollider2D* otherCollider = static_cast<BoxCollider2D*>(other->Get_Component(BOXCOLLIDER2D));
        if (!otherCollider) continue;

        // Check for collision with the swept AABB
        if (CheckSweptCollision(sweptAABB, *otherCollider))
        {
            HandleCollision(other);
        }
    }
}

bool BoxCollider2D::CollisionIntersection_RectRect(const AABB& aabb1,          //Input
    const ToastBox::Vec2& vel1,         //Input 
    const AABB& aabb2,          //Input 
    const ToastBox::Vec2& vel2,         //Input
    float& firstTimeOfCollision) //Output: the calculated value of tFirst, below, must be returned here
{
    

    ToastBox::Vec2 vel_rel;

    vel_rel.x = vel2.x - vel1.x;
    vel_rel.y = vel2.y - vel1.y;
    //collision for one side
    // Check if it not colliding with static object
    if (aabb1.max.x < aabb2.min.x) {
        return 0;
    }
    if (aabb1.max.y < aabb2.min.y) {
        return 0;
    }
    //collision for the other side
    if (aabb1.min.x > aabb2.max.x) {
        return 0;
    }
    if (aabb1.min.y > aabb2.max.y) {
        return 0;
    }
    //collided


    //check if it not colliding with dynamic object
    float t_first = 0;
    float t_last = SageTimer::delta_time;

    // for x axis
    //case for vel < 0;
    if (vel_rel.x < 0) {
        //case1
        if (aabb1.min.x > aabb2.max.x) {
            return 0;
        }
        //case4
        if (aabb1.max.x < aabb2.min.x) {
            t_first = std::max<float>(((aabb1.max.x - aabb2.min.x) / vel_rel.x), t_first);
        }
        if (aabb1.min.x < aabb2.max.x) {
            t_last = std::min<float>(((aabb1.min.x - aabb2.max.x) / vel_rel.x), t_last);

        }

        //case for velocity more than 0
    }
    if (vel_rel.x > 0) {
        //case2
        if (aabb1.min.x > aabb2.max.x) {
            t_first = std::max<float>(((aabb1.min.x - aabb2.max.x) / vel_rel.x), t_first);
        }
        if (aabb1.max.x > aabb2.min.x) {
            t_last = std::min<float>(((aabb1.max.x - aabb2.min.x) / vel_rel.x), t_last);
        }
        //case3
        if (aabb1.max.x < aabb2.min.x) {
            return 0;
        }

    }
    //case 5 parallel towards the opposite coordinates
    if (vel_rel.x == 0) {
        if (aabb1.max.x < aabb2.min.x) {
            return 0;
        }
        else if (aabb1.min.x > aabb2.max.x) {
            return 0;
        }
    }
    //case 6
    if (t_first > t_last) {
        return 0;
    }




    // for y axis
    if (vel_rel.y < 0) {
        //case1
        if (aabb1.min.y > aabb2.max.y) {
            return 0;
        }
        //case4
        if (aabb1.max.y < aabb2.min.y) {
            t_first = std::max<float>(((aabb1.max.y - aabb2.min.y) / vel_rel.y), t_first);
        }
        if (aabb1.min.y < aabb2.max.y) {
            t_last = std::min<float>(((aabb1.min.y - aabb2.max.y) / vel_rel.y), t_last);
        }
    }
    //for velocity more than 0
    if (vel_rel.y > 0) {
        //case2
        if (aabb1.min.y > aabb2.max.y) {
            t_first = std::max<float>(((aabb1.min.y - aabb2.max.y) / vel_rel.y), t_first);
        }
        if (aabb1.max.y > aabb2.min.y) {
            t_last = std::min<float>(((aabb1.max.y - aabb2.min.y) / vel_rel.y), t_last);
        }
        //case3
        if (aabb1.max.y < aabb2.min.y) {
            return 0;
        }
    }
    //case 5
    if (vel_rel.y == 0) {
        if (aabb1.max.y < aabb2.min.y) {
            return 0;
        }
        else if (aabb1.min.y > aabb2.max.y) {
            return 0;
        }
    }
    //case 6
    if (t_first > t_last) {
        return 0;
    }



    return true;
}

/*!*****************************************************************************
  \brief
    Handles the response when a collision is detected.
  \param other
    The other GameObject involved in the collision.
*******************************************************************************/
void BoxCollider2D::HandleCollision(GameObject* other)
{
    // Option 1: Use a type identifier if available
    std::cout << "Collision detected between objects of type "
        << typeid(*parent).name() << " and "
        << typeid(*other).name() << std::endl;

    // Stop movement if there's a physics component
    Physics* physics = static_cast<Physics*>(parent->Get_Component(PHYSICS));
    if (physics)
    {
        physics->Get_Velocity().x = 0;
        physics->Get_Velocity().y = 0;
    }
}

/*!****************************************************************************
  \brief
    Checks if the swept AABB intersects with another BoxCollider2D.
  \param sweptAABB
    The swept AABB to check against.
  \param other
    The other BoxCollider2D to check against.
  \return
    True if a collision is detected, false otherwise.
*******************************************************************************/
bool BoxCollider2D::CheckSweptCollision(const BoxCollider2D::AABB& sweptAABB, const BoxCollider2D& other) const
{
    const AABB& otherAABB = other.GetAABB();

    // Check for overlap
    return (sweptAABB.max.x > otherAABB.min.x &&
        sweptAABB.min.x < otherAABB.max.x &&
        sweptAABB.max.y > otherAABB.min.y &&
        sweptAABB.min.y < otherAABB.max.y);
    /*if (sweptAABB.max.x > otherAABB.min.x &&
        sweptAABB.min.x < otherAABB.max.x &&
        sweptAABB.max.y > otherAABB.min.y &&
        sweptAABB.min.y < otherAABB.max.y){
        if(sweptAABB.max.x == swea)*/
}




// AABB Transformation Functions

/*!****************************************************************************
  \brief
    Transforms the AABB based on the object's position and size.
*******************************************************************************/
void BoxCollider2D::TransformAABB()
{
    Transform* transform = static_cast<Transform*>(Get_Parent()->Get_Component(TRANSFORM));

    const float* pos = transform->Get_Positions();
    const float* scale = transform->Get_Scale();

	aabb.center.x = pos[0];
	aabb.center.y = pos[1];

    
    // Calculate min and max based on position and scale
    ToastBox::Vec2 min = { pos[0] - scale[0] / 2.0f, pos[1] - scale[1] / 2.0f};
    ToastBox::Vec2 max = { pos[0] + scale[0] / 2.0f, pos[1] + scale[1] / 2.0f};

    aabb.scale = max - min;

    // Set the AABB with the calculated min and max
    SetAABB(min, max);
}


// AABB Getter and Setter Functions

/*!****************************************************************************
  \brief
    Sets the AABB for this collider.
  \param min
    The minimum bounds of the AABB.
  \param max
    The maximum bounds of the AABB.
*******************************************************************************/
void BoxCollider2D::SetAABB(const ToastBox::Vec2& min, const ToastBox::Vec2& max)
{
    aabb.min = min;
    aabb.max = max;
}



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


void BoxCollider2D::onCollide(BoxCollider2D* collide)
{
	if (collision_callback)
	{
		collision_callback(collide->Get_Parent());
	}

}





void BoxCollider2D::AABB::calculate_model_matrix(GameObject* _parent)
{
	

	ToastBox::Matrix3x3 scale_matrix;
	scale_matrix.Matrix3Scale(scale.x, scale.y);

	ToastBox::Matrix3x3 translation_matrix;
	translation_matrix.Matrix3Translate(center.x, center.y);


	

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



/*!****************************************************************************
  \brief
    Gets the current AABB.
  \return
    A const reference to the AABB representing the min and max corners of the AABB.
*******************************************************************************/
const BoxCollider2D::AABB& BoxCollider2D::GetAABB() const
{
    return aabb;
}
