/* Start Header ************************************************************************/
/*!
\file		BoxCollider2D.hpp
\title		Little Match
\author		Muhammad Hafiz Bin Onn, b.muhammadhafiz, 2301265 (100%)
\par		b.muhammadhafiz@digipen.edu
\date		10 September 2024
\brief		Contains the derived class BoxCollider2D that overrides the virtual functions of the
			base class Component to do Collision specific tasks

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Components/Component.hpp"
#include "GameObjects.hpp"
#include "Shapes.h"

class BoxCollider2D : public Component
{
private:
	//float x, y;	// position of collider
	//float width, height; // dimension of collider

    ToastBox::Rectangle rect;

public:
    BoxCollider2D(); // Default constructor
    BoxCollider2D(float width, float height); // Parameterized constructor

    // Initialization and lifecycle methods
    void Init(GameObject* _parent) override;   // Initialization with GameObject
    void Update() override;                    // Update method for collision detection
    void Draw() override;                // Draw the collider (for debugging purposes)
    void Exit() override;                      // Cleanup resources if necessary

    // Getter and Setter methods for position and size
    float GetX() const;                        // Get the x position of the collider
    float GetY() const;                        // Get the y position of the collider
    float GetWidth() const;                    // Get the width of the collider
    float GetHeight() const;                   // Get the height of the collider

    // Collision detection functions
    void UpdatePosition();                     // Update the position based on the parent transform
    void CheckCollisions();                    // Check for collisions with other colliders
    void CheckBoundaryCollisions();            // Check for collisions with screen boundaries
    bool IsCollidingWith(const BoxCollider2D* other) const; // Check collision with another collider
    void HandleCollision(BoxCollider2D* other); // Handle the collision event
    void ResolveCollision(BoxCollider2D* other); // Specific collision resolution logic

    ComponentType Get_Component_Type() override;  // Return component type
};