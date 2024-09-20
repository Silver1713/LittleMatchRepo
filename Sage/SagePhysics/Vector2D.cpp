#include "Vector2D.h"
#include <cmath>
#include <stdexcept>


constexpr float PI = 3.14159265358f;

namespace MFEngine
{
    Vector2D::Vector2D(float X, float Y) : x(X), y(Y) {}

    Vector2D::Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}

    Vector2D Vector2D::operator+(const Vector2D& rhs) const {
        return Vector2D(x + rhs.x, y + rhs.y);
    }

    Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2D Vector2D::operator-(const Vector2D& rhs) const {
        return Vector2D(x - rhs.x, y - rhs.y);
    }

    Vector2D& Vector2D::operator-=(const Vector2D& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2D Vector2D::operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D& Vector2D::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D Vector2D::operator/(float scalar) const {
        if (scalar == 0.0f) {
            throw std::runtime_error("Division by zero in vector division.");
        }
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D& Vector2D::operator/=(float scalar) {
        if (scalar == 0.0f) {
            throw std::runtime_error("Division by zero in vector division.");
        }
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2D Vector2D::operator-() const {
        return Vector2D(-x, -y);
    }

    bool Vector2D::operator==(const Vector2D& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool Vector2D::operator!=(const Vector2D& rhs) const {
        return !(*this == rhs);
    }

    float Vector2D::magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    float Vector2D::magnitudeSquared() const {
        return x * x + y * y;
    }

    void Vector2D::normalize() {
        float mag = magnitude();
        if (mag > 0) {
            x /= mag;
            y /= mag;
        }
    }

    Vector2D Vector2D::normalized() const {
        float mag = magnitude();
        return mag > 0 ? *this / mag : *this;
    }

    float Vector2D::dot(const Vector2D& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    Vector2D Vector2D::normal() const {
        return Vector2D(-y, x);
    }

    Vector2D Vector2D::rotate(float angle) const {
        float rad = angle * (PI / 180.0f); // Converting degrees to radians
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);
        return Vector2D(x * cosA - y * sinA, x * sinA + y * cosA);
    }

    std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << '(' << v.x << ", " << v.y << ')';
        return os;
    }

    Vector2D Vector2D::zero() {
        return Vector2D(0.0f, 0.0f);
    }
}
