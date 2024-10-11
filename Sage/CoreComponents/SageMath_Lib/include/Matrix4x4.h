/* Start Header ************************************************************************/
/*!
\file		Matrix4x4.h
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		13 September 2024
\brief		Matrix4x4 class and class operation declaration
			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace ToastBox {
	class Matrix4 {
	private:
		union {
			struct {
				float a{}, b{}, c{}, d{};
				float e{}, f{}, g{}, h{};
				float i{}, j{}, k{}, l{};
				float m{}, n{}, o{}, p{};
			} Components;
			float matrixArray[16]{};
		};
	public:
		/*!*****************************************************************************
		\brief
			Default constructor. Initializes the matrix to zero.
		*******************************************************************************/
		Matrix4() = default;

		/*!*****************************************************************************
		\brief
			Constructs a Matrix4 object from an array of floats.

		\param arr
			Pointer to an array of 16 floats representing the matrix elements.
		*******************************************************************************/
		Matrix4(const float* arr);

		/*!*****************************************************************************
		\brief
			Constructs a Matrix4 object with specified elements.

		\param AA, BB, CC, DD, EE, FF, GG, HH, II, JJ, KK, LL, MM, NN, OO, PP
			The 16 elements of the 4x4 matrix.
		*******************************************************************************/
		Matrix4(float AA, float BB, float CC, float DD,
			float EE, float FF, float GG, float HH,
			float II, float JJ, float KK, float LL,
			float MM, float NN, float OO, float PP);

		/*!*****************************************************************************
		\brief
			Transposes the matrix.

		\return
			A new Matrix4 object representing the transposed matrix.
		*******************************************************************************/
		Matrix4 operator~() const;

		/*!*****************************************************************************
		\brief
			Assigns the values of another matrix to this matrix
			.
		\param rhs
			The matrix to copy from.

		\return
			A reference to this matrix after assignment.
		*******************************************************************************/
		Matrix4 operator=(const Matrix4& rhs);

		/*!*****************************************************************************
		\brief
			Sets the matrix to an identity matrix.

		\param result
			The matrix to be set as an identity matrix.
		*******************************************************************************/
		void Matrix4_Identity(Matrix4& result);

		/*!*****************************************************************************
		\brief
			Applies a translation to the matrix.

		\param x, y, z
			The translation distances along the x, y, and z axes.
		*******************************************************************************/
		void Matrix4_Translate(float x, float y, float z);

		/*!*****************************************************************************
		\brief
			Applies a scaling to the matrix.

		\param x, y, z
			The scaling factors along the x, y, and z axes.
		*******************************************************************************/
		void Matrix4_Scale(float x, float y, float z);

		/*!*****************************************************************************
		\brief
			Applies a rotation around the X-axis (in radians).

		\param angle
			The rotation angle in radians.
		*******************************************************************************/
		void Matrix4AxisXRotRad(float angle);

		/*!*****************************************************************************
		\brief
			Applies a rotation around the Y-axis (in radians).

		\param angle
			The rotation angle in radians.
		*******************************************************************************/
		void Matrix4AxisYRotRad(float angle);

		/*!*****************************************************************************
		\brief
			Applies a rotation around the Z-axis (in radians).

		\param angle
			The rotation angle in radians.
		*******************************************************************************/
		void Matrix4AxisZRotRad(float angle);

		/*!*****************************************************************************
		\brief
			Applies a rotation around the X-axis (in degrees).

		\param angle
			The rotation angle in degrees.
		*******************************************************************************/
		void Matrix4AxisXRotDeg(float angle);

		/*!*****************************************************************************
		\brief
			Applies a rotation around the Y-axis (in degrees).

		\param angle
			The rotation angle in degrees.
		*******************************************************************************/
		void Matrix4AxisYRotDeg(float angle);

		/*!*****************************************************************************
		\brief
			Applies a rotation around the Z-axis (in degrees).

		\param angle
			The rotation angle in degrees.
		*******************************************************************************/
		void Matrix4AxisZRotDeg(float angle);

		/*!*****************************************************************************
		\brief
			Transposes the matrix.

		\param mtx
			The matrix to be transposed.
		*******************************************************************************/
		void Matrix4_Transpose(const Matrix4& mtx);

		/*!*****************************************************************************
		\brief
			Adds another matrix to this matrix.

		\param rhs
			The matrix to be added.
		*******************************************************************************/
		void Matrix4_Add(const Matrix4& rhs);

		/*!*****************************************************************************
		\brief
			Adds two matrices and returns the result.

		\param lhs, rhs
			The matrices to be added.

		\return
			A new Matrix4 object representing the sum of the two matrices.
		*******************************************************************************/
		Matrix4 Matrix4_Add2(const Matrix4& lhs, const Matrix4& rhs);

		/*!*****************************************************************************
		\brief
			Subtracts another matrix from this matrix.

		\param rhs
			The matrix to be subtracted.
		*******************************************************************************/
		void Matrix4_Sub(const Matrix4& rhs);

		/*!*****************************************************************************
		\brief
			Subtracts one matrix from another and returns the result.

		\param lhs, rhs
			The matrices for the subtraction operation.

		\return
			A new Matrix4 object representing the difference of the two matrices.
		*******************************************************************************/
		Matrix4 Matrix4_Sub2(const Matrix4& lhs, const Matrix4& rhs);

		/*!*****************************************************************************
		\brief
			Multiplies the matrix by a scalar.

		\param scale
			The scalar value to multiply by.
		*******************************************************************************/
		void Matrix4_Mul(const float scale);

		/*!*****************************************************************************
		\brief
			Multiplies a matrix by a scalar and returns the result.

		\param rhs
			The matrix to be multiplied.

		\param scale
			The scalar value to multiply by.

		\return
			A new Matrix4 object representing the scaled matrix.
		*******************************************************************************/
		Matrix4 Matrix4_Mul2(const Matrix4& rhs, const float scale);

		/*!*****************************************************************************
		\brief
			Divides the matrix by a scalar.

		\param scale
			The scalar value to divide by.
		*******************************************************************************/
		void Matrix4_Div(const float scale);

		/*!*****************************************************************************
		\brief
			Divides a matrix by a scalar and returns the result.

		\param rhs
			The matrix to be divided.

		\param scale
			The scalar value to divide by.

		\return
			A new Matrix4 object representing the divided matrix.
		*******************************************************************************/
		Matrix4 Matrix4_Div2(const Matrix4& rhs, const float scale);

		/*!*****************************************************************************
		\brief
			Gets the matrix elements.

		\return
			A copy of the current matrix.
		*******************************************************************************/
		Matrix4 Get_Matrix_Elements() const;

		/*!*****************************************************************************
		\brief
			Gets the matrix.

		\return
			A copy of the current matrix.
		*******************************************************************************/
		Matrix4 Get_Matrix() const;

		/*!*****************************************************************************
		\brief
			Sets the matrix elements.

		\param [16 float parameters]
			The 16 elements of the 4x4 matrix.

		\return
			A reference to this matrix after setting the elements.
		*******************************************************************************/
		Matrix4 Set_Matrix(float, float, float, float,
			float, float, float, float,
			float, float, float, float,
			float, float, float, float);

		/*!*****************************************************************************
		\brief
			Gets a pointer to the matrix data.

		\return
			A pointer to the first element of the matrix array.
		*******************************************************************************/
		float* Data();

		/*!*****************************************************************************
		\brief
			Gets a const pointer to the matrix data.

		\return
			A const pointer to the first element of the matrix array.
		*******************************************************************************/
		const float* Data() const;
	};
}