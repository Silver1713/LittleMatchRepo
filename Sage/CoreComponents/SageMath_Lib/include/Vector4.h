/* Start Header ************************************************************************/
/*!
\file		Vector4.h
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		13 September 2024
\brief		Vector4 class and class operation declaration

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#ifndef TOAST_VEC4_HPP
#define TOAST_VEC4_HPP
namespace ToastBox
{
	class Vec4;
	using Vector4 =  Vec4;

	class Vec4
	{
	public:
		union
		{
			float x, r, s;
		};
		union
		{
			float y, g, t;
		};

		union
		{
			float z, b, p;
		};

		union
		{
			float w, a, q;
		};

		/*!*****************************************************************************
		  \brief
		   Default constructor initializing all components to zero

		  \return
		   Initialized Vec4 object
		*******************************************************************************/
		Vec4() :x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {}

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
		Vec4( float const& x,  float const& y,  float const& z,  float const& w);

		/*!*****************************************************************************
		  \brief
		   Copy constructor

		  \param pVec0
		   Vector to be copied

		  \return
		   New Vec4 object as a copy of pVec0
		*******************************************************************************/
		Vec4(const Vec4& pVec0);

		/*!*****************************************************************************
		  \brief
		   Negation operator

		  \return
		   Negated vector
		*******************************************************************************/
		Vec4& operator-();

		/*!*****************************************************************************
		  \brief
		   Scalar multiplication assignment operator

		  \param value
		   Scalar to multiply with

		  \return
		   Reference to this vector after multiplication
		*******************************************************************************/
		Vec4& operator*=(const float value);

		/*!*****************************************************************************
		  \brief
		   Vector division assignment operator

		  \param pVec0
		   Vector to divide by

		  \return
		   Reference to this vector after division
		*******************************************************************************/
		Vec4& operator/=(const Vec4& pVec0);

		/*!*****************************************************************************
		  \brief
		   Scalar division assignment operator

		  \param value
		   Scalar to divide by

		  \return
		   Reference to this vector after division
		*******************************************************************************/
		Vec4& operator/=(const float value);

		/*!*****************************************************************************
		  \brief
		   Vector addition assignment operator

		  \param pVec0
		   Vector to add

		  \return
		   Reference to this vector after addition
		*******************************************************************************/
		Vec4& operator+=(const Vec4& pVec0);

		/*!*****************************************************************************
		  \brief
		   Vector subtraction assignment operator

		  \param pVec0
		   Vector to subtract

		  \return
		   Reference to this vector after subtraction
		*******************************************************************************/
		Vec4& operator-=(const Vec4& pVec0);

		/*!*****************************************************************************
		  \brief
		   Assignment operator

		  \param pVec0
		   Vector to assign from

		  \return
		   Reference to this vector after assignment
		*******************************************************************************/
		Vec4& operator=(const Vec4& pVec0);

		/*!*****************************************************************************
		  \brief
		   Cross product assignment operator

		  \param pVec0
		   Vector to cross with

		  \return
		   Reference to this vector after cross product
		*******************************************************************************/
		Vec4& operator%=(const Vec4& pVec0);

		/*!*****************************************************************************
		  \brief
		   Indexed access operator (mutable)

		  \param index
		   Index of the component to access

		  \return
		   Reference to the component at the specified index
		*******************************************************************************/
		float& operator[](int index);

		/*!*****************************************************************************
		  \brief
		   Indexed access operator (const)

		  \param index
		   Index of the component to access

		  \return
		   Value of the component at the specified index
		*******************************************************************************/
		float operator[](int index) const;

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
		   Normalize a vector

		  \param pResult
		   Vector to store the normalized result
		  \param pVec0
		   Vector to be normalized
		*******************************************************************************/
		void Normalize(Vec4& pResult, const Vec4& pVec0);

		/*!*****************************************************************************
		  \brief
		   Get a pointer to the vector's data

		  \return
		   Pointer to the first component of the vector
		*******************************************************************************/
		float* Data();
		

	};


	/*!*****************************************************************************
	  \brief
	   Vector addition operator

	  \param pVec0
	   First vector
	  \param pVec1
	   Second vector

	  \return
	   Sum of the two vectors
	*******************************************************************************/
	Vector4 operator+(const Vector4& pVec0, const Vector4& pVec1);

	/*!*****************************************************************************
	  \brief
	   Vector subtraction operator

	  \param pVec0
	   First vector
	  \param pVec1
	   Second vector

	  \return
	   Difference of the two vectors
	*******************************************************************************/
	Vector4 operator-(const Vector4& pVec0, const Vector4& pVec1); 

	/*!*****************************************************************************
	  \brief
	   Scalar multiplication operator (vector * scalar)

	  \param pVec0
	   Vector to scale
	  \param value
	   Scalar value

	  \return
	   Scaled vector
	*******************************************************************************/
	Vector4 operator*(const Vector4& pVec0, const float value);

	/*!*****************************************************************************
	  \brief
	   Scalar multiplication operator (scalar * vector)

	  \param value
	   Scalar value
	  \param pVec0
	   Vector to scale

	  \return
	   Scaled vector
	*******************************************************************************/
	Vector4 operator*(const float value, const Vector4& pVec0);
	
	/*!*****************************************************************************
	  \brief
	   Scalar division operator (scalar / vector)

	  \param value
	   Scalar value
	  \param pVec0
	   Vector to divide

	  \return
	   Result of scalar divided by vector
	*******************************************************************************/
	Vector4 operator/(const float value, const Vector4& pVec0);

	/*!*****************************************************************************
	  \brief
	   Scalar division operator (vector / scalar)

	  \param pVec0
	   Vector to divide
	  \param value
	   Scalar value

	  \return
	   Vector divided by scalar
	*******************************************************************************/
	Vector4 operator/(const Vector4& pVec0, const float value);

	/*!*****************************************************************************
	  \brief
	   Dot product operator

	  \param pVec0
	   First vector
	  \param pVec1
	   Second vector

	  \return
	   Dot product of the two vectors
	*******************************************************************************/
	float operator*(const Vector4& pVec0, const Vector4& pVec1);

	/*!*****************************************************************************
	  \brief
	   Vector division operator

	  \param pVec0
	   Numerator vector
	  \param pVec1
	   Denominator vector

	  \return
	   Result of component-wise division
	*******************************************************************************/
	Vector4 operator/(const Vector4& pVec0, const Vector4& pVec1);

	/*!*****************************************************************************
	  \brief
	   Cross product operator

	  \param pVec0
	   First vector
	  \param pVec1
	   Second vector

	  \return
	   Cross product of the two vectors
	*******************************************************************************/
	Vector4 operator%(const Vector4& pVec0, const Vector4& pVec1);

}
#endif