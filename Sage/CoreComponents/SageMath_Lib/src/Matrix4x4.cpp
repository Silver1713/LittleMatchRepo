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


const float PI = 3.14159265358979323846f;


namespace ToastBox {
	Matrix4::Matrix4(const float* arr) {
		std::copy(arr, arr + 16, matrixArray);
	}

	Matrix4::Matrix4(float AA, float BB, float CC, float DD,
					 float EE, float FF, float GG, float HH,
					 float II, float JJ, float KK, float LL,
					 float MM, float NN, float OO, float PP)
		: Components{ AA, BB, CC, DD, EE, FF, GG, HH, II, JJ, KK, LL, MM, NN, OO, PP } {}

	Matrix4 Matrix4::operator~() const {
		Matrix4 result = *this;
		result.Matrix4_Transpose(result);
		return result;
	}

	Matrix4 Matrix4::operator=(const Matrix4& rhs) {
		if (this != &rhs) {
			std::copy(rhs.matrixArray, rhs.matrixArray + 16, matrixArray);
		}
		return *this;
	}

	void Matrix4::Matrix4_Identity(Matrix4& result) {
		static const float identity[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		std::copy(identity, identity + 16, result.matrixArray);
	}

	void Matrix4::Matrix4_Translate(float x, float y, float z) {
		Components.d += x;
		Components.h += y;
		Components.l += z;
	}

	void Matrix4::Matrix4_Scale(float x, float y, float z) {
		Components.a *= x;
		Components.f *= y;
		Components.k *= z;
	}


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

	void Matrix4::Matrix4AxisXRotDeg(float angle) {
		float radAngle = (angle / 360) * 2 * PI;

		Matrix4 id(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, (float)cos(radAngle), (float)sin(radAngle), 0.0f,
			0.0f, (float)-sin(radAngle), (float)cos(radAngle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 16; i++) {
			matrixArray[i] = id.matrixArray[i];
		}

		a = matrixArray[0];
		b = matrixArray[1];
		c = matrixArray[2];
		d = matrixArray[3];
		e = matrixArray[4];
		f = matrixArray[5];
		g = matrixArray[6];
		h = matrixArray[7];
		i = matrixArray[8];
		j = matrixArray[9];
		k = matrixArray[10];
		l = matrixArray[11];
		m = matrixArray[12];
		n = matrixArray[13];
		o = matrixArray[14];
		p = matrixArray[15];
	}

	void Matrix4::Matrix4AxisYRotDeg(float angle) {
		float radAngle = (angle / 360) * 2 * PI;
		Matrix4 id((float)cos(radAngle), 0.0f, (float)-sin(radAngle), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			(float)sin(radAngle), 0.0f, (float)cos(radAngle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 16; i++) {
			matrixArray[i] = id.matrixArray[i];
		}

		a = matrixArray[0];
		b = matrixArray[1];
		c = matrixArray[2];
		d = matrixArray[3];
		e = matrixArray[4];
		f = matrixArray[5];
		g = matrixArray[6];
		h = matrixArray[7];
		i = matrixArray[8];
		j = matrixArray[9];
		k = matrixArray[10];
		l = matrixArray[11];
		m = matrixArray[12];
		n = matrixArray[13];
		o = matrixArray[14];
		p = matrixArray[15];
	}

	void Matrix4::Matrix4AxisZRotDeg(float angle) {
		float radAngle = (angle / 360) * 2 * PI;
		Matrix4 id((float)cos(radAngle), (float)-sin(radAngle), 0.0f, 0.0f,
			(float)sin(radAngle), (float)cos(radAngle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		for (int i{ 0 }; i < 16; i++) {
			matrixArray[i] = id.matrixArray[i];
		}

		a = matrixArray[0];
		b = matrixArray[1];
		c = matrixArray[2];
		d = matrixArray[3];
		e = matrixArray[4];
		f = matrixArray[5];
		g = matrixArray[6];
		h = matrixArray[7];
		i = matrixArray[8];
		j = matrixArray[9];
		k = matrixArray[10];
		l = matrixArray[11];
		m = matrixArray[12];
		n = matrixArray[13];
		o = matrixArray[14];
		p = matrixArray[15];
	}

	void Matrix4::Matrix4_Transpose(const Matrix4& mtx) {
		std::swap(Components.b, Components.e);
		std::swap(Components.c, Components.i);
		std::swap(Components.d, Components.m);
		std::swap(Components.g, Components.j);
		std::swap(Components.h, Components.n);
		std::swap(Components.l, Components.o);
	}

	void Matrix4::Matrix4_Add(const Matrix4& rhs) {
		for (int i = 0; i < 16; ++i) {
			matrixArray[i] += rhs.matrixArray[i];
		}
	}

	Matrix4 Matrix4::Matrix4_Add2(const Matrix4& lhs, const Matrix4& rhs) {
		Matrix4 result;
		for (int i = 0; i < 16; ++i) {
			result.matrixArray[i] = lhs.matrixArray[i] + rhs.matrixArray[i];
		}
		return result;
	}

	void Matrix4::Matrix4_Sub(const Matrix4& rhs) {
		for (int i = 0; i < 16; ++i) {
			matrixArray[i] -= rhs.matrixArray[i];
		}
	}

	Matrix4 Matrix4::Matrix4_Sub2(const Matrix4& lhs, const Matrix4& rhs) {
		Matrix4 result;
		for (int i = 0; i < 16; ++i) {
			result.matrixArray[i] = lhs.matrixArray[i] - rhs.matrixArray[i];
		}
		return result;
	}

	void Matrix4::Matrix4_Mul(const float scale) {
		for (int i = 0; i < 16; ++i) {
			matrixArray[i] *= scale;
		}
	}

	Matrix4 Matrix4::Matrix4_Mul2(const Matrix4& rhs, const float scale) {
		Matrix4 result = rhs;
		result.Matrix4_Mul(scale);
		return result;
	}

	void Matrix4::Matrix4_Div(const float scale) {
		if (scale != 0) {
			float invScale = 1.0f / scale;
			for (int i = 0; i < 16; ++i) {
				matrixArray[i] *= invScale;
			}
		}
	}

	Matrix4 Matrix4::Matrix4_Div2(const Matrix4& rhs, const float scale) {
		Matrix4 result = rhs;
		result.Matrix4_Div(scale);
		return result;
	}

	Matrix4 Matrix4::Get_Matrix_Elements() const {
		return *this;
	}

	Matrix4 Matrix4::Get_Matrix() const {
		return *this;
	}

	Matrix4 Matrix4::Set_Matrix(float a11, float a12, float a13, float a14,
								float a21, float a22, float a23, float a24,
								float a31, float a32, float a33, float a34,
								float a41, float a42, float a43, float a44) {
		Components = { a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44 };
		return *this;
	}

	float* Matrix4::Data() {
		return matrixArray;
	}

	const float* Matrix4::Data() const {
		return matrixArray;
	}
}