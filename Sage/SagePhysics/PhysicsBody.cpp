#include "PhysicsBody.h"
#include "Vector2D.h"

namespace MFEngine {
	PhysicsBody::PhysicsBody(float x, float y, float m) {
		shape = shape->Clone();
		bodyPosition = Vector2D(x, y);
		bodyVelocity = Vector2D(x, y);
		bodyAcceleration = Vector2D(x, y);
		bodyRotation = 0.0;
		bodyAngularVelocity = 0.0;
		bodyAngularAcceleration = 0.0;
		bodyForce = Vector2D(0, 0);
		bodyTorque = 0.0;
		bodyRestitution = 1.0;
		bodyFriction = 0.7f;
		bodyMass = m;
		if (m != 0.0) {
			bodyInverseMass = static_cast<float>(1.0 / m);
		}
		else {
			bodyInverseMass = static_cast<float>(0.0);
		}
		bodyI = shape->GetInertia() * bodyMass;
		if (bodyI != 0.0) {
			bodyInverseI = static_cast<float>(1.0 / bodyI);
		}
		else {
			bodyInverseI = static_cast<float>(0.0);
		}

	}

	bool PhysicsBody::isStatic() const {
		const float epsilon = 0.005f;
		return fabs(bodyInverseMass - 0.0) < epsilon;
	}

	PhysicsBody::~PhysicsBody() {
		delete shape;
	}

	void PhysicsBody::BodyForceAdd(const Vector2D& force) {
		bodyForce += force;
		;
	}

	void PhysicsBody::BodyTorqueAdd(float tor) {
		bodyTorque += tor;
	}

	void PhysicsBody::BodyForceClear() {
		bodyForce = Vector2D(0.0, 0.0);
	}

	void PhysicsBody::BodyTorqueClear() {
		bodyTorque = 0.0;
	}

	void PhysicsBody::BodyIntergrateLinear(float dt) {
		if (isStatic()) {
			return;
		}
		//Acceleration = Force * InverseMass;
		bodyAcceleration = bodyForce * bodyInverseMass;

		//Integrate the acceleration to find new velocity of object
		bodyVelocity += bodyAcceleration * dt;

		bodyPosition += bodyVelocity * dt;

		BodyForceClear();
	}

	void PhysicsBody::BodyIntergrateAngular(float dt) {
		if (isStatic()) {
			return;
		}
		//Angular acceleration = torque * inverse inertia
		bodyAngularAcceleration = bodyTorque * bodyInverseI;

		//Intergrate angular acceleration to find angular velocity
		bodyAngularVelocity += bodyAngularAcceleration * dt;

		//Intergrate angular velocity to find new rotational angle
		bodyRotation += bodyAngularVelocity * dt;

		BodyTorqueClear();
	}

	void PhysicsBody::ApplyImpulse(const Vector2D& j) {
		if (isStatic()) {
			return;
		}
		bodyVelocity += j * bodyInverseMass;
	}

	void PhysicsBody::ApplyImpulse(const Vector2D& j, const Vector2D& r) {
		if (isStatic()) {
			return;
		}
		bodyVelocity += j * bodyInverseMass;
		bodyAngularVelocity += r.cross(j) * bodyInverseI;
	}

	void PhysicsBody::bodyUpdate(float dt) {
		BodyIntergrateLinear(dt);
		BodyIntergrateAngular(dt);
		bool polygonCheck = shape->GetType() == ShapeType::POLYGON || shape->GetType() == ShapeType::BOX;
		if (polygonCheck) {
			PhysicsShapePolygon* polygonShape = (PhysicsShapePolygon*)shape;
			polygonShape->updateVertices(bodyRotation, bodyPosition);
		}
	}
}