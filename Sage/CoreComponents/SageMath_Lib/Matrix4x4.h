/******************************************************************************
File name	 : Matrix4x4.h
Project		 : Memory's Flame
Author       : Edwin Lee Zirui
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 12/09/2024
Brief		 : Matrix4x4 class and class operation declaration
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/

#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace ToastBox {
	class Matrix4 {
	private:
		struct {
			float a{}, b{}, c{}, d{};
			float e{}, f{}, g{}, h{};
			float i{}, j{}, k{}, l{};
			float m{}, n{}, o{}, p{};
		};

		float matrixArray[16]{};
	public:
		Matrix4() :a{ 0 }, b{ 0 }, c{ 0 }, d{ 0 },
			e{ 0 }, f{ 0 }, g{ 0 }, h{ 0 },
			i{ 0 }, j{ 0 }, k{ 0 }, l{ 0 },
			m{ 0 }, n{ 0 }, o{ 0 }, p{ 0 },
			matrixArray{ a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p } {};

		Matrix4(const float* arr);

		Matrix4(float AA, float BB, float CC, float DD,
			float EE, float FF, float GG, float HH,
			float II, float JJ, float KK, float LL,
			float MM, float NN, float OO, float PP) :
			a{ AA }, b{ BB }, c{ CC }, d{ DD },
			e{ EE }, f{ FF }, g{ GG }, h{ HH },
			i{ II }, j{ JJ }, k{ KK }, l{ LL },
			m{ MM }, n{ NN }, o{ OO }, p{ PP },
			matrixArray{ AA,BB,CC,DD,EE,GG,HH,II,JJ,KK,LL,MM,NN,OO,PP }
		{}

		Matrix4 operator=(const Matrix4& rhs);

		void Matrix4Identity(Matrix4& result);
		void Matrix4Translate(float x, float y, float z);
		void Matrix4Scale(float x, float y, float z);

		void Matrix4AxisXRotRad(float angle);
		void Matrix4AxisYRotRad(float angle);
		void Matrix4AxisZRotRad(float angle);


		void Matrix4AxisXRotDeg(float angle);
		void Matrix4AxisYRotDeg(float angle);
		void Matrix4AxisZRotDeg(float angle);

		void Matrix4Transpose(const Matrix4& mtx);

		//void Matrix4SetInverse(const Matrix4& mtx);
		//Matrix4 inverse() const;
		//void invert();

		void Matrix4Add(const Matrix4& rhs);
		Matrix4 Matrix4Add2(const Matrix4& lhs, const Matrix4& rhs);

		void Matrix4Sub(const Matrix4& rhs);
		Matrix4 Matrix4Sub2(const Matrix4& lhs, const Matrix4& rhs);

		void Matrix4Mul(const float scale);
		Matrix4 Matrix4Mul2(const Matrix4& rhs, const float scale);

		void Matrix4Div(const float scale);
		Matrix4 Matrix4Div2(const Matrix4& rhs, const float scale);

		Matrix4 getMatrixElements();

		Matrix4 getMatrix();

		Matrix4 setMatrix(float, float, float, float,
			float, float, float, float,
			float, float, float, float,
			float, float, float, float);



	};
}