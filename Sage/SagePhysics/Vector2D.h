#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept> // For std::runtime_error

namespace MFEngine
{
    struct Vector2D
    {
        // Constructors
        Vector2D(float X = 0.0f, float Y = 0.0f);
        Vector2D(const Vector2D& v);

        // Arithmetic operators
        Vector2D operator+(const Vector2D& rhs) const;
        Vector2D& operator+=(const Vector2D& rhs);
        Vector2D operator-(const Vector2D& rhs) const;
        Vector2D& operator-=(const Vector2D& rhs);
        Vector2D operator*(float scalar) const;
        Vector2D& operator*=(float scalar);
        Vector2D operator/(float scalar) const;
        Vector2D& operator/=(float scalar);

        // Unary operations
        Vector2D operator-() const;
        Vector2D operator+() const { return *this; }

        // Comparison operators
        bool operator==(const Vector2D& rhs) const;
        bool operator!=(const Vector2D& rhs) const;

        // Utility methods
        float magnitude() const;
        float magnitudeSquared() const;
        void normalize();
        Vector2D normalized() const;
        float dot(const Vector2D& rhs) const;
        float cross(const Vector2D& rhs) const;
        Vector2D normal() const;
        Vector2D rotate(const float angle) const;
        static Vector2D zero();

        // Stream insertion
        friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);

        float x, y;
    };
}
