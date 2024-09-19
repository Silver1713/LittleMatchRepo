/******************************************************************************
File name	 : Matrix3x3.h
Project		 : Memory's Flame
Author       : Edwin Lee
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 11/09/2024
Brief		 : Matrix3x3 class and class operation declaration
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/
#pragma once
#include "Vector2.h"

namespace ToastBox {
	class Matrix3x3 {
	private:
		struct {
			float m00{}, m01{}, m02{};
			float m10{}, m11{}, m12{};
			float m20{}, m21{}, m22{};
		};

		float m[9]{};
	public:
		Matrix3x3() :m00{ 0 }, m01{ 0 }, m02{ 0 }, m10{ 0 }, m11{ 0 }, m12{ 0 }, m20{ 0 }, m21{ 0 }, m22{ 0 }, m{ 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f } {};

		Matrix3x3(const float* arr);


		Matrix3x3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
			:m00{ _00 }, m01{ _01 }, m02{ _02 }, m10{ _10 }, m11{ _11 }, m12{ _12 }, m20{ _20 }, m21{ _21 }, m22{ _22 }, m{ _00,_01,_02,_10,_11,_12,_20,_21,_22 } {}

		Matrix3x3 operator=(const Matrix3x3& rhs);

		//Identity matrix
		void Matrix3Identity(Matrix3x3& pResult);

		//Translate matrix
		void Matrix3Translate(float x, float y);

		//Scale matrix
		void Matrix3Scale(float x, float y);

		//Rotate (radian) matrix
		void Matrix3RotRad(float angle);

		//Rotate (degree) matrix
		void Matrix3RotDeg(float angle);

		//Transpose matrix
		void Matrix3Transpose(const Matrix3x3& pMtx);

		//Inverse matrix
		void Matrix3SetInverse(const Matrix3x3& mtx);
		Matrix3x3 inverse() const;
		void invert();

		//Matrix Addition
		void Matrix3Add(const Matrix3x3& rhs);
		Matrix3x3 Matrix3Add2(const Matrix3x3& lhs, const Matrix3x3& rhs);

		//Matrix Subtraction
		void Matrix3Sub(const Matrix3x3& rhs);
		Matrix3x3 Matrix3Sub2(const Matrix3x3& lhs, const Matrix3x3& rhs);

		//Matrix Multiplication scale
		void Matrix3Mul(const float scale);
		Matrix3x3 Matrix3Mul2(const Matrix3x3& lhs, const float scale);

		//Matrix Division scale
		void Matrix3Div(const float scale);
		Matrix3x3 Matrix3Div2(const Matrix3x3& lhs, const float scale);

		//Get elements of matrix
		Matrix3x3 getMatrixElements();

		//Get matrix
		Matrix3x3 getMatrix();

		//Mutate matrix
		Matrix3x3 setMatrix(float, float, float, float, float, float, float, float, float);
	};
}
