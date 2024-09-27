/******************************************************************************
File name	 : Vector2.h
Project		 : Memory's Flame
Author       : Edwin Lee Zirui
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 09/09/2024
Brief		 : Vector2 class and class operation declaration
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/

#pragma once

#include <cmath>

#define real_sqrt sqrtf
#define real_pow powf

namespace ToastBox {


	class Vec2 {
	public:
		float x{}, y{};
		//Construction
		Vec2();
		Vec2(const float x, const float y);

		//Accessor
		float getX() const;
		float getY() const;

		//Setter
		void setX(float value);
		void setY(float value);

		//Invert/negate the values
		void invert();

		//Size
		float magnitude() const;
		float magnitudeSquared() const;
		void normalize(Vec2& pResult, const Vec2& pVec0);

		//Scalar/Vector multiplication
		void operator*=(const float value);
		Vec2 operator*(const float value) const;

		//Vector addition
		void operator+=(const Vec2& pVec0);
		Vec2 operator+(const Vec2& pVec0) const;
		Vec2 addition(const Vec2& vec1, const Vec2& vec2);

		//Vector subtraction
		void operator-=(const Vec2& pVec0);
		Vec2 operator-(const Vec2& pVec0) const;
		Vec2 subtraction(const Vec2& vec1, const Vec2& vec2);

		//Vector division
		void operator/=(const Vec2& pVec0);
		Vec2 operator/(const float value) const;

		//Scaled version of another vector. Can be used to detemine position += velocity * time
		void scaledVectorAdding(const Vec2& pVec0, float scale);

		//Product
		//Component
		Vec2 productComponent(const Vec2& pVec0) const;
		void productComponentUpdate(const Vec2& pVec0);

		//Dot
		float productScalar(const Vec2& pVec0) const;
		float operator*(const Vec2& pVec0) const;

		//Cross product magnitude
		float productCrossMag(const Vec2& pVec0) const;

		//Rotate
		void rotate(float angle);

		void clear();


	};
}
