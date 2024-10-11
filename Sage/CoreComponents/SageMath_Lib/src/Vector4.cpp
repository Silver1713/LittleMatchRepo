/* Start Header ************************************************************************/
/*!
\file		Vector4.cpp
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		13 September 2024
\brief		Vector4 class and class operation defination

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "Vector4.h"

#include <cmath>

namespace ToastBox
{
	/*!*****************************************************************************
	  \brief
	   Copy constructor for Vec4

	  \param pVec0
	   Vector to be copied

	  \return
	   New Vec4 object as a copy of pVec0
	*******************************************************************************/
	Vec4::Vec4(const Vec4& pVec0)
	{
		x = pVec0.x;
		y = pVec0.y;
		z = pVec0.z;
		w = pVec0.w;
	}

	/*!*****************************************************************************
	  \brief
	   Constructor with individual component values

	  \param x
	   X component of the vector
	  \param y
	   Y component of the vector
	  \param z
	   Z component of the vector
	  \param w
	   W component of the vector

	  \return
	   Initialized Vec4 object with specified components
	*******************************************************************************/
	Vec4::Vec4(float const& x, float const& y, float const& z, float const& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	/*!*****************************************************************************
	  \brief
	   Scalar multiplication assignment operator

	  \param value
	   Scalar to multiply with

	  \return
	   Reference to this vector after multiplication
	*******************************************************************************/
	Vec4& Vec4::operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	/*!*****************************************************************************
	  \brief
	   Vector addition assignment operator

	  \param pVec0
	   Vector to add

	  \return
	   Reference to this vector after addition
	*******************************************************************************/
	Vec4& Vec4::operator+=(const Vec4& pVec0)
	{
		x += pVec0.x;
		y += pVec0.y;
		z += pVec0.z;
		w += pVec0.w;
		return *this;
	}

	/*!*****************************************************************************
	  \brief
	   Cross product assignment operator

	  \param pVec0
	   Vector to cross with

	  \return
	   Reference to this vector after cross product
	*******************************************************************************/
	Vec4& Vec4::operator%=(const Vec4& pVec0)
	{
		// Cross product
		Vec4 result{};
		result.x = y * pVec0.z - z * pVec0.y;
		result.y = z * pVec0.x - x * pVec0.z;
		result.z = x * pVec0.y - y * pVec0.x;

		x = result.x;
		y = result.y;
		z = result.z;

		return *this;
	}

	/*!*****************************************************************************
	  \brief
	   Negation operator

	  \return
	   Negated vector
	*******************************************************************************/
	Vec4& Vec4::operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	}

	/*!*****************************************************************************
	  \brief
	   Vector subtraction assignment operator

	  \param pVec0
	   Vector to subtract

	  \return
	   Reference to this vector after subtraction
	*******************************************************************************/
	Vec4& Vec4::operator-=(const Vec4& pVec0)
	{
		x -= pVec0.x;
		y -= pVec0.y;
		z -= pVec0.z;
		w -= pVec0.w;
		return *this;
	}

	/*!*****************************************************************************
	  \brief
	   Vector division assignment operator

	  \param pVec0
	   Vector to divide by

	  \return
	   Reference to this vector after division
	*******************************************************************************/
	Vec4& Vec4::operator/=(const Vec4& pVec0)
	{
		x /= pVec0.x;
		y /= pVec0.y;
		z /= pVec0.z;
		w /= pVec0.w;
		return *this;
	}

	/*!*****************************************************************************
	  \brief
	   Scalar division assignment operator

	  \param value
	   Scalar to divide by

	  \return
	   Reference to this vector after division
	*******************************************************************************/
	Vec4& Vec4::operator/=(const float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	/*!*****************************************************************************
	  \brief
	   Assignment operator

	  \param pVec0
	   Vector to assign from

	  \return
	   Reference to this vector after assignment
	*******************************************************************************/
	Vec4& Vec4::operator=(const Vec4& pVec0)
	{
		x = pVec0.x;
		y = pVec0.y;
		z = pVec0.z;
		w = pVec0.w;
		return *this;
	}

	/*!*****************************************************************************
	  \brief
	   Indexed access operator (mutable)

	  \param index
	   Index of the component to access

	  \return
	   Reference to the component at the specified index
	*******************************************************************************/
	float& Vec4::operator[](int index)
	{
		return (&x)[index];
	}

	/*!*****************************************************************************
	  \brief
	   Indexed access operator (const)

	  \param index
	   Index of the component to access

	  \return
	   Value of the component at the specified index
	*******************************************************************************/
	float Vec4::operator[](int index) const
	{
		return (&x)[index];
	}

	/*!*****************************************************************************
	  \brief
	   Calculate the magnitude of the vector

	  \return
	   Magnitude of the vector
	*******************************************************************************/
	float Vec4::Magnitude() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	/*!*****************************************************************************
	  \brief
	   Calculate the squared magnitude of the vector

	  \return
	   Squared magnitude of the vector
	*******************************************************************************/
	float Vec4::Magnitude_Squared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	/*!*****************************************************************************
	  \brief
	   Normalize a vector

	  \param pResult
	   Vector to store the normalized result
	  \param pVec0
	   Vector to be normalized
	*******************************************************************************/
	void Vec4::Normalize(Vec4& pResult, const Vec4& pVec0)
	{
		const Vec4 result{ pVec0 };

		pResult = result / result.Magnitude();
	}

	/*!*****************************************************************************
	  \brief
	   Scalar multiplication operator

	  \param value
	   Scalar value to multiply with the vector
	  \param pVec0
	   Vector to be multiplied

	  \return
	   New Vec4 object representing the result of the multiplication
	*******************************************************************************/
	Vec4 operator*(const float value, const Vector4& pVec0)
	{
		Vec4 res{ pVec0 };
		res *= value;

		return res;
	}

	/*!*****************************************************************************
	  \brief
	   Scalar multiplication operator

	  \param pVec0
	   Vector to be multiplied
	  \param value
	   Scalar value to multiply with the vector

	  \return
	   New Vec4 object representing the result of the multiplication
	*******************************************************************************/
	Vec4 operator*(const Vector4& pVec0, const float value)
	{
		Vec4 res{ pVec0 };
		res *= value;

		return res;
	}

	/*!*****************************************************************************
	  \brief
	   Scalar division operator

	  \param pVec0
	   Vector to be divided
	  \param value
	   Scalar value to divide the vector by

	  \return
	   New Vec4 object representing the result of the division
	*******************************************************************************/
	Vec4 operator/(const Vector4& pVec0, const float value)
	{
		Vec4 res{ pVec0 };
		res /= value;

		return res;
	}

	/*!*****************************************************************************
	  \brief
	   Component-wise vector division operator

	  \param pVec0
	   Vector to be divided
	  \param pVec1
	   Vector to divide by

	  \return
	   New Vec4 object representing the result of the component-wise division
	*******************************************************************************/
	Vec4 operator/(const Vector4& pVec0, const Vector4& pVec1)
	{
		Vec4 res{ pVec0 };
		res /= pVec1;

		return res;
	}

	/*!*****************************************************************************
	  \brief
	   Cross product operator

	  \param pVec0
	   First vector in the cross product
	  \param pVec1
	   Second vector in the cross product

	  \return
	   New Vec4 object representing the result of the cross product
	*******************************************************************************/
	Vector4 operator%(const Vector4& pVec0, const Vector4& pVec1)
	{
		Vec4 res{ pVec0 };

		res %= pVec1;
		return res;
	}

	/*!*****************************************************************************
	  \brief
	   Vector addition operator

	  \param pVec0
	   First vector to be added
	  \param pVec1
	   Second vector to be added

	  \return
	   New Vec4 object representing the sum of the two vectors
	*******************************************************************************/
	Vector4 operator+(const Vector4& pVec0, const Vector4& pVec1)
	{
		Vector4 res{ pVec0 };
		res += pVec1;
		return res;
	}

	/*!*****************************************************************************
	  \brief
	   Vector subtraction operator

	  \param pVec0
	   Vector to subtract from
	  \param pVec1
	   Vector to be subtracted

	  \return
	   New Vec4 object representing the result of the subtraction
	*******************************************************************************/
	Vector4 operator-(const Vector4& pVec0, const Vector4& pVec1)
	{
		Vec4 newVec{ pVec0 };

		newVec -= pVec1;

		return newVec;

	}

	/*!*****************************************************************************
	  \brief
	   Dot product operator

	  \param pVec0
	   First vector in the dot product
	  \param pVec1
	   Second vector in the dot product

	  \return
	   Float value representing the dot product of the two vectors
	*******************************************************************************/
	float operator*(const Vector4& pVec0, const Vector4& pVec1)
	{
		return pVec0.x * pVec1.x + pVec0.y * pVec1.y + pVec0.z * pVec1.z + pVec0.w * pVec1.w;
	}

	/*!*****************************************************************************
	  \brief
	   Scalar division operator (scalar divided by vector)

	  \param value
	   Scalar value to be divided
	  \param pVec0
	   Vector to divide by

	  \return
	   New Vec4 object representing the result of the division
	*******************************************************************************/
	Vector4 operator/(const float value, const Vector4& pVec0)
	{
		Vec4 res{ pVec0 };
		res /= value;

		return res;
	}

	/*!*****************************************************************************
	  \brief
	   Get a pointer to the vector's data

	  \return
	   Pointer to the first component of the vector
	*******************************************************************************/
	float* Vec4::Data()
	{
		return &x;
	}


}









