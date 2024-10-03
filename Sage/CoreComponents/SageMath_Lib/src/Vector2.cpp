/* Start Header ************************************************************************/
/*!
\file		Vector2.cpp
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		07 September 2024
\brief		Vector2 class and class operation defintion

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "Vector2.h"
namespace ToastBox {

	/*!*****************************************************************************
	 \brief
	  Default constructor for Vector2
   *******************************************************************************/
	Vec2::Vec2() :x{ 0 }, y{ 0 } {}

	/*!*****************************************************************************
	  \brief
	   Parameterized constructor for Vector2

	  \param _x
	   X component of the vector

	  \param _y
	   Y component of the vector
	*******************************************************************************/
	Vec2::Vec2(const float x, const float y) : x{ x }, y{ y } {}

	/*!*****************************************************************************
	  \brief
	   Get the X component of the vector

	  \return
	   X component of the vector
	*******************************************************************************/
	float Vec2::GetX() const {
		return x;
	}

	/*!*****************************************************************************
	  \brief
	   Get the Y component of the vector

	  \return
	   Y component of the vector
	*******************************************************************************/
	float Vec2::GetY() const {
		return y;
	}

	/*!*****************************************************************************
	  \brief
	   Set the X component of the vector

	  \param _value
	   New value for the X component
	*******************************************************************************/
	void Vec2::SetX(float value) {
		x = value;
	}

	/*!*****************************************************************************
	  \brief
	   Set the Y component of the vector

	  \param _value
	   New value for the Y component
	*******************************************************************************/
	void Vec2::SetY(float value) {
		y = value;
	}

	/*!*****************************************************************************
	  \brief
	   Invert the vector
	*******************************************************************************/
	void Vec2::Invert() {
		x = -x;
		y = -y;
	}

	/*!*****************************************************************************
	  \brief
	   Calculate the magnitude of the vector

	  \return
	   Magnitude of the vector
	*******************************************************************************/
	float Vec2::Magnitude() const {
		return real_sqrt(x * x + y * y);
	}

	/*!*****************************************************************************
	  \brief
	   Calculate the squared magnitude of the vector

	  \return
	   Squared magnitude of the vector
	*******************************************************************************/
	float Vec2::Magnitude_Squared() const {
		return (x * x + y * y);
	}

	/*!*****************************************************************************
	  \brief
	   Normalize a given vector

	  \param _result
	   Vector to store the normalized result

	  \param _vec0
	   Vector to be normalized
	*******************************************************************************/
	void Vec2::Normalize(Vec2& pResult, const Vec2& pVec0) {
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

	/*!*****************************************************************************
	  \brief
	   Multiply the vector by a scalar

	  \param _value
	   Scalar value to multiply by
	*******************************************************************************/
	void Vec2::operator*=(const float value) {
		x *= value;
		y *= value;
	}

	/*!*****************************************************************************
	  \brief
	   Multiply the vector by a scalar and return the result

	  \param _value
	   Scalar value to multiply by

	  \return
	   Resulting vector after multiplication
	*******************************************************************************/
	Vec2 Vec2::operator*(const float value) const {
		return Vec2(x * value, y * value);
	}

	/*!*****************************************************************************
	  \brief
	   Add another vector to this vector

	  \param _vec0
	   Vector to add
	*******************************************************************************/
	void Vec2::operator+=(const Vec2& pVec0) {
		x += pVec0.x;
		y += pVec0.y;
	}

	/*!*****************************************************************************
	  \brief
	   Add two vectors and return the result

	  \param _vec0
	   Vector to add

	  \return
	   Resulting vector after addition
	*******************************************************************************/
	Vec2 Vec2::operator+(const Vec2& pVec0) const {
		return Vec2(x + pVec0.x, y + pVec0.y);
	}

	/*!*****************************************************************************
	  \brief
	   Add two vectors and return the result

	  \param _vec1
	   First vector to add

	  \param _vec2
	   Second vector to add

	  \return
	   Resulting vector after addition
	*******************************************************************************/
	Vec2 Vec2::Addition(const Vec2& vec1, const Vec2& vec2) {
		return Vec2(vec1.x + vec2.x, vec1.y + vec2.y);
	}

	/*!*****************************************************************************
	  \brief
	   Subtract another vector from this vector

	  \param _vec0
	   Vector to subtract
	*******************************************************************************/
	void Vec2::operator-=(const Vec2& pVec0) {
		x -= pVec0.x;
		y -= pVec0.y;
	}

	/*!*****************************************************************************
	  \brief
	   Subtract two vectors and return the result

	  \param _vec0
	   Vector to subtract

	  \return
	   Resulting vector after subtraction
	*******************************************************************************/
	Vec2 Vec2::operator-(const Vec2& pVec0) const {
		return Vec2(x - pVec0.x, y - pVec0.y);
	}

	/*!*****************************************************************************
	  \brief
	   Subtract two vectors and return the result

	  \param _vec1
	   Vector to subtract from

	  \param _vec2
	   Vector to subtract

	  \return
	   Resulting vector after subtraction
	*******************************************************************************/
	Vec2 Vec2::Subtraction(const Vec2& vec1, const Vec2& vec2) {
		return Vec2(vec1.x - vec2.x, vec1.y - vec2.y);
	}

	/*!*****************************************************************************
	  \brief
	   Divide this vector by another vector component-wise

	  \param _vec0
	   Vector to divide by
	*******************************************************************************/
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

	/*!*****************************************************************************
	  \brief
	   Divide this vector by a scalar and return the result

	  \param _value
	   Scalar value to divide by

	  \return
	   Resulting vector after division
	*******************************************************************************/
	Vec2 Vec2::operator/(const float value) const {
		if (value == 0) {
			return Vec2(0, 0);
		}
		else {
			return Vec2(x / value, y / value);
		}
	}

	/*!*****************************************************************************
	  \brief
	   Add a scaled version of another vector to this vector

	  \param _vec0
	   Vector to scale and add

	  \param _k
	   Scalar value to multiply _vec0 by before adding
	*******************************************************************************/
	void Vec2::Scaled_Vector_Adding(const Vec2& pVec0, float k) {
		x += pVec0.x * k;
		y += pVec0.y * k;
	}

	/*!*****************************************************************************
	  \brief
	   Compute the component-wise product of two vectors

	  \param _vec0
	   Vector to multiply with

	  \return
	   Resulting vector after component-wise multiplication
	*******************************************************************************/
	Vec2 Vec2::Product_Component(const Vec2& pVec0) const {
		return Vec2(x * pVec0.x, y * pVec0.y);
	}

	/*!*****************************************************************************
	  \brief
	   Update this vector with the component-wise product of another vector

	  \param _vec0
	   Vector to multiply with
	*******************************************************************************/
	void Vec2::Product_Component_Update(const Vec2& pVec0) {
		x *= pVec0.x;
		y *= pVec0.y;
	}

	/*!*****************************************************************************
	  \brief
	   Compute the dot product with another vector

	  \param _vec0
	   Vector to compute dot product with

	  \return
	   Resulting scalar after dot product
	*******************************************************************************/
	float Vec2::Product_Scalar(const Vec2& pVec0) const {
		return x * pVec0.x + y * pVec0.y;
	}


	/*!*****************************************************************************
	  \brief
	   Compute the dot product with another vector (operator overload)

	  \param _vec0
	   Vector to compute dot product with

	  \return
	   Resulting scalar after dot product
	*******************************************************************************/
	float Vec2::operator*(const Vec2& pVec0) const {
		return x * pVec0.x + y * pVec0.y;
	}

	/*!*****************************************************************************
	  \brief
	   Compute the magnitude of the cross product with another vector

	  \param _vec0
	   Vector to compute cross product with

	  \return
	   Magnitude of the resulting cross product
	*******************************************************************************/
	float Vec2::Cross_Product_Magnitude(const Vec2& pVec0) const {
		Vec2 dp;
		dp.x = x * pVec0.y;
		dp.y = y * pVec0.x;
		return dp.x - dp.y;
	}

	/*!*****************************************************************************
	  \brief
	   Rotate the vector by a given angle

	  \param _angle
	   Angle to rotate by (in radians)
	*******************************************************************************/
	void Vec2::Rotate(float angle) {
		float cosAngle = std::cos(angle);
		float sinAngle = std::sin(angle);
		float px = x * cosAngle - y * sinAngle;  // Calculate new x component
		float py = x * sinAngle + y * cosAngle;  // Calculate new y component

		x = px;  // Update x to new rotated x
		y = py;  // Update y to new rotated y
	}

	/*!*****************************************************************************
	  \brief
	   Reset the vector to zero
	*******************************************************************************/
	void Vec2::Clear() {
		x = 0;
		y = 0;
	}

}