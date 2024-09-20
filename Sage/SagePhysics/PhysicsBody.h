#pragma once
#include"PhysicsShape.h"

namespace MFEngine {
	struct Transform;
	class GameObject;

	class PhysicsBody {
	public:
		//added capital Body infront of all variable to avoid name conflict
		//Linear Motion
		Vector2D bodyPosition, bodyVelocity, bodyAcceleration, bodyForce;
		//Angular Motion
		float bodyRotation, bodyAngularVelocity, bodyAngularAcceleration, bodyTorque;

		float bodyMass;
		float bodyInverseMass{};
		float bodyI;
		float bodyInverseI;

		bool CollidingCheck{ false };

		float bodyRestitution;

		float bodyFriction;

		PhysicsShape* shape = nullptr;

		PhysicsBody(float, float, float);
		~PhysicsBody();

		void BodyForceAdd(const Vector2D& force);
		void BodyTorqueAdd(float tor);
		void BodyForceClear();
		void BodyTorqueClear();

		void BodyIntergrateLinear(float);
		void BodyIntergrateAngular(float);

		bool isStatic() const;
		void ApplyImpulse(const Vector2D& j);
		void ApplyImpulse(const Vector2D& j, const Vector2D& r);

		void bodyUpdate(float dt);

	};

}