#include "PhysicsShape.h"

namespace MFEngine {
	PhysicsShapeCircle::PhysicsShapeCircle(float rad) {
		radius = rad;
	}

	PhysicsShapeCircle::~PhysicsShapeCircle() {

	}

	PhysicsShape* PhysicsShapeCircle::Clone() const {
		return new PhysicsShapeCircle(radius);
	}

	ShapeType PhysicsShapeCircle::GetType() const {
		return ShapeType::CIRCLE;
	}

	float PhysicsShapeCircle::GetInertia() const {
		return 0.5f * (static_cast<float>(radius) * static_cast<float>(radius));
	}

	PhysicsShapePolygon::PhysicsShapePolygon(const std::vector<Vector2D> vertices) {
		for (auto vert : vertices) {
			localVertices.push_back(vert);
			worldVertices.push_back(vert);
		}
	}

	PhysicsShapePolygon::~PhysicsShapePolygon() {
	}

	ShapeType PhysicsShapePolygon::GetType() const {
		return ShapeType::POLYGON;
	}

	PhysicsShape* PhysicsShapePolygon::Clone() const {
		return new PhysicsShapePolygon(localVertices);
	}

	float PhysicsShapePolygon::GetInertia() const {
		return 5000;
	}

	Vector2D PhysicsShapePolygon::Edging(int k) const {
		int currentVertex = k;
		int nextVertex = (static_cast<unsigned long long>(k) + 1) % worldVertices.size();
		return worldVertices[nextVertex] - worldVertices[currentVertex];
	}

	float PhysicsShapePolygon::SAT(const PhysicsShapePolygon* other, Vector2D axis, Vector2D& point) const {
		float separation = std::numeric_limits<float>::lowest();
		//Loop through all the vertices of current polygon
		for (int p{ 0 }; p < worldVertices.size(); p++) {
			Vector2D va = worldVertices[p];
			Vector2D normal = Edging(p).normal();
			//Loop through all vertices of other polygon
			float minimumSeparation = std::numeric_limits<float>::max();
			Vector2D minimumVertex;
			for (int q{ 0 }; q < other->worldVertices.size(); q++) {
				Vector2D vb = other->worldVertices[q];
				float projection = (vb - va).dot(normal);
				if (projection < minimumSeparation) {
					minimumSeparation = projection;
					minimumVertex = vb;
				}
			}
			if (minimumSeparation > separation) {
				separation = minimumSeparation;
				axis = this->Edging(p);
				point = minimumVertex;
			}
		}
		return separation;
	}

	void PhysicsShapePolygon::updateVertices(float angle, const Vector2D& position) {
		//Loop through all vertices, transforming from local to world space
		for (int k{ 0 }; k < localVertices.size(); k++) {
			//Todo add rotation
			worldVertices[k] = localVertices[k].rotate(angle);
			worldVertices[k] += position;
		}
	}

	PhysicsShapeBox::PhysicsShapeBox(float w, float h) {
		width = w;
		height = h;

		//Load vertices of the box polygon
		localVertices.push_back(Vector2D(-width / 2.0f, -height / 2.0f));
		localVertices.push_back(Vector2D(+width / 2.0f, -height / 2.0f));
		localVertices.push_back(Vector2D(+width / 2.0f, +height / 2.0f));
		localVertices.push_back(Vector2D(-width / 2.0f, +height / 2.0f));

		worldVertices.push_back(Vector2D(-width / 2.0f, -height / 2.0f));
		worldVertices.push_back(Vector2D(+width / 2.0f, -height / 2.0f));
		worldVertices.push_back(Vector2D(+width / 2.0f, +height / 2.0f));
		worldVertices.push_back(Vector2D(-width / 2.0f, +height / 2.0f));
	}

	PhysicsShapeBox::~PhysicsShapeBox() {
		//TODO
	}

	ShapeType PhysicsShapeBox::GetType() const {
		return ShapeType::BOX;
	}

	PhysicsShape* PhysicsShapeBox::Clone() const {
		return new PhysicsShapeBox(width, height);
	}

	float PhysicsShapeBox::GetInertia() const {
		//For rectangle, the moment of inertia is (1/12 * mass) * (w^2 + h^2) according to wiki
		//This part does not account for the body's mass (to call further)
		return (0.83333f) * (width * width + height * height);
	}
}