/* Start Header ************************************************************************/
/*!
\file		Vector3.h
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		07 September 2024
\brief		Vector3 class and class operation declaration

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once

namespace ToastBox {
	class Matrix3x3;
	class Vec3 {
	public:
		float x{}, y{}, z{};
	private:
		float padding{};
	public:
		/*!*****************************************************************************
		  \brief
		   Default constructor for Vector3
		*******************************************************************************/
		Vec3();
		
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
		Vec3(const float x, const float y, const float z);

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
		void Normalize(Vec3& pResult, const Vec3& pVec0);

		/*!*****************************************************************************
		  \brief
		   Multiply the vector by a scalar

		  \param _value
		   Scalar value to multiply by
		*******************************************************************************/
		void operator*= (const float value);

		/*!*****************************************************************************
		  \brief
		   Multiply the vector by a scalar and return the result

		  \param _value
		   Scalar value to multiply by

		  \return
		   Resulting vector after multiplication
		*******************************************************************************/
		Vec3 operator*(const float value) const;

		/*!*****************************************************************************
		  \brief
		   Divide this vector by another vector component-wise

		  \param _vec0
		   Vector to divide by
		*******************************************************************************/
		void operator/=(const Vec3& pVec0);

		/*!*****************************************************************************
		  \brief
		   Divide this vector by a scalar and return the result

		  \param _value
		   Scalar value to divide by

		  \return
		   Resulting vector after division
		*******************************************************************************/
		Vec3 operator/(const float value) const;

		/*!*****************************************************************************
		  \brief
		   Add another vector to this vector

		  \param _vec0
		   Vector to add
		*******************************************************************************/
		void operator+=(const Vec3& pVec0);

		/*!*****************************************************************************
		  \brief
		   Add two vectors and return the result

		  \param _vec0
		   Vector to add

		  \return
		   Resulting vector after addition
		*******************************************************************************/
		Vec3 operator+(const Vec3& pVec0) const;

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
		Vec3 Addition(const Vec3& vec1, const Vec3& vec2);

		/*!*****************************************************************************
		  \brief
		   Subtract another vector from this vector

		  \param _vec0
		   Vector to subtract
		*******************************************************************************/
		void operator-=(const Vec3& pVec0);

		/*!*****************************************************************************
		  \brief
		   Subtract two vectors and return the result

		  \param _vec0
		   Vector to subtract

		  \return
		   Resulting vector after subtraction
		*******************************************************************************/
		Vec3 operator-(const Vec3& pVec0) const;
		
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
		Vec3 Subtraction(const Vec3& vec1, const Vec3& vec2);

		/*!*****************************************************************************
		  \brief
		   Add a scaled version of another vector to this vector

		  \param _vec0
		   Vector to scale and add

		  \param _k
		   Scalar value to multiply _vec0 by before adding
		*******************************************************************************/
		void Scaled_Vector_Adding(const Vec3& pVec0, float k);

		/*!*****************************************************************************
		  \brief
		   Compute the component-wise product of two vectors

		  \param _vec0
		   Vector to multiply with

		  \return
		   Resulting vector after component-wise multiplication
		*******************************************************************************/
		Vec3 Product_Component(const Vec3& pVec0) const;

		/*!*****************************************************************************
		  \brief
		   Update this vector with the component-wise product of another vector

		  \param _vec0
		   Vector to multiply with
		*******************************************************************************/
		void Product_Component_Update(const Vec3& pVec0);

		/*!*****************************************************************************
		  \brief
		   Compute the dot product with another vector

		  \param _vec0
		   Vector to compute dot product with

		  \return
		   Resulting scalar after dot product
		*******************************************************************************/
		float Product_Scalar(const Vec3& pVec0) const;

		/*!*****************************************************************************
		  \brief
		   Compute the dot product with another vector (operator overload)

		  \param _vec0
		   Vector to compute dot product with

		  \return
		   Resulting scalar after dot product
		*******************************************************************************/
		float operator*(const Vec3& pVec0) const;

		/*!*****************************************************************************
		  \brief
		   Compute the cross product with another vector

		  \param _vec0
		   Vector to compute cross product with

		  \return
		   Resulting vector after cross product
		*******************************************************************************/
		Vec3 Cross_Product(const Vec3& pVec0) const;

		/*!*****************************************************************************
		  \brief
		   Compute the cross product with another vector and store the result in this vector

		  \param _vec0
		   Vector to compute cross product with
		*******************************************************************************/
		void operator%=(const Vec3& pVec0);

		/*!*****************************************************************************
		  \brief
		   Compute the cross product with another vector and return the result

		  \param _vec0
		   Vector to compute cross product with

		  \return
		   Resulting vector after cross product
		*******************************************************************************/
		Vec3 operator%(const Vec3& pVec0) const;

		/*!*****************************************************************************
		  \brief
		  Overloads subscript operator to access x, y or z in the Vec3

		  \param _index
		  Index to return

		  \return
		  float in x, y or z
		*******************************************************************************/
		float& operator[](unsigned int const index);

		/*!*****************************************************************************
		  \brief
		  Overloads subscript operator to access x, y or z in the Vec3

		  \param _index
		  Index to return

		  \return
		  float in x, y or z
		*******************************************************************************/
		float const& operator[](unsigned int const index) const;

		/*!*****************************************************************************
		  \brief
		   Reset the vector to zero
		*******************************************************************************/
		void Clear();

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
		friend Vec3 operator*(const Matrix3x3& pMtx0, const Vec3& pVec0);


	};

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
	bool operator==(Vec3 const& lhs, Vec3 const& rhs);
	
}
