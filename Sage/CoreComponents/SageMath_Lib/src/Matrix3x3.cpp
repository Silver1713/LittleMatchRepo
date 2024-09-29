/******************************************************************************
File name	 : Matrix3x3.cpp
Project		 : Memory's Flame
Author       : Edwin Lee
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 11/09/2024
Brief		 : Matrix3x3 class and class operation definition
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/


#include "Matrix3x3.h"
#include <cmath>

constexpr float EPSILON = 0.0001f;
constexpr float PI = 3.14159265358f;

namespace ToastBox {
	//Constructor
	Matrix3x3::Matrix3x3(const float* arr) {
		for (int i{ 0 }; i < 9; i++) {
			m[i] = *arr++;
		}

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];
	}
	/*
	Function: operator=()
	Param: Matrix3x3 rhs
	Desc: Assign m array with rhs*/
	Matrix3x3 Matrix3x3::operator=(const Matrix3x3& rhs) {
		for (int i{ 0 }; i < 9; i++) {
			m[i] = rhs.m[i];
		}

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];

		return *this;
	}

	/*
	Function: Matrix3Identity()
	Param: Matrix3x3 pResult
	Desc: Return Identity Matrix m*/
	void Matrix3x3::Matrix3Identity(Matrix3x3& pResult) {
		Matrix3x3 id(1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.f,
			0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 9; i++) {
			m[i] = id.m[i];
		}

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];
	}

	/*
	Function: Matrix3Translate()
	Param: x,y
	Desc: Perfrom translation transformation */
	void Matrix3x3::Matrix3Translate(float x, float y) {
		Matrix3x3 id(1.0f, 0.0f, x,
			0.0f, 1.0f, y,
			0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 9; i++) {
			m[i] = id.m[i];
		}

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];
	}

	/*
	Function: Matrix3Scale()
	Param: x,y
	Desc: Perfrom scaling transformation */
	void Matrix3x3::Matrix3Scale(float x, float y) {
		Matrix3x3 id(1.0f * x, 0.0f, 0.0f,
			0.0f, 1.0f * y, 0.0f,
			0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 9; i++) {
			m[i] = id.m[i];
		}

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];
	}

	/*
	Function: Matrix3RotRad()
	Param: angle (in radian)
	Desc: Perfrom rotation transformation */
	void Matrix3x3::Matrix3RotRad(float angle) {
		Matrix3x3 id((float)cos(angle), (float)-sin(angle), 0.0f,
			(float)sin(angle), (float)cos(angle), 0.0f,
			0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 9; i++) {
			m[i] = id.m[i];
		}

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];
	}

	/*
	Function: Matrix3RotDeg()
	Param: angle (in degree)
	Desc: Perfrom rotation transformation */
	void Matrix3x3::Matrix3RotDeg(float angle) {
		float radAngle = (angle * PI / 180);

		Matrix3x3 id((float)cos(radAngle), (float)-sin(radAngle), 0.0f,
			(float)sin(radAngle), (float)cos(radAngle), 0.0f,
			0.0f, 0.0f, 1.0f);


		for (int i = 0; i < 9; i++)
		{
			// insert id matrix into result matrix
			m[i] = id.m[i];
		}

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];
	}

	/*
	Function: Matrix3Transpose()
	Param: Matrix3x3 pMtx
	Desc: Perfrom transpose a matrix*/
	void Matrix3x3::Matrix3Transpose(const Matrix3x3& pMtx) {
		//row becomes columns
		m[0] = pMtx.m[0];
		m[3] = pMtx.m[1];
		m[6] = pMtx.m[2];
		m[1] = pMtx.m[3];
		m[4] = pMtx.m[4];
		m[7] = pMtx.m[5];
		m[2] = pMtx.m[6];
		m[5] = pMtx.m[7];
		m[8] = pMtx.m[8];

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];
	}

	/*
	Function: Matrix3Inverse()
	Param: Matrix3x3 pmtx
	Desc: Inverse a matrix */
	void Matrix3x3::Matrix3SetInverse(const Matrix3x3& mtx) {
		float t4 = mtx.m00 * mtx.m11;
		float t6 = mtx.m00 * mtx.m12;
		float t8 = mtx.m01 * mtx.m10;
		float t10 = mtx.m02 * mtx.m10;
		float t12 = mtx.m01 * mtx.m20;
		float t14 = mtx.m02 * mtx.m20;

		//calculate det
		float t16 = (t4 * mtx.m22 - t6 * mtx.m21 - t8 * mtx.m22 +
			t10 * mtx.m21 + t12 * mtx.m12 - t14 * mtx.m11);

		//Check if det is non-zero
		if (t16 == (float)0.0f) {
			return;
		}
		float t17 = 1 / t16;

		m00 = (mtx.m11 * mtx.m22 - mtx.m12 * mtx.m21) * t17;
		m01 = -(mtx.m01 * mtx.m22 - mtx.m02 * mtx.m21) * t17;
		m02 = (mtx.m01 * mtx.m12 - mtx.m02 * mtx.m11) * t17;
		m10 = -(mtx.m10 * mtx.m22 - mtx.m12 * mtx.m20) * t17;
		m11 = (mtx.m00 * mtx.m22 - t14) * t17;
		m12 = -(t6 - t10) * t17;
		m20 = (mtx.m10 * mtx.m21 - mtx.m11 * mtx.m20) * t17;
		m21 = -(mtx.m00 * mtx.m21 - t12) * t17;
		m22 = (t4 - t8) * t17;

		m[0] = m00;
		m[1] = m01;
		m[2] = m02;
		m[3] = m10;
		m[4] = m11;
		m[5] = m12;
		m[6] = m20;
		m[7] = m21;
		m[8] = m22;

	}

	/*
	Function: inverse()
	Param: Matrix3x3 pmtx
	Desc: Inverse a matrix */
	Matrix3x3 Matrix3x3::inverse() const {
		Matrix3x3 result;
		result.Matrix3SetInverse(*this);
		return result;
	}
	/*
	Function: invert()
	Param: Matrix3x3 pmtx
	Desc: Inverse a matrix */
	void Matrix3x3::invert() {
		return Matrix3SetInverse(*this);
	}

	/*
	Function: Matrix3Add()
	Param: Matrix3x3 rhs
	Desc: Add matrix*/
	void Matrix3x3::Matrix3Add(const Matrix3x3& rhs) {
		m00 += rhs.m00;
		m01 += rhs.m01;
		m02 += rhs.m02;
		m10 += rhs.m10;
		m11 += rhs.m11;
		m12 += rhs.m12;
		m20 += rhs.m20;
		m21 += rhs.m21;
		m22 += rhs.m22;

		m[0] = m00;
		m[1] = m01;
		m[2] = m02;
		m[3] = m10;
		m[4] = m11;
		m[5] = m12;
		m[6] = m20;
		m[7] = m21;
		m[8] = m22;
	}

	/*
	Function: Matrix3Add2()
	Param: Matrix3x3 lhs, rhs
	Desc: Return a new matrix from lhs + rhs*/
	Matrix3x3 Matrix3x3::Matrix3Add2(const Matrix3x3& lhs, const Matrix3x3& rhs) {
		Matrix3x3 result;
		result.m00 = lhs.m00 + rhs.m00;
		result.m01 = lhs.m01 + rhs.m01;
		result.m02 = lhs.m02 + rhs.m02;
		result.m10 = lhs.m10 + rhs.m10;
		result.m11 = lhs.m11 + rhs.m11;
		result.m12 = lhs.m12 + rhs.m12;
		result.m20 = lhs.m20 + rhs.m20;
		result.m21 = lhs.m21 + rhs.m21;
		result.m22 = lhs.m22 + rhs.m22;

		result.m[0] = result.m00;
		result.m[1] = result.m01;
		result.m[2] = result.m02;
		result.m[3] = result.m10;
		result.m[4] = result.m11;
		result.m[5] = result.m12;
		result.m[6] = result.m20;
		result.m[7] = result.m21;
		result.m[8] = result.m22;
		return result;
	}

	/*
	Function: Matrix3Sub()
	Param: Matrix3x3 rhs
	Desc: Subtract matrix*/
	void Matrix3x3::Matrix3Sub(const Matrix3x3& rhs) {
		m00 -= rhs.m00;
		m01 -= rhs.m01;
		m02 -= rhs.m02;
		m10 -= rhs.m10;
		m11 -= rhs.m11;
		m12 -= rhs.m12;
		m20 -= rhs.m20;
		m21 -= rhs.m21;
		m22 -= rhs.m22;

		m[0] = m00;
		m[1] = m01;
		m[2] = m02;
		m[3] = m10;
		m[4] = m11;
		m[5] = m12;
		m[6] = m20;
		m[7] = m21;
		m[8] = m22;
	}

	/*
	Function: Matrix3Sub2()
	Param: Matrix3x3 lhs, rhs
	Desc: Return a new matrix from lhs + rhs*/
	Matrix3x3 Matrix3x3::Matrix3Sub2(const Matrix3x3& lhs, const Matrix3x3& rhs) {
		Matrix3x3 result;
		result.m00 = lhs.m00 - rhs.m00;
		result.m01 = lhs.m01 - rhs.m01;
		result.m02 = lhs.m02 - rhs.m02;
		result.m10 = lhs.m10 - rhs.m10;
		result.m11 = lhs.m11 - rhs.m11;
		result.m12 = lhs.m12 - rhs.m12;
		result.m20 = lhs.m20 - rhs.m20;
		result.m21 = lhs.m21 - rhs.m21;
		result.m22 = lhs.m22 - rhs.m22;

		result.m[0] = result.m00;
		result.m[1] = result.m01;
		result.m[2] = result.m02;
		result.m[3] = result.m10;
		result.m[4] = result.m11;
		result.m[5] = result.m12;
		result.m[6] = result.m20;
		result.m[7] = result.m21;
		result.m[8] = result.m22;

		return result;
	}

	/*
	Function: Matrix3Mul()
	Param: scale
	Desc: Multiply matrix by scale*/
	void Matrix3x3::Matrix3Mul(const float scale) {
		m00 *= scale;
		m01 *= scale;
		m02 *= scale;
		m10 *= scale;
		m11 *= scale;
		m12 *= scale;
		m20 *= scale;
		m21 *= scale;
		m22 *= scale;

		m[0] = m00;
		m[1] = m01;
		m[2] = m02;
		m[3] = m10;
		m[4] = m11;
		m[5] = m12;
		m[6] = m20;
		m[7] = m21;
		m[8] = m22;
	}

	Matrix3x3 Matrix3x3::Matrix3Mul2(const Matrix3x3& lhs, const float scale) {
		Matrix3x3 result;
		result.m00 = lhs.m00 * scale;
		result.m01 = lhs.m01 * scale;
		result.m02 = lhs.m02 * scale;
		result.m10 = lhs.m10 * scale;
		result.m11 = lhs.m11 * scale;
		result.m12 = lhs.m12 * scale;
		result.m20 = lhs.m20 * scale;
		result.m21 = lhs.m21 * scale;
		result.m22 = lhs.m22 * scale;

		result.m[0] = result.m00;
		result.m[1] = result.m01;
		result.m[2] = result.m02;
		result.m[3] = result.m10;
		result.m[4] = result.m11;
		result.m[5] = result.m12;
		result.m[6] = result.m20;
		result.m[7] = result.m21;
		result.m[8] = result.m22;

		return result;
	}

	/*
	Function: Matrix3Div()
	Param: scale
	Desc: Divide matrix by scale*/
	void Matrix3x3::Matrix3Div(const float scale) {
		if (scale == 0) {
			m00 = 0;
			m01 = 0;
			m02 = 0;
			m10 = 0;
			m11 = 0;
			m12 = 0;
			m20 = 0;
			m21 = 0;
			m22 = 0;
		}
		else {
			m00 /= scale;
			m01 /= scale;
			m02 /= scale;
			m10 /= scale;
			m11 /= scale;
			m12 /= scale;
			m20 /= scale;
			m21 /= scale;
			m22 /= scale;
		}

		m[0] = m00;
		m[1] = m01;
		m[2] = m02;
		m[3] = m10;
		m[4] = m11;
		m[5] = m12;
		m[6] = m20;
		m[7] = m21;
		m[8] = m22;
	}

	Matrix3x3 Matrix3x3::Matrix3Div2(const Matrix3x3& lhs, const float scale) {
		Matrix3x3 result;
		if (scale == 0) {
			result.m00 = 0.f;
			result.m01 = 0.f;
			result.m02 = 0.f;
			result.m10 = 0.f;
			result.m11 = 0.f;
			result.m12 = 0.f;
			result.m20 = 0.f;
			result.m21 = 0.f;
			result.m22 = 0.f;
		}
		else {
			result.m00 = lhs.m00 / scale;
			result.m01 = lhs.m01 / scale;
			result.m02 = lhs.m02 / scale;
			result.m10 = lhs.m10 / scale;
			result.m11 = lhs.m11 / scale;
			result.m12 = lhs.m12 / scale;
			result.m20 = lhs.m20 / scale;
			result.m21 = lhs.m21 / scale;
			result.m22 = lhs.m22 / scale;
		}

		m[0] = m00;
		m[1] = m01;
		m[2] = m02;
		m[3] = m10;
		m[4] = m11;
		m[5] = m12;
		m[6] = m20;
		m[7] = m21;
		m[8] = m22;

		return result;
	}

	/*
	Function: getMatrixElements()()
	Desc: return elements of matrix*/
	Matrix3x3 Matrix3x3::getMatrixElements() {
		Matrix3x3 mat(m00, m01, m02, m10, m11, m12, m20, m21, m22);
		return mat;
	}

	/*
	Function: getMatrix()()
	Desc: return matrix*/
	Matrix3x3 Matrix3x3::getMatrix() {
		return m;
	}

	/*
	Function: setMatrix()()
	Param: floats _00,_01,_02,_10,_11,_12,_20,_21,_22
	Desc: set matrix*/
	Matrix3x3 Matrix3x3::setMatrix(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22) {
		Matrix3x3 mat;
		mat.m00 = _00;
		mat.m01 = _01;
		mat.m02 = _02;
		mat.m10 = _10;
		mat.m11 = _11;
		mat.m12 = _12;
		mat.m20 = _20;
		mat.m21 = _21;
		mat.m22 = _22;

		mat.m[0] = mat.m00;
		mat.m[1] = mat.m01;
		mat.m[2] = mat.m02;
		mat.m[3] = mat.m10;
		mat.m[4] = mat.m11;
		mat.m[5] = mat.m12;
		mat.m[6] = mat.m20;
		mat.m[7] = mat.m21;
		mat.m[8] = mat.m22;

		return mat;
	}
	
	Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{

		
		Matrix3x3 result;
		result.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20;
		result.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21;
		result.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22;
		result.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20;
		result.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21;
		result.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22;
		result.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20;
		result.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21;
		result.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22;

		

		return result;
	}
	Matrix3x3 Matrix3Scaling(Matrix3x3& data, float x, float y)
	{
		Matrix3x3 result{data};
		result.Matrix3Scale(x, y);
		return result;
	}


	Matrix3x3 Matrix3Rotation(Matrix3x3&, float angle)
	{
		Matrix3x3 result{};
		result.Matrix3RotRad(angle);
		return result;
	}

	Matrix3x3 Matrix3Concat(Matrix3x3 const& lhs, Matrix3x3 const& rhs)
	{
		Matrix3x3 result{lhs * rhs};
		
		return result;
	}

	Matrix3x3 Matrix3Translation(Matrix3x3&, float x, float y)
	{
		Matrix3x3 result{};
		result.Matrix3Translate(x, y);
		return result;
	}

	
	Matrix3x3 Matrix3x3::operator~()
	{
		Matrix3x3 result{};
		result.Matrix3Transpose(*this);
		return result;
	}





}

