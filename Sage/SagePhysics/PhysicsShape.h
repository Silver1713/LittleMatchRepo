#pragma once 
#include "Vector2D.h"
#include <vector>

namespace MFEngine {
	enum class ShapeType {
		CIRCLE,
		POLYGON,
		BOX
	};

	class PhysicsShape {
	public:
		virtual ~PhysicsShape() = default;
		virtual ShapeType GetType() const = 0;
		virtual PhysicsShape* Clone() const = 0;
		virtual float GetInertia() const = 0;
	};

	class PhysicsShapeCircle : public PhysicsShape {
	public:
		float radius;

		PhysicsShapeCircle(const float radius);
		virtual ~PhysicsShapeCircle();
		ShapeType GetType() const override;
		PhysicsShape* Clone() const override;
		float GetInertia() const override;
	};

	class PhysicsShapePolygon : public PhysicsShape {
	public:
		std::vector<Vector2D> localVertices;
		std::vector<Vector2D> worldVertices;

		PhysicsShapePolygon() = default;
		PhysicsShapePolygon(const std::vector<Vector2D> vertices);
		virtual ~PhysicsShapePolygon();
		ShapeType GetType() const override;
		PhysicsShape* Clone() const override;
		Vector2D Edging(int k)const;
		float SAT(const PhysicsShapePolygon* other, Vector2D axis, Vector2D& point) const;
		float GetInertia() const override;
		void updateVertices(float angle, const Vector2D& position);
	};

	class PhysicsShapeBox : public PhysicsShapePolygon {
	public:
		float width;
		float height;

		PhysicsShapeBox(float width, float height);
		virtual ~PhysicsShapeBox();
		ShapeType GetType() const override;
		PhysicsShape* Clone() const override;
		float GetInertia() const override;
	};


}