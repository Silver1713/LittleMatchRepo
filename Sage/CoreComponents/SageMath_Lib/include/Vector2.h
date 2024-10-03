/* Start Header ************************************************************************/
/*!
\file		Vector2.h
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		07 September 2024
\brief		Vector2 class and class operation declaration

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#pragma once

#include <cmath>

#define real_sqrt sqrtf
#define real_pow powf

namespace ToastBox {


	class Vec2 {
	public:
		float x{}, y{};
		/*!*****************************************************************************
		  \brief
		   Default constructor for Vector2
		*******************************************************************************/
		Vec2();

		/*!*****************************************************************************
		  \brief
		   Parameterized constructor for Vector2

		  \param _x
		   X component of the vector

		  \param _y
		   Y component of the vector
		*******************************************************************************/
		Vec2(const float x, const float y);

		/*!*****************************************************************************
		  \brief
		   Get the X component of the vector

		  \return
		   X component of the vector
		*******************************************************************************/
		float GetX() const;

		/*!*****************************************************************************
		  \brief
		   Get the Y component of the vector

		  \return
		   Y component of the vector
		*******************************************************************************/
		float GetY() const;

		/*!*****************************************************************************
		  \brief
		   Set the X component of the vector

		  \param _value
		   New value for the X component
		*******************************************************************************/
		void SetX(float value);

		/*!*****************************************************************************
		  \brief
		   Set the Y component of the vector

		  \param _value
		   New value for the Y component
		*******************************************************************************/
		void SetY(float value);

		/*!*****************************************************************************
		  \brief
		   Invert the vector
		*******************************************************************************/
		void Invert();

		/*!*****************************************************************************
		  \brief
		   Calculate the magnitude of the vector

		  \return
		   Magnitude of the vector
		*******************************************************************************/
		float Magnitude() const;

		/*!*****************************************************************************
		  \brief
		   Calculate the squared magnitude of the vector

		  \return
		   Squared magnitude of the vector
		*******************************************************************************/
		float Magnitude_Squared() const;

		/*!*****************************************************************************
		  \brief
		   Normalize a given vector

		  \param _result
		   Vector to store the normalized result

		  \param _vec0
		   Vector to be normalized
		*******************************************************************************/
		void Normalize(Vec2& pResult, const Vec2& pVec0);

		/*!*****************************************************************************
		  \brief
		   Multiply the vector by a scalar

		  \param _value
		   Scalar value to multiply by
		*******************************************************************************/
		void operator*=(const float value);

		/*!*****************************************************************************
		  \brief
		   Multiply the vector by a scalar and return the result

		  \param _value
		   Scalar value to multiply by

		  \return
		   Resulting vector after multiplication
		*******************************************************************************/
		Vec2 operator*(const float value) const;

		/*!*****************************************************************************
		  \brief
		   Add another vector to this vector

		  \param _vec0
		   Vector to add
		*******************************************************************************/
		void operator+=(const Vec2& pVec0);

		/*!*****************************************************************************
		  \brief
		   Add two vectors and return the result

		  \param _vec0
		   Vector to add

		  \return
		   Resulting vector after addition
		*******************************************************************************/
		Vec2 operator+(const Vec2& pVec0) const;

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
		Vec2 Addition(const Vec2& vec1, const Vec2& vec2);

		/*!*****************************************************************************
		  \brief
		   Subtract another vector from this vector

		  \param _vec0
		   Vector to subtract
		*******************************************************************************/
		void operator-=(const Vec2& pVec0);

		/*!*****************************************************************************
		  \brief
		   Subtract two vectors and return the result

		  \param _vec0
		   Vector to subtract

		  \return
		   Resulting vector after subtraction
		*******************************************************************************/
		Vec2 operator-(const Vec2& pVec0) const;

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
		Vec2 Subtraction(const Vec2& vec1, const Vec2& vec2);

		/*!*****************************************************************************
		  \brief
		   Divide this vector by another vector component-wise

		  \param _vec0
		   Vector to divide by
		*******************************************************************************/
		void operator/=(const Vec2& pVec0);

		/*!*****************************************************************************
		  \brief
		   Divide this vector by a scalar and return the result

		  \param _value
		   Scalar value to divide by

		  \return
		   Resulting vector after division
		*******************************************************************************/
		Vec2 operator/(const float value) const;

		/*!*****************************************************************************
		  \brief
		   Add a scaled version of another vector to this vector

		  \param _vec0
		   Vector to scale and add

		  \param _scale
		   Scalar value to multiply _vec0 by before adding
		*******************************************************************************/
		void Scaled_Vector_Adding(const Vec2& pVec0, float scale);

		/*!*****************************************************************************
		  \brief
		   Compute the component-wise product of two vectors

		  \param _vec0
		   Vector to multiply with

		  \return
		   Resulting vector after component-wise multiplication
		*******************************************************************************/
		Vec2 Product_Component(const Vec2& pVec0) const;

		/*!*****************************************************************************
		  \brief
		   Update this vector with the component-wise product of another vector

		  \param _vec0
		   Vector to multiply with
		*******************************************************************************/
		void Product_Component_Update(const Vec2& pVec0);

		/*!*****************************************************************************
		  \brief
		   Compute the dot product with another vector

		  \param _vec0
		   Vector to compute dot product with

		  \return
		   Resulting scalar after dot product
		*******************************************************************************/
		float Product_Scalar(const Vec2& pVec0) const;

		/*!*****************************************************************************
		  \brief
		   Compute the dot product with another vector (operator overload)

		  \param _vec0
		   Vector to compute dot product with

		  \return
		   Resulting scalar after dot product
		*******************************************************************************/
		float operator*(const Vec2& pVec0) const;

		/*!*****************************************************************************
		  \brief
		   Compute the magnitude of the cross product with another vector

		  \param _vec0
		   Vector to compute cross product with

		  \return
		   Magnitude of the resulting cross product
		*******************************************************************************/
		float Cross_Product_Magnitude(const Vec2& pVec0) const;

		/*!*****************************************************************************
		  \brief
		   Rotate the vector by a given angle

		  \param _angle
		   Angle to rotate by (in radians)
		*******************************************************************************/
		void Rotate(float angle);

		/*!*****************************************************************************
		  \brief
		   Reset the vector to zero
		*******************************************************************************/
		void Clear();


	};
}
