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
#include "Vector2.h"

class BoxCollider2D : public Component
{
public:
    struct AABB
    {
        ToastBox::Vec2 min; // Minimum corner
        ToastBox::Vec2 max; // Maximum corner
    };

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


    /*!*****************************************************************************
      \brief
        Frees and unloads any members that need it.
    *******************************************************************************/
    void Exit() override;


    /*!*****************************************************************************
      \brief
        Gets overridden based on what component this is.

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

private:
    AABB aabb; // The axis-aligned bounding box for this collider
};
