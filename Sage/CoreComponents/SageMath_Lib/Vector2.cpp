/******************************************************************************
File name	 : Vector2.cpp
Project		 : Memory's Flame
Author       : Edwin Lee Zirui
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 09/09/2024
Brief		 : Vector2 class and class operation defintion
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/

#include "Vector2.h"
namespace ToastBox {

	Vec2::Vec2() :x{ 0 }, y{ 0 } {}
	Vec2::Vec2(const float x, const float y) : x{ x }, y{ y } {}

	/*
	Function: getX()
	Desc: Access x value of vector*/
	float Vec2::getX() const {
		return x;
	}

	/*
	Function: getY()
	Desc: Access y value of vector*/
	float Vec2::getY() const {
		return y;
	}

	/*
	Function: setX()
	Desc: Mutate x value of vector*/
	void Vec2::setX(float value) {
		x = value;
	}

	/*
	Function: setY()
	Desc: Mutate y value of vector*/
	void Vec2::setY(float value) {
		y = value;
	}


	/*
	Function: invert
	Desc: Invert the vector
	Example:  -a = -1 * a = <-x,-y>*/
	void Vec2::invert() {
		x = -x;
		y = -y;
	}

	/*
	Function: magnitude
	Desc: Returned magnitude of the vector*/
	float Vec2::magnitude() const {
		return real_sqrt(x * x + y * y);
	}

	/*
	Function: magnitudeSquared
	Desc: Returned squared magnitude of the vector*/
	float Vec2::magnitudeSquared() const {
		return (x * x + y * y);
	}

	/*
	Function: normalize
	Param: pReseult -> For returning of normalized vector
	Param: pVec0	-> The vector to normalized
	Desc: Normalized vector*/
	void Vec2::normalize(Vec2& pResult, const Vec2& pVec0) {
		Vec2 result;
		result.x = pVec0.x * pVec0.x;
		result.y = pVec0.y * pVec0.y;
		float addition{ result.x + result.y };
		float magnitude{ static_cast<float>(sqrt(addition)) };
		if (magnitude == 0) {
			pResult.x = 0;
			pResult.y = 0;
		}
		else {
			pResult.x = pVec0.x / magnitude;  // Normalize x
			pResult.y = pVec0.y / magnitude;  // Normalize y
		}
	}

	/*
	Function: operator*=
	Param: value
	Desc: Multiplies vector by param <value>*/
	void Vec2::operator*=(const float value) {
		x *= value;
		y *= value;
	}

	/*
	Function: operator*
	Param: value
	Desc: Return a copy of the vector scaled to param <value>
	Notes: Functions is overloaded:
		* if param is float: does component multiplication with scale
		* if param is Vec2: does dot product*/
	Vec2 Vec2::operator*(const float value) const {
		return Vec2(x * value, y * value);
	}

	/*
	Function: operator+=
	Param: pVec0
	Desc: Append *this vector with param<pVec0> vector (add values)
	Example: a + b = <a.x, a.y> + <b.x, b.y > = <a.x + b.x, a.y + b.y>*/
	void Vec2::operator+=(const Vec2& pVec0) {
		x += pVec0.x;
		y += pVec0.y;
	}

	/*
	Function: operator+
	Param: pVec2
	Desc: Return a new vector by adding current vector with param<pVec0> vector
	Example: c = a + b = <a.x, a.y> + <b.x, b.y > = <a.x + b.x, a.y + b.y*/
	Vec2 Vec2::operator+(const Vec2& pVec0) const {
		return Vec2(x + pVec0.x, y + pVec0.y);
	}

	/*
	Function: addition
	Param: vec1, vec2
	Desc: Add 2 vec2 object together and return the result*/
	Vec2 Vec2::addition(const Vec2& vec1, const Vec2& vec2) {
		return Vec2(vec1.x + vec2.x, vec1.y + vec2.y);
	}

	/*
	Function: operator-=
	Param: pVec0
	Desc: Append *this vector with param<pVec0> vector (subtract values)
	Example: a - b = <a.x, a.y> - <b.x, b.y > = <a.x - b.x, a.y - b.y*/
	void Vec2::operator-=(const Vec2& pVec0) {
		x -= pVec0.x;
		y -= pVec0.y;
	}

	/*
	Function: operator-
	Param: pVec0
	Desc: Return a new vector by subracting current vector with param<pVec0> vector
	Example: c = a - b = <a.x, a.y> - <b.x, b.y > = <a.x - b.x, a.y - b.y*/
	Vec2 Vec2::operator-(const Vec2& pVec0) const {
		return Vec2(x - pVec0.x, y - pVec0.y);
	}

	/*
	Function: subtraction
	Param: vec1, vec2
	Desc: Substract 2 vec2 object and return result. Vec1 - Vec2*/
	Vec2 Vec2::subtraction(const Vec2& vec1, const Vec2& vec2) {
		return Vec2(vec1.x - vec2.x, vec1.y - vec2.y);
	}

	/*
	Function: operator/=
	Param: pVec0
	Desc: Divide component of this vector by with another vector with param<pVec0> vector
	Example: a / b = <a.x, a.y> / <b.x, b.y > = <a.x / b.x, a.y / b.y*/
	void Vec2::operator/=(const Vec2& pVec0) {
		if (pVec0.x == 0) {
			x = 0;
		}
		else {
			x /= pVec0.x;
		}

		if (pVec0.y == 0) {
			y = 0;
		}
		else {
			y /= pVec0.y;
		}
	}


	/*
	Function: operator/
	Param: value
	Desc: Return a new vector by subracting current vector with param<pVec0> vector
	Example: c = a / b = <a.x, a.y> / <b.x, b.y > = <a.x / b.x, a.y / b.y*/
	Vec2 Vec2::operator/(const float value) const {
		if (value == 0) {
			return Vec2(0, 0);
		}
		else {
			return Vec2(x / value, y / value);
		}
	}

	/*
	Function: scaledVectorAdding
	Param: value
	Desc: Scales another vector by k and adds the result to this vector.
	Example: a + kb = <a.x, a.y> + k<b.x, b.y > = <a.x + kb.x, a.y + kb.y
	Notes: This function can be used update position of point as in
	position = (velocity * time) + acceleration * time^2 * 0.5
	can be calulated with
	object.position = scaledVectorAdding(object.velocity,time) and
	object.position = scaledVectorAdding(object.acceleration,time*time*0.5)
	*/
	void Vec2::scaledVectorAdding(const Vec2& pVec0, float k) {
		x += pVec0.x * k;
		y += pVec0.y * k;
	}

	/*
	Function: productComponent
	Param: pVec0
	Desc: Multiples individual component of a vector by param<pVec0> corresponding component value
	Example: c = a productComponent b = <a.x, a.y> productComponent <b.x, b.y> = <a.x * b.x, a.y * b.y> */
	Vec2 Vec2::productComponent(const Vec2& pVec0) const {
		return Vec2(x * pVec0.x, y * pVec0.y);
	}
	/*
	Function: productComponentUpdate
	Param: pVec0
	Desc: Multiples individual component of self vector by another vector <pVec0> with new corresponding component value
	Example: a dot b = <a.x, a.y> dot <b.x, b.y> = <a.x * b.x, a.y * b.y> */
	void Vec2::productComponentUpdate(const Vec2& pVec0) {
		x *= pVec0.x;
		y *= pVec0.y;
	}

	/*
	Function: productScalar
	Param: pVec0
	Desc: Dot-Product Operation
	Return scalar product of current vector with another vector <pVec2>.
	Example: a * b = <a.x, a.y> * <b.x, b.y> = a.x * b.x + a.y * b.y */
	float Vec2::productScalar(const Vec2& pVec0) const {
		return x * pVec0.x + y * pVec0.y;
	}


	/*
	Function: operator*
	Param: pVec0
	Desc: Dot-Product Operation
	Return scalar product of current vector with another vector <pVec2>.
	Example: a * b = <a.x, a.y> * <b.x, b.y> = a.x * b.x + a.y * b.y  */
	float Vec2::operator*(const Vec2& pVec0) const {
		return x * pVec0.x + y * pVec0.y;
	}

	/*
	Function: cross product (magnitude)
	Param: pVec0
	Desc: Return cross product magnitude between 2 points. */
	float Vec2::productCrossMag(const Vec2& pVec0) const {
		Vec2 dp;
		dp.x = x * pVec0.y;
		dp.y = y * pVec0.x;
		return dp.x - dp.y;
	}

	/*
	Function: rotate
	Param: angle in radians
	Desc: Rotates the vector by a given angle around the origin (0, 0). */
	Vec2 Vec2::rotate(const float angle) const {
		float cosAngle = std::cos(angle);
		float sinAngle = std::sin(angle);
		return Vec2(
			this->x * cosAngle - this->y * sinAngle,  // New x coordinate
			this->x * sinAngle + this->y * cosAngle   // New y coordinate
		);
	}

	/*
	Function: clear
	Desc: Reset the points*/
	void Vec2::clear() {
		x = 0;
		y = 0;
	}

}