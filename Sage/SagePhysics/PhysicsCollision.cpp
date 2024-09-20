#include "PhysicsCollision.h"

namespace PogEngine {
	bool CollisionBody::Colliding(PhysicsBody* a, PhysicsBody* b, PhysicsContact& contact) {
		bool aCircleCheck = a->shape->GetType() == ShapeType::CIRCLE;
		bool bCircleCheck = b->shape->GetType() == ShapeType::CIRCLE;
		bool aPolygonCheck = a->shape->GetType() == ShapeType::POLYGON || a->shape->GetType() == ShapeType::BOX;
		bool bPolygonCheck = b->shape->GetType() == ShapeType::POLYGON || b->shape->GetType() == ShapeType::BOX;

		if (aCircleCheck && bCircleCheck) {
			return CollidingCIRC2CIRC(a, b, contact);
		}

		if (aPolygonCheck && bPolygonCheck) {
			return CollidingPOLY2POLY(a, b, contact);
		}

		if (aPolygonCheck && bCircleCheck) {
			return CollidingPOLY2CIRC(a, b, contact);
		}
		if (aCircleCheck && bPolygonCheck) {
			return CollidingPOLY2CIRC(b, a, contact);
		}

		return false;
	}

	bool CollisionBody::CollidingCIRC2CIRC(PhysicsBody* a, PhysicsBody* b, PhysicsContact& contact) {
		PhysicsShapeCircle* circA = (PhysicsShapeCircle*)a->shape;
		PhysicsShapeCircle* circB = (PhysicsShapeCircle*)b->shape;

		const Vector2D ab = b->bodyPosition - a->bodyPosition;
		const float totalRadius = circA->radius + circB->radius;

		bool collisionCheck = ab.magnitudeSquared() <= (totalRadius * totalRadius);

		if (!collisionCheck) {
			return false;
		}

		contact.a = a;
		contact.b = b;

		contact.normal = ab;
		contact.normal.Normie();

		contact.start = b->bodyPosition - contact.normal * circB->radius;
		contact.end = a->bodyPosition - contact.normal * circA->radius;

		contact.collisionDepth = (contact.end - contact.start).magnitude();

		return true;
	}

	bool CollisionBody::CollidingPOLY2POLY(PhysicsBody* a, PhysicsBody* b, PhysicsContact& contact) {
		const PhysicsShapePolygon* polyA = (PhysicsShapePolygon*)a->shape;
		const PhysicsShapePolygon* polyB = (PhysicsShapePolygon*)b->shape;

		Vector2D axisA, axisB, pointA, pointB;

		float abSeparation = polyA->SAT(polyB, axisA, pointA);
		if (abSeparation >= 0) {
			return false;
		}
		float baSeparation = polyB->SAT(polyA, axisB, pointB);
		if (baSeparation >= 0) {
			return false;
		}

		contact.a = a;
		contact.b = b;

		if (abSeparation > baSeparation) {
			contact.collisionDepth = -abSeparation;
			contact.normal = axisA.Normie();
			contact.start = pointA;
			contact.end = pointA + contact.normal * contact.collisionDepth;
		}
		else {
			contact.collisionDepth = -baSeparation;
			contact.normal = -axisB.Normie();
			contact.start = pointB - contact.normal * contact.collisionDepth;
			contact.end = pointB;
		}
		return true;
	}

	bool CollisionBody::CollidingPOLY2CIRC(PhysicsBody* pol, PhysicsBody* cir, PhysicsContact& contact) {
		const PhysicsShapePolygon* polyShape = (PhysicsShapePolygon*)pol->shape;
		const PhysicsShapeCircle* circleShape = (PhysicsShapeCircle*)cir->shape;
		const std::vector<Vector2D>& polygonVertices = polyShape->worldVertices;

		bool outsideCheck = false;
		Vector2D minCurrentVertex;
		Vector2D minNextVertex;
		float distanceCircleEdge = std::numeric_limits<float>::lowest();

		//Loop all edges of the polygon and find the nearest edge to the circle center
		for (int index{ 0 }; index < polygonVertices.size(); index++) {
			int currV{ index };
			int nextV = (static_cast<unsigned long long>(index) + 1) % polygonVertices.size();
			Vector2D edge = polyShape->Edging(currV);
			Vector2D normal = edge.Normal();

			//compare circle center with retangle vertex
			Vector2D vertex2CircleCenter = cir->bodyPosition - polygonVertices[currV];
			float projection = vertex2CircleCenter.Dot(normal);

			//If dot product project is that outside of normal is found
			if (projection > 0) {
				distanceCircleEdge = projection;
				minCurrentVertex = polygonVertices[currV];
				minNextVertex = polygonVertices[nextV];
				outsideCheck = true;
				break;
			}
			else {
				//Circle center inside the rectangle, find min edge
				if (projection > distanceCircleEdge) {
					distanceCircleEdge = projection;
					minCurrentVertex = polygonVertices[currV];
					minNextVertex = polygonVertices[nextV];
				}
			}
		}

		if (outsideCheck) {
			//region A check--
			//vector from the nearest vertex to the circle center
			Vector2D v1 = cir->bodyPosition - minCurrentVertex;
			//nearest edge from current vertex to next
			Vector2D v2 = minNextVertex - minCurrentVertex;
			if (v1.Dot(v2) < 0) {
				//if distance from vertex to center of circle is greater than radius (no collision)
				if (v1.magnitude() > circleShape->radius) {
					return false;
				}
				else {
					//collision detected in region A
					contact.a = pol;
					contact.b = cir;
					contact.collisionDepth = circleShape->radius - v1.magnitude();
					contact.normal - v1.Normie();
					contact.start = cir->bodyPosition + (contact.normal * -circleShape->radius);
					contact.end = contact.start + (contact.normal * contact.collisionDepth);
				}
			}
			else {
				//region B check--
				//vector from the next nearest vertex to circle center
				v1 = cir->bodyPosition - minNextVertex;
				//nearest edge
				v2 = minCurrentVertex - minNextVertex;
				if (v1.Dot(v2) < 0) {
					//if distance from vertex to circle center is greater than radius (no collision)
					if (v1.magnitude() > circleShape->radius) {
						return false;
					}
					else {
						//collision dectected in region B
						contact.a = pol;
						contact.b = cir;
						contact.collisionDepth = circleShape->radius - v1.magnitude();
						contact.normal = v1.Normie();
						contact.start = cir->bodyPosition + (contact.normal * -circleShape->radius);
						contact.end = contact.start + (contact.normal * contact.collisionDepth);
					}
				}
				else {
					if (distanceCircleEdge > circleShape->radius) {
						return false;
					}
					else {
						//region c
						contact.a = pol;
						contact.b = cir;
						contact.collisionDepth = circleShape->radius - distanceCircleEdge;
						contact.normal = (minNextVertex - minCurrentVertex).Normal();
						contact.start = cir->bodyPosition - (contact.normal * circleShape->radius);
						contact.end = contact.start + (contact.normal * contact.collisionDepth);
					}
				}
			}
		}
		else {
			//center of circle is inside the polygon
			contact.a = pol;
			contact.b = cir;
			contact.collisionDepth = circleShape->radius - distanceCircleEdge;
			contact.normal = (minNextVertex - minCurrentVertex).Normal();
			contact.start = cir->bodyPosition - (contact.normal * circleShape->radius);
			contact.end = contact.start + (contact.normal * contact.collisionDepth);
		}
		return true;
	}
}