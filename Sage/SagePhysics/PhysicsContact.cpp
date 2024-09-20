#include "PhysicsContact.h"

namespace MFEngine {
	void PhysicsContact::ResolutionPenetration() {
		if (a->isStatic() && b->isStatic()) {
			return;
		}

		float da = collisionDepth / (a->bodyInverseMass + b->bodyInverseMass) * a->bodyInverseMass;
		float db = collisionDepth / (a->bodyInverseMass + b->bodyInverseMass) * b->bodyInverseMass;

		a->bodyPosition -= normal * da;
		b->bodyPosition += normal * db;
	}

	void PhysicsContact::ResolutionCollision() {
		ResolutionPenetration();

		//Determine restitution and friction
		float e = std::min(a->bodyRestitution, b->bodyRestitution);
		float f = std::min(a->bodyFriction, b->bodyFriction);

		//Calculate relative velocity
		Vector2D ra = end - a->bodyPosition;
		Vector2D rb = start - b->bodyPosition;
		Vector2D va = a->bodyVelocity + Vector2D(-a->bodyAngularVelocity * ra.y, a->bodyAngularVelocity * ra.x);
		Vector2D vb = b->bodyVelocity + Vector2D(-b->bodyAngularVelocity * rb.y, b->bodyAngularVelocity * rb.x);
		const Vector2D velRelative = va - vb;

		//Calculate collision impulse
		//along normal
		float velRelativeNormal = velRelative.dot(normal);
		const Vector2D impulseDirectionN = normal;
		const float impulseMagnitudeN = -(1 + e) * velRelativeNormal / ((a->bodyInverseMass + b->bodyInverseMass) + ra.Cross(normal) * ra.Cross(normal) * a->bodyInverseI + rb.Cross(normal) * rb.Cross(normal) * b->bodyInverseI);
		Vector2D jN = impulseDirectionN * impulseMagnitudeN;

		//along tangent
		Vector2D tan = normal.normal();
		float velRelativeTangent = velRelative.dot(tan);
		const Vector2D impulseDirectionT = tan;
		const float impulseMagnitudeT = f * -(1 + e) * velRelativeTangent / ((a->bodyInverseMass + b->bodyInverseMass) + ra.Cross(tan) * ra.Cross(tan) * a->bodyInverseI + rb.Cross(tan) * rb.Cross(tan) * b->bodyInverseI);
		Vector2D jT = impulseDirectionT * impulseMagnitudeT;

		///calculate final impulse
		Vector2D j = jN + jT;

		//Apply impulse to both objects
		a->ApplyImpulse(j, ra);
		b->ApplyImpulse(-j, rb);

	}
}
