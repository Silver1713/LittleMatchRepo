#pragma once

#include "PhysicsBody.h"
#include "PhysicsContact.h"

namespace PogEngine {
	struct Transform;
	class GameObject;

	class CollisionBody {
	public:
		static bool Colliding(PhysicsBody* a, PhysicsBody* b, PhysicsContact& con);
		static bool CollidingCIRC2CIRC(PhysicsBody* a, PhysicsBody* b, PhysicsContact& con);
		static bool CollidingPOLY2POLY(PhysicsBody* a, PhysicsBody* b, PhysicsContact& con);
		static bool CollidingPOLY2CIRC(PhysicsBody* pol, PhysicsBody* cir, PhysicsContact& con);
	};
}
