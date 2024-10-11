/* Start Header ************************************************************************/
/*!
\file		Matrix3x3.cpp
\title		Memory's Flame
\author		Halis Ilyasa Bin Amat Sarijan, halisilyasa.b, 2301333 (100%)
\par		halisilyasa.b@digipen.edu
\date		08 September 2024
\brief		Contains the functions to calculate matrices.

			All content � 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/


#include "Matrix3x3.h"
#include <cmath>

//Defines epsilon
constexpr float EPSILON = 0.0001f;

//Defines pi
constexpr float PI = 3.14159265358f;

namespace ToastBox {
	/*!*****************************************************************************
	  \brief
		Constructor for class matrix.
	*******************************************************************************/
	Matrix3x3::Matrix3x3()
		: m{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f } {}


	/*!*****************************************************************************
	  \brief
		Constructor for class matrix.

	  \param _arr
		
	*******************************************************************************/
	Matrix3x3::Matrix3x3(const float* arr)
		: m{ arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8] } {}

	/*!*****************************************************************************
	  \brief
		Constructor for class matrix.
	*******************************************************************************/
	Matrix3x3::Matrix3x3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
		: m{ _00, _01, _02, _10, _11, _12, _20, _21, _22 } {}

	/*!*****************************************************************************
	  \brief
		Copy Assignment for class matrix.

	  \param _rhs
		The other matrix.

	  \return
		The current matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::operator=(const Matrix3x3& _rhs) {
		for (int i{ 0 }; i < 9; i++) {
			m[i] = _rhs.m[i];
		}

		matrix.m00 = m[0];
		matrix.m01 = m[1];
		matrix.m02 = m[2];
		matrix.m10 = m[3];
		matrix.m11 = m[4];
		matrix.m12 = m[5];
		matrix.m20 = m[6];
		matrix.m21 = m[7];
		matrix.m22 = m[8];

		return *this;
	}

	/*!*****************************************************************************
	  \brief
		Operator overload for ~ to transpose a matrix.

	  \return
		The result of transposing the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::operator~()
	{
		Matrix3x3 result{};
		result.Matrix3Transpose(*this);
		return result;
	}

	/*!*****************************************************************************
	  \brief
		Creates an identity matrix to the current matrix.
	*******************************************************************************/
	void Matrix3x3::Matrix3Identity() {
		Matrix3x3 id(1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.f,
			0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 9; i++) {
			m[i] = id.m[i];
		}

		matrix.m00 = m[0];
		matrix.m01 = m[1];
		matrix.m02 = m[2];
		matrix.m10 = m[3];
		matrix.m11 = m[4];
		matrix.m12 = m[5];
		matrix.m20 = m[6];
		matrix.m21 = m[7];
		matrix.m22 = m[8];
	}

	/*!*****************************************************************************
	  \brief
		Performs translation transformation to the matrix.

	  \param _x
		The x translation.

	  \param _y
		The y translation.
	*******************************************************************************/
	void Matrix3x3::Matrix3Translate(float _x, float _y) {
		Matrix3x3 id(1.0f, 0.0f, _x,
			0.0f, 1.0f, _y,
			0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 9; i++) {
			m[i] = id.m[i];
		}

		matrix.m00 = m[0];
		matrix.m01 = m[1];
		matrix.m02 = m[2];
		matrix.m10 = m[3];
		matrix.m11 = m[4];
		matrix.m12 = m[5];
		matrix.m20 = m[6];
		matrix.m21 = m[7];
		matrix.m22 = m[8];
	}

	/*!*****************************************************************************
	  \brief
		Performs scaling transformation to the matrix.

	  \param _x
		The x scale.

	  \param _y
		The y scale.
	*******************************************************************************/
	void Matrix3x3::Matrix3Scale(float _x, float _y) {
		Matrix3x3 id(1.0f * _x, 0.0f, 0.0f,
			0.0f, 1.0f * _y, 0.0f,
			0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 9; i++) {
			m[i] = id.m[i];
		}

		matrix.m00 = m[0];
		matrix.m01 = m[1];
		matrix.m02 = m[2];
		matrix.m10 = m[3];
		matrix.m11 = m[4];
		matrix.m12 = m[5];
		matrix.m20 = m[6];
		matrix.m21 = m[7];
		matrix.m22 = m[8];
	}

	/*!*****************************************************************************
	  \brief
		Performs radian rotation transformation to the matrix.

	  \param _angle
	    The angle (in radian) of the rotation.
	*******************************************************************************/
	void Matrix3x3::Matrix3RotRad(float _angle) {
		Matrix3x3 id((float)cos(_angle), (float)-sin(_angle), 0.0f,
			(float)sin(_angle), (float)cos(_angle), 0.0f,
			0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 9; i++) {
			m[i] = id.m[i];
		}

		matrix.m00 = m[0];
		matrix.m01 = m[1];
		matrix.m02 = m[2];
		matrix.m10 = m[3];
		matrix.m11 = m[4];
		matrix.m12 = m[5];
		matrix.m20 = m[6];
		matrix.m21 = m[7];
		matrix.m22 = m[8];
	}

	/*!*****************************************************************************
	  \brief
		Performs degree rotation transformation to the matrix.

	  \param _angle
		The angle (in degree) of the rotation.
	*******************************************************************************/
	void Matrix3x3::Matrix3RotDeg(float _angle) {
		float radAngle = (_angle * PI / 180);

		Matrix3x3 id((float)cos(radAngle), (float)-sin(radAngle), 0.0f,
			(float)sin(radAngle), (float)cos(radAngle), 0.0f,
			0.0f, 0.0f, 1.0f);


		for (int i = 0; i < 9; i++)
		{
			m[i] = id.m[i];
		}

		matrix.m00 = m[0];
		matrix.m01 = m[1];
		matrix.m02 = m[2];
		matrix.m10 = m[3];
		matrix.m11 = m[4];
		matrix.m12 = m[5];
		matrix.m20 = m[6];
		matrix.m21 = m[7];
		matrix.m22 = m[8];
	}

	/*!*****************************************************************************
	  \brief
		Transposes a matrix.

	  \param _p_mtx
		The matrix itself.
	*******************************************************************************/
	void Matrix3x3::Matrix3Transpose(const Matrix3x3& _p_mtx) {
		m[0] = _p_mtx.m[0];
		m[3] = _p_mtx.m[1];
		m[6] = _p_mtx.m[2];
		m[1] = _p_mtx.m[3];
		m[4] = _p_mtx.m[4];
		m[7] = _p_mtx.m[5];
		m[2] = _p_mtx.m[6];
		m[5] = _p_mtx.m[7];
		m[8] = _p_mtx.m[8];

		matrix.m00 = m[0];
		matrix.m01 = m[1];
		matrix.m02 = m[2];
		matrix.m10 = m[3];
		matrix.m11 = m[4];
		matrix.m12 = m[5];
		matrix.m20 = m[6];
		matrix.m21 = m[7];
		matrix.m22 = m[8];
	}

	/*!*****************************************************************************
	  \brief
		Invereses a matrix.

	  \param _mtx
		The matrix itself.
	*******************************************************************************/
	void Matrix3x3::Matrix3SetInverse(const Matrix3x3& _mtx) {
		float t4 = _mtx.matrix.m00 * _mtx.matrix.m11;
		float t6 = _mtx.matrix.m00 * _mtx.matrix.m12;
		float t8 = _mtx.matrix.m01 * _mtx.matrix.m10;
		float t10 = _mtx.matrix.m02 * _mtx.matrix.m10;
		float t12 = _mtx.matrix.m01 * _mtx.matrix.m20;
		float t14 = _mtx.matrix.m02 * _mtx.matrix.m20;

		float t16 = (t4 * _mtx.matrix.m22 - t6 * _mtx.matrix.m21 - t8 * _mtx.matrix.m22 +
			t10 * _mtx.matrix.m21 + t12 * _mtx.matrix.m12 - t14 * _mtx.matrix.m11);

		if (t16 == (float)0.0f) {
			return;
		}
		float t17 = 1 / t16;

		matrix.m00 = (_mtx.matrix.m11 * _mtx.matrix.m22 - _mtx.matrix.m12 * _mtx.matrix.m21) * t17;
		matrix.m01 = -(_mtx.matrix.m01 * _mtx.matrix.m22 - _mtx.matrix.m02 * _mtx.matrix.m21) * t17;
		matrix.m02 = (_mtx.matrix.m01 * _mtx.matrix.m12 - _mtx.matrix.m02 * _mtx.matrix.m11) * t17;
		matrix.m10 = -(_mtx.matrix.m10 * _mtx.matrix.m22 - _mtx.matrix.m12 * _mtx.matrix.m20) * t17;
		matrix.m11 = (_mtx.matrix.m00 * _mtx.matrix.m22 - t14) * t17;
		matrix.m12 = -(t6 - t10) * t17;
		matrix.m20 = (_mtx.matrix.m10 * _mtx.matrix.m21 - _mtx.matrix.m11 * _mtx.matrix.m20) * t17;
		matrix.m21 = -(_mtx.matrix.m00 * _mtx.matrix.m21 - t12) * t17;
		matrix.m22 = (t4 - t8) * t17;

		m[0] = matrix.m00;
		m[1] = matrix.m01;
		m[2] = matrix.m02;
		m[3] = matrix.m10;
		m[4] = matrix.m11;
		m[5] = matrix.m12;
		m[6] = matrix.m20;
		m[7] = matrix.m21;
		m[8] = matrix.m22;
	}

	/*!*****************************************************************************
	  \brief
		Invereses a matrix.

	  \return
	    The copy of the matrix but inversed.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::inverse() const {
		Matrix3x3 result;
		result.Matrix3SetInverse(*this);
		return result;
	}

	/*!*****************************************************************************
	  \brief
		Invereses a matrix.

	  \return
		The matrix itself.
	*******************************************************************************/
	void Matrix3x3::invert() {
		return Matrix3SetInverse(*this);
	}

	/*!*****************************************************************************
	  \brief
		Performs addition calculation to a matrix

	  \param _rhs
		The other matrix.
	*******************************************************************************/
	void Matrix3x3::Matrix3Add(const Matrix3x3& _rhs) {
		matrix.m00 += _rhs.matrix.m00;
		matrix.m01 += _rhs.matrix.m01;
		matrix.m02 += _rhs.matrix.m02;
		matrix.m10 += _rhs.matrix.m10;
		matrix.m11 += _rhs.matrix.m11;
		matrix.m12 += _rhs.matrix.m12;
		matrix.m20 += _rhs.matrix.m20;
		matrix.m21 += _rhs.matrix.m21;
		matrix.m22 += _rhs.matrix.m22;

		m[0] = matrix.m00;
		m[1] = matrix.m01;
		m[2] = matrix.m02;
		m[3] = matrix.m10;
		m[4] = matrix.m11;
		m[5] = matrix.m12;
		m[6] = matrix.m20;
		m[7] = matrix.m21;
		m[8] = matrix.m22;
	}

	/*!*****************************************************************************
	  \brief
		Performs addition calculation to 2 matrices

	  \param _lhs
		The first matrix.

	  \param _rhs
		The second matrix.

	  \return
	    The result of both matrices added.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::Matrix3Add2(const Matrix3x3& _lhs, const Matrix3x3& _rhs) {
		Matrix3x3 result;
		result.matrix.m00 = _lhs.matrix.m00 + _rhs.matrix.m00;
		result.matrix.m01 = _lhs.matrix.m01 + _rhs.matrix.m01;
		result.matrix.m02 = _lhs.matrix.m02 + _rhs.matrix.m02;
		result.matrix.m10 = _lhs.matrix.m10 + _rhs.matrix.m10;
		result.matrix.m11 = _lhs.matrix.m11 + _rhs.matrix.m11;
		result.matrix.m12 = _lhs.matrix.m12 + _rhs.matrix.m12;
		result.matrix.m20 = _lhs.matrix.m20 + _rhs.matrix.m20;
		result.matrix.m21 = _lhs.matrix.m21 + _rhs.matrix.m21;
		result.matrix.m22 = _lhs.matrix.m22 + _rhs.matrix.m22;

		result.m[0] = result.matrix.m00;
		result.m[1] = result.matrix.m01;
		result.m[2] = result.matrix.m02;
		result.m[3] = result.matrix.m10;
		result.m[4] = result.matrix.m11;
		result.m[5] = result.matrix.m12;
		result.m[6] = result.matrix.m20;
		result.m[7] = result.matrix.m21;
		result.m[8] = result.matrix.m22;
		return result;
	}

	/*!*****************************************************************************
	  \brief
		Performs subtraction calculation to a matrix

	  \param _rhs
		The other matrix.
	*******************************************************************************/
	void Matrix3x3::Matrix3Sub(const Matrix3x3& _rhs) {
		matrix.m00 -= _rhs.matrix.m00;
		matrix.m01 -= _rhs.matrix.m01;
		matrix.m02 -= _rhs.matrix.m02;
		matrix.m10 -= _rhs.matrix.m10;
		matrix.m11 -= _rhs.matrix.m11;
		matrix.m12 -= _rhs.matrix.m12;
		matrix.m20 -= _rhs.matrix.m20;
		matrix.m21 -= _rhs.matrix.m21;
		matrix.m22 -= _rhs.matrix.m22;

		m[0] = matrix.m00;
		m[1] = matrix.m01;
		m[2] = matrix.m02;
		m[3] = matrix.m10;
		m[4] = matrix.m11;
		m[5] = matrix.m12;
		m[6] = matrix.m20;
		m[7] = matrix.m21;
		m[8] = matrix.m22;
	}

	/*!*****************************************************************************
	  \brief
		Performs subtraction calculation to 2 matrices

	  \param _lhs
		The first matrix.

	  \param _rhs
		The second matrix.

	  \return
		The result of both matrices subtracted.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::Matrix3Sub2(const Matrix3x3& _lhs, const Matrix3x3& _rhs) {
		Matrix3x3 result;
		result.matrix.m00 = _lhs.matrix.m00 - _rhs.matrix.m00;
		result.matrix.m01 = _lhs.matrix.m01 - _rhs.matrix.m01;
		result.matrix.m02 = _lhs.matrix.m02 - _rhs.matrix.m02;
		result.matrix.m10 = _lhs.matrix.m10 - _rhs.matrix.m10;
		result.matrix.m11 = _lhs.matrix.m11 - _rhs.matrix.m11;
		result.matrix.m12 = _lhs.matrix.m12 - _rhs.matrix.m12;
		result.matrix.m20 = _lhs.matrix.m20 - _rhs.matrix.m20;
		result.matrix.m21 = _lhs.matrix.m21 - _rhs.matrix.m21;
		result.matrix.m22 = _lhs.matrix.m22 - _rhs.matrix.m22;

		result.m[0] = result.matrix.m00;
		result.m[1] = result.matrix.m01;
		result.m[2] = result.matrix.m02;
		result.m[3] = result.matrix.m10;
		result.m[4] = result.matrix.m11;
		result.m[5] = result.matrix.m12;
		result.m[6] = result.matrix.m20;
		result.m[7] = result.matrix.m21;
		result.m[8] = result.matrix.m22;

		return result;
	}

	/*!*****************************************************************************
	  \brief
		Performs multiplication calculation to a matrix

	  \param _scale
		The scalar.
	*******************************************************************************/
	void Matrix3x3::Matrix3Mul(const float _scale) {
		matrix.m00 *= _scale;
		matrix.m01 *= _scale;
		matrix.m02 *= _scale;
		matrix.m10 *= _scale;
		matrix.m11 *= _scale;
		matrix.m12 *= _scale;
		matrix.m20 *= _scale;
		matrix.m21 *= _scale;
		matrix.m22 *= _scale;

		m[0] = matrix.m00;
		m[1] = matrix.m01;
		m[2] = matrix.m02;
		m[3] = matrix.m10;
		m[4] = matrix.m11;
		m[5] = matrix.m12;
		m[6] = matrix.m20;
		m[7] = matrix.m21;
		m[8] = matrix.m22;
	}

	/*!*****************************************************************************
	  \brief
		Performs multiplication calculation to 2 matrices

	  \param _lhs
		The matrix itself.

	  \param _scale
		The scalar.

	  \return
		The result of multiplying the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::Matrix3Mul2(const Matrix3x3& _lhs, const float _scale) {
		Matrix3x3 result;
		result.matrix.m00 = _lhs.matrix.m00 * _scale;
		result.matrix.m01 = _lhs.matrix.m01 * _scale;
		result.matrix.m02 = _lhs.matrix.m02 * _scale;
		result.matrix.m10 = _lhs.matrix.m10 * _scale;
		result.matrix.m11 = _lhs.matrix.m11 * _scale;
		result.matrix.m12 = _lhs.matrix.m12 * _scale;
		result.matrix.m20 = _lhs.matrix.m20 * _scale;
		result.matrix.m21 = _lhs.matrix.m21 * _scale;
		result.matrix.m22 = _lhs.matrix.m22 * _scale;

		result.m[0] = result.matrix.m00;
		result.m[1] = result.matrix.m01;
		result.m[2] = result.matrix.m02;
		result.m[3] = result.matrix.m10;
		result.m[4] = result.matrix.m11;
		result.m[5] = result.matrix.m12;
		result.m[6] = result.matrix.m20;
		result.m[7] = result.matrix.m21;
		result.m[8] = result.matrix.m22;

		return result;
	}

	/*!*****************************************************************************
	  \brief
		Performs division calculation to a matrix

	  \param _scale
		The scalar.
	*******************************************************************************/
	void Matrix3x3::Matrix3Div(const float _scale) {
		if (_scale == 0) {
			matrix.m00 = 0;
			matrix.m01 = 0;
			matrix.m02 = 0;
			matrix.m10 = 0;
			matrix.m11 = 0;
			matrix.m12 = 0;
			matrix.m20 = 0;
			matrix.m21 = 0;
			matrix.m22 = 0;
		}
		else {
			matrix.m00 /= _scale;
			matrix.m01 /= _scale;
			matrix.m02 /= _scale;
			matrix.m10 /= _scale;
			matrix.m11 /= _scale;
			matrix.m12 /= _scale;
			matrix.m20 /= _scale;
			matrix.m21 /= _scale;
			matrix.m22 /= _scale;
		}

		m[0] = matrix.m00;
		m[1] = matrix.m01;
		m[2] = matrix.m02;
		m[3] = matrix.m10;
		m[4] = matrix.m11;
		m[5] = matrix.m12;
		m[6] = matrix.m20;
		m[7] = matrix.m21;
		m[8] = matrix.m22;
	}

	/*!*****************************************************************************
	  \brief
		Performs division calculation to 2 matrices

	  \param _lhs
		The matrix itself.

	  \param _scale
		The scalar.

	  \return
		The result of dividing the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::Matrix3Div2(const Matrix3x3& _lhs, const float _scale) {
		Matrix3x3 result;
		if (_scale == 0) {
			result.matrix.m00 = 0.f;
			result.matrix.m01 = 0.f;
			result.matrix.m02 = 0.f;
			result.matrix.m10 = 0.f;
			result.matrix.m11 = 0.f;
			result.matrix.m12 = 0.f;
			result.matrix.m20 = 0.f;
			result.matrix.m21 = 0.f;
			result.matrix.m22 = 0.f;
		}
		else {
			result.matrix.m00 = _lhs.matrix.m00 / _scale;
			result.matrix.m01 = _lhs.matrix.m01 / _scale;
			result.matrix.m02 = _lhs.matrix.m02 / _scale;
			result.matrix.m10 = _lhs.matrix.m10 / _scale;
			result.matrix.m11 = _lhs.matrix.m11 / _scale;
			result.matrix.m12 = _lhs.matrix.m12 / _scale;
			result.matrix.m20 = _lhs.matrix.m20 / _scale;
			result.matrix.m21 = _lhs.matrix.m21 / _scale;
			result.matrix.m22 = _lhs.matrix.m22 / _scale;
		}

		m[0] = matrix.m00;
		m[1] = matrix.m01;
		m[2] = matrix.m02;
		m[3] = matrix.m10;
		m[4] = matrix.m11;
		m[5] = matrix.m12;
		m[6] = matrix.m20;
		m[7] = matrix.m21;
		m[8] = matrix.m22;

		return result;
	}

	/*!*****************************************************************************
	  \brief
		Returns the elements of a matrix

	  \return
		The elements of a matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::getMatrixElements() {
		Matrix3x3 mat(matrix.m00, matrix.m01, matrix.m02, matrix.m10, matrix.m11, matrix.m12, matrix.m20, matrix.m21, matrix.m22);
		return mat;
	}

	/*!*****************************************************************************
	  \brief
		Retrieves a matrix

	  \return
		A matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::getMatrix() {
		return m;
	}

	/*!*****************************************************************************
	  \brief
		Sets a matrix to desired values.

	  \return
		The set matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3x3::setMatrix(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22) {
		Matrix3x3 mat;
		mat.matrix.m00 = _00;
		mat.matrix.m01 = _01;
		mat.matrix.m02 = _02;
		mat.matrix.m10 = _10;
		mat.matrix.m11 = _11;
		mat.matrix.m12 = _12;
		mat.matrix.m20 = _20;
		mat.matrix.m21 = _21;
		mat.matrix.m22 = _22;

		mat.m[0] = mat.matrix.m00;
		mat.m[1] = mat.matrix.m01;
		mat.m[2] = mat.matrix.m02;
		mat.m[3] = mat.matrix.m10;
		mat.m[4] = mat.matrix.m11;
		mat.m[5] = mat.matrix.m12;
		mat.m[6] = mat.matrix.m20;
		mat.m[7] = mat.matrix.m21;
		mat.m[8] = mat.matrix.m22;

		return mat;
	}

	/*!*****************************************************************************
	  \brief
		Returns the elements in the matrix.

	  \return
		The elements in the matrix.
	*******************************************************************************/
	const float* Matrix3x3::data() const { return m; }

	/*!*****************************************************************************
	  \brief
		Returns the elements in the matrix.

	  \return
		The elements in the matrix.
	*******************************************************************************/
	float* Matrix3x3::data() { return m; }

	/*!*****************************************************************************
	  \brief
		Operator overload for * to multiply 2 matrices.

	  \param _lhs
		The first matrix.

	  \param _rhs
		The second matrix.

	  \return
		The result of multiplying the matrices.
	*******************************************************************************/
	Matrix3x3 operator*(const Matrix3x3& _lhs, const Matrix3x3& _rhs)
	{
		Matrix3x3 result;
		result.matrix.m00 = _lhs.matrix.m00 * _rhs.matrix.m00 + _lhs.matrix.m01 * _rhs.matrix.m10 + _lhs.matrix.m02 * _rhs.matrix.m20;
		result.matrix.m01 = _lhs.matrix.m00 * _rhs.matrix.m01 + _lhs.matrix.m01 * _rhs.matrix.m11 + _lhs.matrix.m02 * _rhs.matrix.m21;
		result.matrix.m02 = _lhs.matrix.m00 * _rhs.matrix.m02 + _lhs.matrix.m01 * _rhs.matrix.m12 + _lhs.matrix.m02 * _rhs.matrix.m22;
		result.matrix.m10 = _lhs.matrix.m10 * _rhs.matrix.m00 + _lhs.matrix.m11 * _rhs.matrix.m10 + _lhs.matrix.m12 * _rhs.matrix.m20;
		result.matrix.m11 = _lhs.matrix.m10 * _rhs.matrix.m01 + _lhs.matrix.m11 * _rhs.matrix.m11 + _lhs.matrix.m12 * _rhs.matrix.m21;
		result.matrix.m12 = _lhs.matrix.m10 * _rhs.matrix.m02 + _lhs.matrix.m11 * _rhs.matrix.m12 + _lhs.matrix.m12 * _rhs.matrix.m22;
		result.matrix.m20 = _lhs.matrix.m20 * _rhs.matrix.m00 + _lhs.matrix.m21 * _rhs.matrix.m10 + _lhs.matrix.m22 * _rhs.matrix.m20;
		result.matrix.m21 = _lhs.matrix.m20 * _rhs.matrix.m01 + _lhs.matrix.m21 * _rhs.matrix.m11 + _lhs.matrix.m22 * _rhs.matrix.m21;
		result.matrix.m22 = _lhs.matrix.m20 * _rhs.matrix.m02 + _lhs.matrix.m21 * _rhs.matrix.m12 + _lhs.matrix.m22 * _rhs.matrix.m22;

		return result;
	}

	/*!*****************************************************************************
	  \brief
		Performs scaling calculation to 2 matrices

	  \param _data
		The matrix itself.

	  \param _x
		The x scalar.

	  \param _y
		The y scalar.

	  \return
		The result of scaling the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3Scaling(Matrix3x3& _data, float _x, float _y)
	{
		Matrix3x3 result{_data};
		result.Matrix3Scale(_x, _y);
		return result;
	}

	/*!*****************************************************************************
	  \brief
		Performs radian rotation calculation to 2 matrices.

	  \param 
		The matrix itself.

	  \param _angle
		The angle of rotation.

	  \return
		The result of rotating the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3Rotation(Matrix3x3&, float _angle)
	{
		Matrix3x3 result{};
		result.Matrix3RotRad(_angle);
		return result;
	}

	/*!*****************************************************************************
	  \brief
		Concatenates 2 matrices.

	  \param
		The matrix itself.

	  \param _angle
		The angle of rotation.

	  \return
		The result of rotating the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3Concat(Matrix3x3 const& _lhs, Matrix3x3 const& _rhs)
	{
		Matrix3x3 result{_lhs * _rhs};
		return result;
	}

	/*!*****************************************************************************
	  \brief
		Translates a matrix.

	  \param
		The matrix itself.

	  \param _x
		The x translation.

	  \param _y
		The y translation.

	  \return
		The result of translating the matrix.
	*******************************************************************************/
	Matrix3x3 Matrix3Translation(Matrix3x3&, float _x, float _y)
	{
		Matrix3x3 result{};
		result.Matrix3Translate(_x, _y);
		return result;
	}
}