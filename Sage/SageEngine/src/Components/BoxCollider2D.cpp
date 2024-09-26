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
#include "SageHelper.hpp"
#include "SageRenderer.hpp"
#include "GameObjects.hpp"
#include <algorithm> // for std::clamp
#include <iostream>

// Default constructor initializes width and height to zero
BoxCollider2D::BoxCollider2D()
    : rect{ ToastBox::Vec2::Vec2(0.0f, 0.0f), 0.0f, 0.0f } {}

// Parameterized constructor to initialize size
BoxCollider2D::BoxCollider2D(float width, float height)
    : rect{ ToastBox::Vec2::Vec2(0.0f, 0.0f), width, height } {}

void BoxCollider2D::Init(GameObject* _parent)
{
    Component::Init(_parent);
    UpdatePosition(); // Initialize collider based on current transform
}

void BoxCollider2D::Update() 
{
    UpdatePosition();
    CheckCollisions();
    CheckBoundaryCollisions();
}

void BoxCollider2D::UpdatePosition() {
    // Get the Transform component from the parent object
    Transform* transform = dynamic_cast<Transform*>(Get_Parent()->Get_Component(TRANSFORM));
    if (transform) {
        // Get the position, size, and scale from the Transform component
        const float* positions = transform->Get_Positions();
        const float* size = transform->Get_Scale(); // Assuming scale affects size
        const float* rotation = transform->Get_Rotations();

        // Update collider position
        rect.center.x = positions[0];
        rect.center.y = positions[1];

        // Update collider size based on scale
        rect.width = size[0];
        rect.height = size[1];

        // If rotation needs to be accounted for, apply it in the draw/render logic
    }
}

void BoxCollider2D::CheckCollisions()
{
    auto& gameObjects = Game_Objects::Get_Game_Objects();
    for (auto& obj : gameObjects) {
        GameObject* gameObject = obj.second.get();
        if (gameObject != Get_Parent() && gameObject->Is_Enabled()) {
            auto* otherCollider = dynamic_cast<BoxCollider2D*>(gameObject->Get_Component(BOXCOLLIDER2D));
            if (otherCollider && IsCollidingWith(otherCollider)) {
                HandleCollision(otherCollider);
            }
        }
    }
}

void BoxCollider2D::CheckBoundaryCollisions() {
    bool collisionDetected = false;

    // Check collision with left wall
    if (rect.center.x < SageHelper::GetScreenLeft()) {
        rect.center.x = SageHelper::GetScreenLeft();  // Reposition object inside the screen
        collisionDetected = true;
    }

    // Check collision with right wall
    if (rect.center.x + rect.width > SageHelper::GetScreenRight()) {
        rect.center.x = SageHelper::GetScreenRight() - rect.width;  // Reposition object inside the screen
        collisionDetected = true;
    }

    // Check collision with top wall
    if (rect.center.y < SageHelper::GetScreenTop()) {
        rect.center.y = SageHelper::GetScreenTop();  // Reposition object inside the screen
        collisionDetected = true;
    }

    // Check collision with bottom wall
    if (rect.center.y + rect.height > SageHelper::GetScreenBottom()) {
        rect.center.y = SageHelper::GetScreenBottom() - rect.height;  // Reposition object inside the screen
        collisionDetected = true;
    }

    // Update position if a boundary collision was detected
    if (collisionDetected) {
        Transform* transform = dynamic_cast<Transform*>(Get_Parent()->Get_Component(TRANSFORM));
        if (transform) {
            float newPos[] = { rect.center.x, rect.center.y };
            transform->Set_Positions(newPos);
        }
    }
}

void BoxCollider2D::HandleCollision(BoxCollider2D* other)
{
    // Log or handle the collision
    std::cout << "Collision detected between " << Get_Parent()->Get_ID() <<
        " and " << other->Get_Parent()->Get_ID() << std::endl;
    ResolveCollision(other);
}

void BoxCollider2D::ResolveCollision(BoxCollider2D* other) {
    auto* myTransform = dynamic_cast<Transform*>(Get_Parent()->Get_Component(TRANSFORM));
    if (myTransform) {
        myTransform->Translate({ -1.0f, -1.0f, 0.0f });
    }
}

// Draw the collider rectangle in sync with the object's transform
void BoxCollider2D::Draw() {
    if (rect.width <= 0 || rect.height <= 0) return;
    const Transform* transform = dynamic_cast<const Transform*>(Get_Parent()->Get_Component(TRANSFORM));
    if (!transform) return;
    SageRenderer::DrawDebugRect(rect.center.x, rect.center.y, rect.width, rect.height, glm::vec4(1, 0, 0, 1), 2.0f);
}

bool BoxCollider2D::IsCollidingWith(const BoxCollider2D* other) const
{
    // Simple AABB collision detection using properties from rect
    return rect.center.x < other->rect.center.x + other->rect.width &&
        rect.center.x + rect.width > other->rect.center.x &&
        rect.center.y < other->rect.center.y + other->rect.height &&
        rect.center.y + rect.height > other->rect.center.y;
}

// Getter for X position
float BoxCollider2D::GetX() const 
{
    return rect.center.x;
}

// Getter for Y position
float BoxCollider2D::GetY() const 
{
    return rect.center.y;
}

// Getter for Width
float BoxCollider2D::GetWidth() const 
{
    return rect.width;
}

// Getter for Height
float BoxCollider2D::GetHeight() const 
{
    return rect.height;
}

ComponentType BoxCollider2D::Get_Component_Type()
{
    return BOXCOLLIDER2D;
}

void BoxCollider2D::Exit() {}
