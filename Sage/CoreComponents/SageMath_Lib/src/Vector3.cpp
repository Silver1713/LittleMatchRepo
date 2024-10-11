/* Start Header ************************************************************************/
/*!
\file		Vector3.cpp
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		07 September 2024
\brief		Vector3 class and class operation defination

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/


#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3x3.h"

namespace ToastBox {
	/*!*****************************************************************************
	  \brief
	   Default constructor for Vector3
	*******************************************************************************/
	Vec3::Vec3() :x{ 0 }, y{ 0 }, z{ 0 } {}

	/*!*****************************************************************************
	  \brief
	   Parameterized constructor for Vector3

	  \param _x
	   X component of the vector

	  \param _y
	   Y component of the vector

	  \param _z
	   Z component of the vector
	*******************************************************************************/
	Vec3::Vec3(const float x, const float y, const float z) : x{ x }, y{ y }, z{ z } {}

	/*!*****************************************************************************
	  \brief
	   Invert the vector
	*******************************************************************************/
	void Vec3::Invert() {
		x = -x;
		y = -y;
		z = -z;
	}

	/*!*****************************************************************************
	  \brief
	   Calculate the magnitude of the vector

	  \return
	   Magnitude of the vector
	*******************************************************************************/
	float Vec3::Magnitude() const {
		return real_sqrt(x * x + y * y + z * z);
	}

	/*!*****************************************************************************
	  \brief
	   Calculate the squared magnitude of the vector

	  \return
	   Squared magnitude of the vector
	*******************************************************************************/
	float Vec3::Magnitude_Squared() const {
		return x * x + y * y + z * z;
	}

	/*!*****************************************************************************
	  \brief
	   Normalize a given vector

	  \param _result
	   Vector to store the normalized result

	  \param _vec0
	   Vector to be normalized
	*******************************************************************************/
	void Vec3::Normalize(Vec3& pResult, const Vec3& pVec0) {
		Vec3 result;
		result.x = pVec0.x * pVec0.x;
		result.y = pVec0.y * pVec0.y;
		result.z = pVec0.z * pVec0.z;

		float addition{ result.x + result.y + result.z };
		float magnitude{ static_cast<float>(sqrt(addition)) };
		pResult.x = pVec0.x / magnitude;
		pResult.y = pVec0.y / magnitude;
		pResult.z = pVec0.z / magnitude;

	}

	/*!*****************************************************************************
	  \brief
	   Multiply the vector by a scalar

	  \param _value
	   Scalar value to multiply by
	*******************************************************************************/
	void Vec3::operator*= (const float value) {
		x *= value;
		y *= value;
		z *= value;
	}

	/*!*****************************************************************************
	 \brief
	  Multiply the vector by a scalar and return the result

	 \param _value
	  Scalar value to multiply by

	 \return
	  Resulting vector after multiplication
   *******************************************************************************/
	Vec3 Vec3::operator*(const float value) const {
		return Vec3(x * value, y * value, z * value);
	}

	/*!*****************************************************************************
	 \brief
	  Divide this vector by another vector component-wise

	 \param _vec0
	  Vector to divide by
   *******************************************************************************/
	void Vec3::operator/=(const Vec3& pVec0) {
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

		if (pVec0.z == 0) {
			z = 0;
		}
		else {
			z /= pVec0.z;
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
	Vec3 Vec3::operator/(const float value) const {
		if (value == 0) {
			return Vec3(0, 0, 0);
		}
		else {
			return Vec3(x / value, y / value, z / value);
		}
	}

	/*!*****************************************************************************
	  \brief
	   Add another vector to this vector

	  \param _vec0
	   Vector to add
	*******************************************************************************/
	void Vec3::operator+=(const Vec3& pVec0) {
		x += pVec0.x;
		y += pVec0.y;
		z += pVec0.z;
	}

	/*!*****************************************************************************
	  \brief
	   Add two vectors and return the result

	  \param _vec0
	   Vector to add

	  \return
	   Resulting vector after addition
	*******************************************************************************/
	Vec3 Vec3::operator+(const Vec3& pVec0) const {
		return Vec3(x + pVec0.x, y + pVec0.y, z + pVec0.z);
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
	Vec3 Vec3::Addition(const Vec3& vec1, const Vec3& vec2) {
		return Vec3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
	}

	/*!*****************************************************************************
	  \brief
	   Subtract another vector from this vector

	  \param _vec0
	   Vector to subtract
	*******************************************************************************/
	void Vec3::operator-=(const Vec3& pVec0) {
		x -= pVec0.x;
		y -= pVec0.y;
		z -= pVec0.z;
	}

	/*!*****************************************************************************
	  \brief
	   Subtract two vectors and return the result

	  \param _vec0
	   Vector to subtract

	  \return
	   Resulting vector after subtraction
	*******************************************************************************/
	Vec3 Vec3::operator-(const Vec3& pVec0) const {
		return Vec3(x - pVec0.x, y - pVec0.y, z - pVec0.z);
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
	Vec3 Vec3::Subtraction(const Vec3& vec1, const Vec3& vec2) {
		return Vec3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
	}

	/*!*****************************************************************************
	  \brief
	   Add a scaled version of another vector to this vector

	  \param _vec0
	   Vector to scale and add

	  \param _k
	   Scalar value to multiply _vec0 by before adding
	*******************************************************************************/
	void Vec3::Scaled_Vector_Adding(const Vec3& pVec0, float k) {
		x += pVec0.x * k;
		y += pVec0.y * k;
		z += pVec0.z * k;
	}

	/*!*****************************************************************************
	  \brief
	   Compute the component-wise product of two vectors

	  \param _vec0
	   Vector to multiply with

	  \return
	   Resulting vector after component-wise multiplication
	*******************************************************************************/
	Vec3 Vec3::Product_Component(const Vec3& pVec0) const {
		return Vec3(x * pVec0.x, y * pVec0.y, z * pVec0.z);
	}

	/*!*****************************************************************************
	  \brief
	   Update this vector with the component-wise product of another vector

	  \param _vec0
	   Vector to multiply with
	*******************************************************************************/
	void Vec3::Product_Component_Update(const Vec3& pVec0) {
		x *= pVec0.x;
		y *= pVec0.y;
		z *= pVec0.z;
	}

	/*!*****************************************************************************
	  \brief
	   Compute the dot product with another vector

	  \param _vec0
	   Vector to compute dot product with

	  \return
	   Resulting scalar after dot product
	*******************************************************************************/
	float Vec3::Product_Scalar(const Vec3& pVec0) const {
		return x * pVec0.x + y * pVec0.y + z * pVec0.z;
	}

	/*!*****************************************************************************
	  \brief
	   Compute the dot product with another vector (operator overload)

	  \param _vec0
	   Vector to compute dot product with

	  \return
	   Resulting scalar after dot product
	*******************************************************************************/
	float Vec3::operator*(const Vec3& pVec0) const {
		return x * pVec0.x + y * pVec0.y + z * pVec0.z;
	}

	/*!*****************************************************************************
	  \brief
	   Compute the cross product with another vector

	  \param _vec0
	   Vector to compute cross product with

	  \return
	   Resulting vector after cross product
	*******************************************************************************/
	Vec3 Vec3::Cross_Product(const Vec3& pVec0) const {
		return Vec3(y * pVec0.z - z * pVec0.y,
			z * pVec0.x - x * pVec0.z,
			x * pVec0.y - y * pVec0.x);
	}

	/*!*****************************************************************************
	  \brief
	   Compute the cross product with another vector and store the result in this vector

	  \param _vec0
	   Vector to compute cross product with
	*******************************************************************************/
	void Vec3::operator%=(const Vec3& pVec0) {
		Cross_Product(pVec0);
	}

	/*!*****************************************************************************
	 \brief
	  Compute the cross product with another vector and return the result

	 \param _vec0
	  Vector to compute cross product with

	 \return
	  Resulting vector after cross product
   *******************************************************************************/
	Vec3 Vec3::operator%(const Vec3& pVec0) const {
		return Vec3(y * pVec0.z - z * pVec0.y,
			z * pVec0.x - x * pVec0.z,
			x * pVec0.y - y * pVec0.x);
	}

	/*!*****************************************************************************
	  \brief
	   Reset the vector to zero
	*******************************************************************************/
	void Vec3::Clear() {
		x = 0;
		y = 0;
		z = 0;
	}

	/*!*****************************************************************************
	  \brief
	   Multiply a matrix by a vector

	  \param _mtx0
	   Matrix to multiply with

	  \param _vec0
	   Vector to multiply by

	  \return
	   Resulting vector after multiplication
	*******************************************************************************/
	Vec3 operator*(const Matrix3x3& pMtx0, const Vec3& pVec0)
	{
		Matrix3x3 pTrans{};
		pTrans.Matrix3Transpose(pMtx0);
		Vec3 result;

		const float* pData = pTrans.data();
		result.x = pData[0] * pVec0.x + pData[1] * pVec0.y + pData[2] * pVec0.z;
		result.y = pData[3] * pVec0.x + pData[4] * pVec0.y + pData[5] * pVec0.z;
		result.z = pData[6] * pVec0.x + pData[7] * pVec0.y + pData[8] * pVec0.z;
		return result;
		
	}

	/*!*****************************************************************************
	  \brief
	   Check if two vectors are equal

	  \param _lhs
	   Left-hand side vector

	  \param _rhs
	   Right-hand side vector

	  \return
	   True if vectors are equal, false otherwise
	*******************************************************************************/
	bool operator==(Vec3 const& lhs, Vec3 const& rhs) {
		return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
	}


}