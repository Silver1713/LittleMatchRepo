#pragma once
#include "PhysicsBody.h"
#include "Vector2D.h"

namespace MFEngine {
	class PhysicsContact {
	public:
		PhysicsBody* a;
		PhysicsBody* b;

		Vector2D start;
		Vector2D end;

		Vector2D normal;
		float collisionDepth;

		PhysicsContact() = default;
		~PhysicsContact() = default;

		void ResolutionPenetration();
		void ResolutionCollision();
	};
}

