/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.cpp
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

#include "Components/BoxCollider2D.hpp"
#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/RigidBody.hpp"
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
    Transform* transform = static_cast<Transform*>(_parent->Get_Component<Transform>());

	ToastBox::Vec3 scale = transform->Get_Scale();
	aabb.min.x = -scale.x / 2;
	aabb.max.x = scale.x / 2;
	aabb.min.y = -scale.y / 2;
	aabb.max.y = scale.y / 2;
}

// Update Function

/*!*****************************************************************************
  \brief
    Updates the BoxCollider2D component.
  \param deltaTime
    Time step for the update.
*******************************************************************************/
void BoxCollider2D::Update(float _delta_time)
{
    if (!is_enabled) { return; }
    Transform* transform = static_cast<Transform*>(Get_Parent()->Get_Component<Transform>());
    if (!transform) return;

    // Transform the AABB
    Transform_AABB();

    // Check for collisions with other objects
    Check_Collisions(_delta_time);
}


/*!*****************************************************************************
  \brief
    A basic update function that only transforms the AABB and calculates the model matrix.
*******************************************************************************/
void BoxCollider2D::Update()
{
    Transform_AABB();

	aabb.Calculate_Model_Matrix(Get_Parent());

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
void BoxCollider2D::Check_Collisions(float _delta_time)
{
    Transform* transform = static_cast<Transform*>(Get_Parent()->Get_Component<Transform>());
    RigidBody* physics = static_cast<RigidBody*>(Get_Parent()->Get_Component<RigidBody>());

    if (!transform || !physics) return;

    ToastBox::Vec2 velocity = physics->Get_Current_Velocity();
    AABB swept_AABB;

	swept_AABB.min = aabb.min + velocity * _delta_time;
	swept_AABB.max = aabb.max + velocity * _delta_time;

    for (const auto& pair : Game_Objects::Get_Game_Objects())
    {
        GameObject* other = pair.second.get();
        if (other == parent) continue;

        BoxCollider2D* other_collider = static_cast<BoxCollider2D*>(other->Get_Component<BoxCollider2D>());
        if (!other_collider) continue;

        float t_first = 0.0f;  // Time of first potential collision

        // Use the Check_Swept_Collision method to handle the actual swept volume check
        if (Check_Swept_Collision(swept_AABB, *other_collider))
        {
            // Calculate or determine the collision time if needed
            Handle_Collision(other, t_first, _delta_time);
        }
    }
}

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

bool BoxCollider2D::Collision_Intersection_Rect_Rect(const AABB& _aabb1,          //Input
    const ToastBox::Vec2& _vel1,         //Input 
    const AABB& _aabb2,          //Input 
    const ToastBox::Vec2& _vel2,         //Input
    float& _t_first) //Output: the calculated value of tFirst, below, must be returned here
{
    

    ToastBox::Vec2 vel_rel;

    vel_rel.x = _vel2.x - _vel1.x;
    vel_rel.y = _vel2.y - _vel1.y;
    //collision for one side
    // Check if it not colliding with static object
    if (_aabb1.max.x < _aabb2.min.x) {
        return 0;
    }
    if (_aabb1.max.y < _aabb2.min.y) {
        return 0;
    }
    //collision for the other side
    if (_aabb1.min.x > _aabb2.max.x) {
        return 0;
    }
    if (_aabb1.min.y > _aabb2.max.y) {
        return 0;
    }
    //collided


    //check if it not colliding with dynamic object
    //float _t_first = 0;
    float t_last = static_cast<float>(SageTimer::delta_time);

    // for x axis
    //case for vel < 0;
    if (vel_rel.x < 0) {
        //case1
        if (_aabb1.min.x > _aabb2.max.x) {
            return 0;
        }
        //case4
        if (_aabb1.max.x < _aabb2.min.x) {
            _t_first = std::max<float>(((_aabb1.max.x - _aabb2.min.x) / vel_rel.x), _t_first);
        }
        if (_aabb1.min.x < _aabb2.max.x) {
            t_last = std::min<float>(((_aabb1.min.x - _aabb2.max.x) / vel_rel.x), t_last);

        }

        //case for velocity more than 0
    }
    if (vel_rel.x > 0) {
        //case2
        if (_aabb1.min.x > _aabb2.max.x) {
            _t_first = std::max<float>(((_aabb1.min.x - _aabb2.max.x) / vel_rel.x), _t_first);
        }
        if (_aabb1.max.x > _aabb2.min.x) {
            t_last = std::min<float>(((_aabb1.max.x - _aabb2.min.x) / vel_rel.x), t_last);
        }
        //case3
        if (_aabb1.max.x < _aabb2.min.x) {
            return 0;
        }

    }
    //case 5 parallel towards the opposite coordinates
    if (vel_rel.x == 0) {
        if (_aabb1.max.x < _aabb2.min.x) {
            return 0;
        }
        else if (_aabb1.min.x > _aabb2.max.x) {
            return 0;
        }
    }
    //case 6
    if (_t_first > t_last) {
        return 0;
    }




    // for y axis
    if (vel_rel.y < 0) {
        //case1
        if (_aabb1.min.y > _aabb2.max.y) {
            return 0;
        }
        //case4
        if (_aabb1.max.y < _aabb2.min.y) {
            _t_first = std::max<float>(((_aabb1.max.y - _aabb2.min.y) / vel_rel.y), _t_first);
        }
        if (_aabb1.min.y < _aabb2.max.y) {
            t_last = std::min<float>(((_aabb1.min.y - _aabb2.max.y) / vel_rel.y), t_last);
        }
    }
    //for velocity more than 0
    if (vel_rel.y > 0) {
        //case2
        if (_aabb1.min.y > _aabb2.max.y) {
            _t_first = std::max<float>(((_aabb1.min.y - _aabb2.max.y) / vel_rel.y), _t_first);
        }
        if (_aabb1.max.y > _aabb2.min.y) {
            t_last = std::min<float>(((_aabb1.max.y - _aabb2.min.y) / vel_rel.y), t_last);
        }
        //case3
        if (_aabb1.max.y < _aabb2.min.y) {
            return 0;
        }
    }
    //case 5
    if (vel_rel.y == 0) {
        if (_aabb1.max.y < _aabb2.min.y) {
            return 0;
        }
        else if (_aabb1.min.y > _aabb2.max.y) {
            return 0;
        }
    }
    //case 6
    if (_t_first > t_last) {
        return 0;
    }



    return true;
}

// code used in M1 (forcifully stop upon collision)
///*!**************************************************************************
//\brief
//  Handles the response when a collision is detected.
//\param other - The other GameObject involved in the collision.
//\param collisionTime - The time at which the collision occurred within the frame.
//\param deltaTime - The total time of the current frame.
//***************************************************************************/
//void BoxCollider2D::Handle_Collision(GameObject* _other, float _collision_time, float _delta_time)
//{
//    // Option 1: Use a type identifier if available
//    std::cout << "Collision detected between objects of type "
//        << typeid(*parent).name() << " and "
//        << typeid(*_other).name() << std::endl;
//
//    // Retrieve the physics component
//    RigidBody* physics = static_cast<RigidBody*>(parent->Get_Component<RigidBody>());
//    if (physics)
//    {
//        // Calculate the movement that occurred after the collision
//        float remainingTime = _delta_time - _collision_time;
//
//        ToastBox::Vec2 movementAfterCollision = {
//            physics->Get_Current_Velocity().x * remainingTime,
//            physics->Get_Current_Velocity().y * remainingTime
//        };
//
//        // Update the position to remove any movement after the collision
//        Transform* transform = static_cast<Transform*>(parent->Get_Component<Transform>());
//        if (transform)
//        {
//            ToastBox::Vec3 pos = transform->Get_Position();
//            pos.x -= movementAfterCollision.x;
//            pos.y -= movementAfterCollision.y;
//            transform->Set_Position(pos);
//        }
//
//        // Set velocity to zero to stop all movement
//        physics->Set_Current_Velocity({ 0, 0 });
//    }
//}


// old time based version without any forces by edwin
/*!**************************************************************************
\brief
  Handles the response when a collision is detected.
\param other - The other GameObject involved in the collision.
\param collisionTime - The time at which the collision occurred within the frame.
\param deltaTime - The total time of the current frame.
***************************************************************************/
//void BoxCollider2D::Handle_Collision(GameObject* _other, float _collision_time, float _delta_time)
//{
//    RigidBody* physics = static_cast<RigidBody*>(parent->Get_Component<RigidBody>());
//    if (!physics) return;
//
//    // Get current velocity and calculate remaining time
//    ToastBox::Vec2 currentVelocity = physics->Get_Current_Velocity();
//    float remainingTime = _delta_time - _collision_time;
//
//    // Calculate deceleration rate based on remaining time
//    ToastBox::Vec2 deceleration = currentVelocity / remainingTime;
//
//    // Update position to collision point
//    Transform* transform = static_cast<Transform*>(parent->Get_Component<Transform>());
//    if (transform)
//    {
//        // Move to collision point
//        ToastBox::Vec3 collisionPosition = {
//            transform->Get_Position().x + currentVelocity.x * _collision_time,
//            transform->Get_Position().y + currentVelocity.y * _collision_time,
//            transform->Get_Position().z
//        };
//        transform->Set_Position(collisionPosition);
//
//        // Gradually reduce velocity over remaining time
//        ToastBox::Vec2 newVelocity = {
//            currentVelocity.x - (deceleration.x * remainingTime),
//            currentVelocity.y - (deceleration.y * remainingTime)
//        };
//
//        physics->Set_Current_Velocity(newVelocity);
//    }
//}


/*!**************************************************************************
\brief
  Handles the response when a collision is detected between the parent GameObject and another GameObject.
\param _other - The other GameObject involved in the collision.
\param _collision_time - The time at which the collision occurred within the frame.
\param _delta_time - The total time of the current frame.
***************************************************************************/
//void BoxCollider2D::Handle_Collision(GameObject* _other, float _collision_time, float _delta_time)
//{
//    // Get physics components
//    RigidBody* physics = static_cast<RigidBody*>(parent->Get_Component<RigidBody>());
//    RigidBody* other_physics = static_cast<RigidBody*>(_other->Get_Component<RigidBody>());
//
//    // Early return if any physics component is missing or has zero mass
//    if (!physics || !other_physics || physics->Get_Mass() <= 0.0f || other_physics->Get_Mass() <= 0.0f) {
//        return;
//    }
//
//    // Get transform components
//    Transform* transform = static_cast<Transform*>(parent->Get_Component<Transform>());
//    Transform* other_transform = static_cast<Transform*>(_other->Get_Component<Transform>());
//
//    if (!transform || !other_transform) {
//        return;
//    }
//
//    // Calculate time segments
//    float remaining_time = _delta_time - _collision_time;
//
//    // Move objects to collision point
//    ToastBox::Vec2 pre_collision_vel = physics->Get_Current_Velocity();
//    ToastBox::Vec2 other_pre_collision_vel = other_physics->Get_Current_Velocity();
//
//    // Update positions to collision point
//    ToastBox::Vec3 collision_pos = transform->Get_Position();
//    collision_pos.x += pre_collision_vel.x * _collision_time;
//    collision_pos.y += pre_collision_vel.y * _collision_time;
//    transform->Set_Position(collision_pos);
//
//    ToastBox::Vec3 other_collision_pos = other_transform->Get_Position();
//    other_collision_pos.x += other_pre_collision_vel.x * _collision_time;
//    other_collision_pos.y += other_pre_collision_vel.y * _collision_time;
//    other_transform->Set_Position(other_collision_pos);
//
//    // Calculate collision properties at collision point
//    ToastBox::Vec2 relative_velocity = other_pre_collision_vel - pre_collision_vel;
//
//    // Calculate collision normal
//    ToastBox::Vec2 difference(collision_pos.x - other_collision_pos.x,
//        collision_pos.y - other_collision_pos.y);
//    ToastBox::Vec2 collision_normal;
//
//    if (difference.Magnitude() > 0.0001f) {
//        difference.Normalize(collision_normal, difference);
//
//        // Calculate impulse using restitution
//        float restitution = std::min(physics->Get_Restitution(), other_physics->Get_Restitution());
//        float impulse_scalar = -(1.0f + restitution) * relative_velocity.Product_Scalar(collision_normal);
//        impulse_scalar /= (1.0f / physics->Get_Mass() + 1.0f / other_physics->Get_Mass());
//
//        // Calculate new velocities after collision
//        ToastBox::Vec2 impulse = collision_normal * impulse_scalar;
//        ToastBox::Vec2 new_velocity = pre_collision_vel + (impulse / physics->Get_Mass());
//        ToastBox::Vec2 other_new_velocity = other_pre_collision_vel - (impulse / other_physics->Get_Mass());
//
//        // Handle friction
//        float friction_coeff = std::min(physics->Get_Friction(), other_physics->Get_Friction());
//        float normal_velocity_mag = relative_velocity.Product_Scalar(collision_normal);
//        ToastBox::Vec2 tangent_velocity = relative_velocity - (collision_normal * normal_velocity_mag);
//
//        if (tangent_velocity.Magnitude() > 0.0001f) {
//            ToastBox::Vec2 friction_direction;
//            tangent_velocity.Normalize(friction_direction, tangent_velocity);
//
//            float friction_impulse_mag = -friction_coeff * impulse_scalar;
//            ToastBox::Vec2 friction_impulse = friction_direction * friction_impulse_mag;
//
//            new_velocity = new_velocity + (friction_impulse / physics->Get_Mass());
//            other_new_velocity = other_new_velocity - (friction_impulse / other_physics->Get_Mass());
//        }
//
//        // Apply new velocities
//        physics->Set_Current_Velocity(new_velocity);
//        other_physics->Set_Current_Velocity(other_new_velocity);
//
//        // Move objects for remaining time after collision with new velocities
//        if (remaining_time > 0.0f) {
//            ToastBox::Vec3 final_pos = transform->Get_Position();
//            final_pos.x += new_velocity.x * remaining_time;
//            final_pos.y += new_velocity.y * remaining_time;
//            transform->Set_Position(final_pos);
//
//            ToastBox::Vec3 other_final_pos = other_transform->Get_Position();
//            other_final_pos.x += other_new_velocity.x * remaining_time;
//            other_final_pos.y += other_new_velocity.y * remaining_time;
//            other_transform->Set_Position(other_final_pos);
//        }
//    }
//
//    // Trigger collision callbacks
//    On_Collide(static_cast<BoxCollider2D*>(_other->Get_Component<BoxCollider2D>()));
//}


/*!**************************************************************************
\brief
  Handles the response when a collision is detected between the parent GameObject and another GameObject.
\param _other - The other GameObject involved in the collision.
\param _collision_time - The time at which the collision occurred within the frame.
\param _delta_time - The total time of the current frame.
***************************************************************************/
void BoxCollider2D::Handle_Collision(GameObject* _other, float _collision_time, float _delta_time)
{
    // Get physics components
    RigidBody* physics = static_cast<RigidBody*>(parent->Get_Component<RigidBody>());
    RigidBody* other_physics = static_cast<RigidBody*>(_other->Get_Component<RigidBody>());

    // Get transform components
    Transform* transform = static_cast<Transform*>(parent->Get_Component<Transform>());
    Transform* other_transform = static_cast<Transform*>(_other->Get_Component<Transform>());

    // Basic validation
    if (!physics || !transform || !other_transform) return;

    // Check if this is a dynamic-static collision
    bool is_static_collision = !other_physics || other_physics->Get_Mass() <= 0.0f;

    if (is_static_collision) {
        // Dynamic-Static Collision
        ToastBox::Vec2 curr_vel = physics->Get_Current_Velocity();
        ToastBox::Vec3 prev_pos = transform->Get_Prev_Position();
        ToastBox::Vec3 curr_pos = transform->Get_Position();
        ToastBox::Vec3 movement_dir = curr_pos - prev_pos;

        // Calculate collision properties
        auto& moving_box = Get_AABB();
        auto& static_box = _other->Get_Component<BoxCollider2D>()->Get_AABB();

        float overlap_x = std::min(moving_box.max.x, static_box.max.x)
            - std::max(moving_box.min.x, static_box.min.x);
        float overlap_y = std::min(moving_box.max.y, static_box.max.y)
            - std::max(moving_box.min.y, static_box.min.y);

        bool is_horizontal_collision = overlap_x < overlap_y;
        float restitution = physics->Get_Restitution();
        float impulse_mag = curr_vel.Magnitude();

        // Position at collision time
        ToastBox::Vec3 collision_pos = curr_pos;
        collision_pos.x = prev_pos.x + curr_vel.x * _collision_time;
        collision_pos.y = prev_pos.y + curr_vel.y * _collision_time;
        transform->Set_Position(collision_pos);

        // Calculate bounce response
        if (is_horizontal_collision) {
            float bounce_vel = impulse_mag * restitution;
            physics->Get_Current_Velocity().x = (movement_dir.x > 0) ? -bounce_vel : bounce_vel;
        }
        else {
            float bounce_vel = impulse_mag * restitution;
            physics->Get_Current_Velocity().y = (movement_dir.y > 0) ? -bounce_vel : bounce_vel;
        }

        // Apply friction
        float friction = physics->Get_Friction();
        if (!is_horizontal_collision) {
            physics->Get_Current_Velocity().x *= (1.0f - friction * _delta_time);
        }

        // Move for remaining time with new velocity
        float remaining_time = _delta_time - _collision_time;
        if (remaining_time > 0.0f) {
            ToastBox::Vec2 new_vel = physics->Get_Current_Velocity();
            transform->Set_Position({
                collision_pos.x + new_vel.x * remaining_time,
                collision_pos.y + new_vel.y * remaining_time,
                collision_pos.z
                });
        }
    }
    else {
        // Dynamic-Dynamic Collision
        if (physics->Get_Mass() <= 0.0f || other_physics->Get_Mass() <= 0.0f) {
            return;
        }

        // Calculate time segments
        float remaining_time = _delta_time - _collision_time;

        // Move objects to collision point
        ToastBox::Vec2 pre_collision_vel = physics->Get_Current_Velocity();
        ToastBox::Vec2 other_pre_collision_vel = other_physics->Get_Current_Velocity();

        // Update positions to collision point
        ToastBox::Vec3 collision_pos = transform->Get_Position();
        collision_pos.x += pre_collision_vel.x * _collision_time;
        collision_pos.y += pre_collision_vel.y * _collision_time;
        transform->Set_Position(collision_pos);

        ToastBox::Vec3 other_collision_pos = other_transform->Get_Position();
        other_collision_pos.x += other_pre_collision_vel.x * _collision_time;
        other_collision_pos.y += other_pre_collision_vel.y * _collision_time;
        other_transform->Set_Position(other_collision_pos);

        // Calculate collision properties
        ToastBox::Vec2 relative_velocity = other_pre_collision_vel - pre_collision_vel;
        ToastBox::Vec2 difference(collision_pos.x - other_collision_pos.x,
            collision_pos.y - other_collision_pos.y);
        ToastBox::Vec2 collision_normal;

        if (difference.Magnitude() > 0.0001f) {
            difference.Normalize(collision_normal, difference);

            // Calculate impulse using restitution
            float restitution = std::min(physics->Get_Restitution(), other_physics->Get_Restitution());
            float impulse_scalar = -(1.0f + restitution) * relative_velocity.Product_Scalar(collision_normal);
            impulse_scalar /= (1.0f / physics->Get_Mass() + 1.0f / other_physics->Get_Mass());

            // Calculate new velocities
            ToastBox::Vec2 impulse = collision_normal * impulse_scalar;
            ToastBox::Vec2 new_velocity = pre_collision_vel + (impulse / physics->Get_Mass());
            ToastBox::Vec2 other_new_velocity = other_pre_collision_vel - (impulse / other_physics->Get_Mass());

            // Handle friction
            float friction_coeff = std::min(physics->Get_Friction(), other_physics->Get_Friction());
            float normal_velocity_mag = relative_velocity.Product_Scalar(collision_normal);
            ToastBox::Vec2 tangent_velocity = relative_velocity - (collision_normal * normal_velocity_mag);

            if (tangent_velocity.Magnitude() > 0.0001f) {
                ToastBox::Vec2 friction_direction;
                tangent_velocity.Normalize(friction_direction, tangent_velocity);

                float friction_impulse_mag = -friction_coeff * impulse_scalar;
                ToastBox::Vec2 friction_impulse = friction_direction * friction_impulse_mag;

                new_velocity = new_velocity + (friction_impulse / physics->Get_Mass());
                other_new_velocity = other_new_velocity - (friction_impulse / other_physics->Get_Mass());
            }

            // Apply new velocities
            physics->Set_Current_Velocity(new_velocity);
            other_physics->Set_Current_Velocity(other_new_velocity);

            // Move for remaining time
            if (remaining_time > 0.0f) {
                ToastBox::Vec3 final_pos = transform->Get_Position();
                final_pos.x += new_velocity.x * remaining_time;
                final_pos.y += new_velocity.y * remaining_time;
                transform->Set_Position(final_pos);

                ToastBox::Vec3 other_final_pos = other_transform->Get_Position();
                other_final_pos.x += other_new_velocity.x * remaining_time;
                other_final_pos.y += other_new_velocity.y * remaining_time;
                other_transform->Set_Position(other_final_pos);
            }
        }
    }

    // Trigger collision callbacks
    On_Collide(static_cast<BoxCollider2D*>(_other->Get_Component<BoxCollider2D>()));
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
bool BoxCollider2D::Check_Swept_Collision(const BoxCollider2D::AABB& _swept_AABB, const BoxCollider2D& _other) const
{
    const AABB& other_AABB = _other.Get_AABB();

    // Check for overlap
    return (_swept_AABB.max.x > other_AABB.min.x &&
        _swept_AABB.min.x < other_AABB.max.x &&
        _swept_AABB.max.y > other_AABB.min.y &&
        _swept_AABB.min.y < other_AABB.max.y);

}


// AABB Transformation Functions

/*!****************************************************************************
  \brief
    Transforms the AABB based on the object's position and size.
*******************************************************************************/
void BoxCollider2D::Transform_AABB()
{
    Transform* transform = static_cast<Transform*>(Get_Parent()->Get_Component<Transform>());

    ToastBox::Vec3 pos = transform->Get_Position();
    ToastBox::Vec3 scale = transform->Get_Scale();

	aabb.center.x = pos.x;
	aabb.center.y = pos.y;

    
    // Calculate min and max based on position and scale
    ToastBox::Vec2 min = { pos.x - scale.x / 2.0f, pos.y - scale.y / 2.0f};
    ToastBox::Vec2 max = { pos.x + scale.x / 2.0f, pos.y + scale.y / 2.0f};

    aabb.scale = max - min;

    // Set the AABB with the calculated min and max
    Set_AABB(min, max);
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
void BoxCollider2D::Set_AABB(const ToastBox::Vec2& _min, const ToastBox::Vec2& _max)
{
    aabb.min = _min;
    aabb.max = _max;
}


/*!*****************************************************************************
  \brief
    Registers a collision callback function for the BoxCollider2D.

  \param _callback
    A function that will be called when the collider detects a collision.
*******************************************************************************/
void BoxCollider2D::Register_Collision_Callback(std::function<void(GameObject*)> _callback)
{
	collision_callback = _callback;
}
/*!*****************************************************************************
  \brief
    Calls the registered collision callback function when a collision occurs on itself.
*******************************************************************************/
void BoxCollider2D::On_Collide()
{
	if (collision_callback)
	{
		collision_callback(Get_Parent());
		
	}
}

/*!*****************************************************************************
  \brief
    Calls the registered collision callback function when a collision with
    another BoxCollider2D occurs.

  \param _collide
    The other BoxCollider2D that this collider collided with.
*******************************************************************************/
void BoxCollider2D::On_Collide(BoxCollider2D* _collide)
{
	if (collision_callback)
	{
		collision_callback(_collide->Get_Parent());
	}

}

/*!****************************************************************************
  \brief
    Calculates and sets the model matrix for the AABB based on the parent object's transform.

  \param _parent
    The parent GameObject whose transform is used for the calculation.
*******************************************************************************/

void BoxCollider2D::AABB::Calculate_Model_Matrix(GameObject* _parent)
{
	

	ToastBox::Matrix3x3 scale_matrix;
	scale_matrix.Matrix3Scale(scale.x, scale.y);

	ToastBox::Matrix3x3 translation_matrix;
	translation_matrix.Matrix3Translate(center.x, center.y);


	

	ToastBox::Matrix3x3 model = ~translation_matrix * ~scale_matrix;
	Transform* transform = static_cast<Transform*>(_parent->Get_Component<Transform>());
	
	if (transform)
	{
		model = ~transform->Get_Model_Matrix() * ~model;

	}
	model_matrix = model;
}

/*!*****************************************************************************
  \brief
    Gets whether the BoxCollider2D is in debug mode.

  \return
    A boolean indicating whether debug mode is enabled.
*******************************************************************************/
bool BoxCollider2D::Get_Debug()
{
	return Debug_Mode;
}

/*!*****************************************************************************
  \brief
    Sets the debug mode for the BoxCollider2D.

  \param _debug
    Boolean value to enable or disable debug mode.
*******************************************************************************/
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
const BoxCollider2D::AABB& BoxCollider2D::Get_AABB() const
{
    return aabb;
}
