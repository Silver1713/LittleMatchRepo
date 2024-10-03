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
		Matrix4() = default;

		Matrix4(const float* arr);

		Matrix4(float AA, float BB, float CC, float DD,
				float EE, float FF, float GG, float HH,
				float II, float JJ, float KK, float LL,
				float MM, float NN, float OO, float PP);

		Matrix4 operator~() const;
		Matrix4 operator=(const Matrix4& rhs);

		void Matrix4_Identity(Matrix4& result);
		void Matrix4_Translate(float x, float y, float z);
		void Matrix4_Scale(float x, float y, float z);

		void Matrix4AxisXRotRad(float angle);
		void Matrix4AxisYRotRad(float angle);
		void Matrix4AxisZRotRad(float angle);

		void Matrix4AxisXRotDeg(float angle);
		void Matrix4AxisYRotDeg(float angle);
		void Matrix4AxisZRotDeg(float angle);

		void Matrix4_Transpose(const Matrix4& mtx);

		//void Matrix4SetInverse(const Matrix4& mtx);
		//Matrix4 inverse() const;
		//void invert();

		void Matrix4_Add(const Matrix4& rhs);
		Matrix4 Matrix4_Add2(const Matrix4& lhs, const Matrix4& rhs);

		void Matrix4_Sub(const Matrix4& rhs);
		Matrix4 Matrix4_Sub2(const Matrix4& lhs, const Matrix4& rhs);

		void Matrix4_Mul(const float scale);
		Matrix4 Matrix4_Mul2(const Matrix4& rhs, const float scale);

		void Matrix4_Div(const float scale);
		Matrix4 Matrix4_Div2(const Matrix4& rhs, const float scale);

		Matrix4 Get_Matrix_Elements() const;

		Matrix4 Get_Matrix() const;

		Matrix4 Set_Matrix(float, float, float, float,
						   float, float, float, float,
						   float, float, float, float,
						   float, float, float, float);

		float* Data();
		const float* Data() const;

	};
}