/* Start Header ************************************************************************/
/*!
\file		Matrix4x4.cpp
\title		Memory's Flame
\author		Edwin Lee Zirui, edwinzirui.lee, 2301299 (100%)
\par		edwinzirui.lee@digipen.edu
\date		13 September 2024
\brief		Matrix4x4 class and class operation definition

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/

#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <cmath>
#include <algorithm>


namespace ToastBox {
	/*!*****************************************************************************
	\brief
		Constructs a Matrix4 object from an array of floats

	\param arr
		Pointer to an array of 16 floats representing the matrix elements
	*******************************************************************************/
	Matrix4::Matrix4(const float* arr) {
		std::copy(arr, arr + 16, matrixArray);
	}

	/*!*****************************************************************************
	\brief
		Constructs a Matrix4 object with specified elements

	\param AA, BB, CC, DD, EE, FF, GG, HH, II, JJ, KK, LL, MM, NN, OO, PP
		The 16 elements of the 4x4 matrix
	*******************************************************************************/
	Matrix4::Matrix4(float AA, float BB, float CC, float DD,
					 float EE, float FF, float GG, float HH,
					 float II, float JJ, float KK, float LL,
					 float MM, float NN, float OO, float PP)
		: Components{ AA, BB, CC, DD, EE, FF, GG, HH, II, JJ, KK, LL, MM, NN, OO, PP } {}

	/*!*****************************************************************************
	\brief
		Transposes the matrix

	\return
		A new Matrix4 object representing the transposed matrix
	*******************************************************************************/
	Matrix4 Matrix4::operator~() const {
		Matrix4 result = *this;
		result.Matrix4_Transpose(result);
		return result;
	}

	/*!*****************************************************************************
	\brief
		Assigns the values of another matrix to this matrix

	\param rhs
		The matrix to copy from

	\return
		A reference to this matrix after assignment
	*******************************************************************************/
	Matrix4 Matrix4::operator=(const Matrix4& rhs) {
		if (this != &rhs) {
			std::copy(rhs.matrixArray, rhs.matrixArray + 16, matrixArray);
		}
		return *this;
	}

	/*!*****************************************************************************
	\brief
		Sets the matrix to an identity matrix

	\param result
		The matrix to be set as an identity matrix
	*******************************************************************************/
	void Matrix4::Matrix4_Identity(Matrix4& result) {
		static const float identity[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		std::copy(identity, identity + 16, result.matrixArray);
	}

	/*!*****************************************************************************
	\brief
		Applies a translation to the matrix

	\param x, y, z
		The translation distances along the x, y, and z axes
	*******************************************************************************/
	void Matrix4::Matrix4_Translate(float x, float y, float z) {
		Components.d += x;
		Components.h += y;
		Components.l += z;
	}

	/*!*****************************************************************************
	\brief
		Applies a scaling to the matrix

	\param x, y, z
		The scaling factors along the x, y, and z axes
	*******************************************************************************/
	void Matrix4::Matrix4_Scale(float x, float y, float z) {
		Components.a *= x;
		Components.f *= y;
		Components.k *= z;
	}

	/*!*****************************************************************************
	\brief
		Applies a rotation around the X-axis (in radians)

	\param angle
		The rotation angle in radians
	*******************************************************************************/
	void Matrix4::Matrix4AxisXRotRad(float angle) {
		float c = std::cos(angle);
		float s = std::sin(angle);

		float temp_e = Components.e * c - Components.i * s;
		float temp_f = Components.f * c - Components.j * s;
		float temp_g = Components.g * c - Components.k * s;
		float temp_h = Components.h * c - Components.l * s;

		Components.i = Components.e * s + Components.i * c;
		Components.j = Components.f * s + Components.j * c;
		Components.k = Components.g * s + Components.k * c;
		Components.l = Components.h * s + Components.l * c;

		Components.e = temp_e;
		Components.f = temp_f;
		Components.g = temp_g;
		Components.h = temp_h;
	}

	/*!*****************************************************************************
	\brief
		Applies a rotation around the Y-axis (in radians)

	\param angle
		The rotation angle in radians
	*******************************************************************************/
	void Matrix4::Matrix4AxisYRotRad(float angle) {
		float c = std::cos(angle);
		float s = std::sin(angle);

		float temp_a = Components.a * c + Components.i * s;
		float temp_b = Components.b * c + Components.j * s;
		float temp_c = Components.c * c + Components.k * s;
		float temp_d = Components.d * c + Components.l * s;

		Components.i = -Components.a * s + Components.i * c;
		Components.j = -Components.b * s + Components.j * c;
		Components.k = -Components.c * s + Components.k * c;
		Components.l = -Components.d * s + Components.l * c;

		Components.a = temp_a;
		Components.b = temp_b;
		Components.c = temp_c;
		Components.d = temp_d;
	}

	/*!*****************************************************************************
	\brief
		Applies a rotation around the Z-axis (in radians)

	\param angle
		The rotation angle in radians
	*******************************************************************************/
	void Matrix4::Matrix4AxisZRotRad(float angle) {
		float c = std::cos(angle);
		float s = std::sin(angle);

		float temp_a = Components.a * c - Components.e * s;
		float temp_b = Components.b * c - Components.f * s;
		float temp_c = Components.c * c - Components.g * s;
		float temp_d = Components.d * c - Components.h * s;

		Components.e = Components.a * s + Components.e * c;
		Components.f = Components.b * s + Components.f * c;
		Components.g = Components.c * s + Components.g * c;
		Components.h = Components.d * s + Components.h * c;

		Components.a = temp_a;
		Components.b = temp_b;
		Components.c = temp_c;
		Components.d = temp_d;
	}

	/*!*****************************************************************************
	\brief
		Applies a rotation around the X-axis (in degrees)

	\param angle
		The rotation angle in degrees
	*******************************************************************************/
	void Matrix4::Matrix4AxisXRotDeg(float angle) {
		constexpr float PI = 3.14159265358979323846f;
		float radAngle = (angle / 180.0f) * PI;
		float cosAngle = std::cos(radAngle);
		float sinAngle = std::sin(radAngle);

		Components = {
			1.0f, 0.0f,     0.0f,      0.0f,
			0.0f, cosAngle, sinAngle,  0.0f,
			0.0f, -sinAngle, cosAngle, 0.0f,
			0.0f, 0.0f,     0.0f,      1.0f
		};
	}

	/*!*****************************************************************************
	\brief
		Applies a rotation around the Y-axis (in degrees)

	\param angle
		The rotation angle in degrees
	*******************************************************************************/
	void Matrix4::Matrix4AxisYRotDeg(float angle) {
		constexpr float PI = 3.14159265358979323846f;
		float radAngle = (angle / 180.0f) * PI;
		float cosAngle = std::cos(radAngle);
		float sinAngle = std::sin(radAngle);

		Components = {
			cosAngle, 0.0f, -sinAngle, 0.0f,
			0.0f,     1.0f, 0.0f,      0.0f,
			sinAngle, 0.0f, cosAngle,  0.0f,
			0.0f,     0.0f, 0.0f,      1.0f
		};
	}

	/*!*****************************************************************************
	\brief
		Applies a rotation around the Z-axis (in degrees)

	\param angle
		The rotation angle in degrees
	*******************************************************************************/
	void Matrix4::Matrix4AxisZRotDeg(float angle) {
		constexpr float PI = 3.14159265358979323846f;
		float radAngle = (angle / 180.0f) * PI;
		float cosAngle = std::cos(radAngle);
		float sinAngle = std::sin(radAngle);

		Components = {
			cosAngle, -sinAngle, 0.0f, 0.0f,
			sinAngle, cosAngle,  0.0f, 0.0f,
			0.0f,     0.0f,      1.0f, 0.0f,
			0.0f,     0.0f,      0.0f, 1.0f
		};
	}

	/*!*****************************************************************************
	\brief
		Transposes the matrix

	\param mtx
		The matrix to be transposed
	*******************************************************************************/
	void Matrix4::Matrix4_Transpose(const Matrix4& mtx) {
		std::swap(Components.b, Components.e);
		std::swap(Components.c, Components.i);
		std::swap(Components.d, Components.m);
		std::swap(Components.g, Components.j);
		std::swap(Components.h, Components.n);
		std::swap(Components.l, Components.o);
	}

	/*!*****************************************************************************
	\brief
		Adds another matrix to this matrix

	\param rhs
		The matrix to be added
	*******************************************************************************/
	void Matrix4::Matrix4_Add(const Matrix4& rhs) {
		for (int i = 0; i < 16; ++i) {
			matrixArray[i] += rhs.matrixArray[i];
		}
	}

	/*!*****************************************************************************
	\brief
		Adds two matrices and returns the result

	\param lhs, rhs
		The matrices to be added

	\return
		A new Matrix4 object representing the sum of the two matrices
	*******************************************************************************/
	Matrix4 Matrix4::Matrix4_Add2(const Matrix4& lhs, const Matrix4& rhs) {
		Matrix4 result;
		for (int i = 0; i < 16; ++i) {
			result.matrixArray[i] = lhs.matrixArray[i] + rhs.matrixArray[i];
		}
		return result;
	}

	/*!*****************************************************************************
	\brief
		Subtracts another matrix from this matrix

	\param rhs
		The matrix to be subtracted
	*******************************************************************************/
	void Matrix4::Matrix4_Sub(const Matrix4& rhs) {
		for (int i = 0; i < 16; ++i) {
			matrixArray[i] -= rhs.matrixArray[i];
		}
	}

	/*!*****************************************************************************
    \brief
	   Subtracts one matrix from another and returns the result
    \param lhs, rhs
	   The matrices for the subtraction operation
    \return
	   A new Matrix4 object representing the difference of the two matrices
    *******************************************************************************/
	Matrix4 Matrix4::Matrix4_Sub2(const Matrix4& lhs, const Matrix4& rhs) {
		Matrix4 result;
		for (int i = 0; i < 16; ++i) {
			result.matrixArray[i] = lhs.matrixArray[i] - rhs.matrixArray[i];
		}
		return result;
	}

	/*!*****************************************************************************
	\brief
		Multiplies the matrix by a scalar

	\param scale
		The scalar value to multiply by
	*******************************************************************************/
	void Matrix4::Matrix4_Mul(const float scale) {
		for (int i = 0; i < 16; ++i) {
			matrixArray[i] *= scale;
		}
	}

	/*!*****************************************************************************
	\brief
		Multiplies a matrix by a scalar and returns the result

	\param rhs
		The matrix to be multiplied

	\param scale
		The scalar value to multiply by

	\return
		A new Matrix4 object representing the scaled matrix
	*******************************************************************************/
	Matrix4 Matrix4::Matrix4_Mul2(const Matrix4& rhs, const float scale) {
		Matrix4 result = rhs;
		result.Matrix4_Mul(scale);
		return result;
	}

	/*!*****************************************************************************
	\brief
		Divides the matrix by a scalar

	\param scale
		The scalar value to divide by
	*******************************************************************************/
	void Matrix4::Matrix4_Div(const float scale) {
		if (scale != 0) {
			float invScale = 1.0f / scale;
			for (int i = 0; i < 16; ++i) {
				matrixArray[i] *= invScale;
			}
		}
	}

	/*!*****************************************************************************
	\brief
		Divides a matrix by a scalar and returns the result
	\param rhs
		The matrix to be divided
	\param scale
		The scalar value to divide by
	\return
		A new Matrix4 object representing the divided matrix
	*******************************************************************************/
	Matrix4 Matrix4::Matrix4_Div2(const Matrix4& rhs, const float scale) {
		Matrix4 result = rhs;
		result.Matrix4_Div(scale);
		return result;
	}

	/*!*****************************************************************************
	\brief
		Gets the matrix elements
	\return
		A copy of the current matrix
	*******************************************************************************/
	Matrix4 Matrix4::Get_Matrix_Elements() const {
		return *this;
	}

	/*!*****************************************************************************
	\brief
		Gets the matrix
	\return
		A copy of the current matrix
	*******************************************************************************/
	Matrix4 Matrix4::Get_Matrix() const {
		return *this;
	}

	/*!*****************************************************************************
    \brief
	    Sets the matrix elements
    \param a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44
	    The 16 elements of the 4x4 matrix
    \return
	    A reference to this matrix after setting the elements
    *******************************************************************************/
	Matrix4 Matrix4::Set_Matrix(float a11, float a12, float a13, float a14,
								float a21, float a22, float a23, float a24,
								float a31, float a32, float a33, float a34,
								float a41, float a42, float a43, float a44) {
		Components = { a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44 };
		return *this;
	}

	/*!*****************************************************************************
	\brief
		Gets a pointer to the matrix data
	\return
		A pointer to the first element of the matrix array
	*******************************************************************************/
	float* Matrix4::Data() {
		return matrixArray;
	}

	/*!*****************************************************************************
	\brief
		Gets a const pointer to the matrix data
	\return
		A const pointer to the first element of the matrix array
	*******************************************************************************/
	const float* Matrix4::Data() const {
		return matrixArray;
	}
}
