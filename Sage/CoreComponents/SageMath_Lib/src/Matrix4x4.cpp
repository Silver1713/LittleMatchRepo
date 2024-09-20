/******************************************************************************
File name	 : Matrix4x4.cpp
Project		 : Memory's Flame
Author       : Edwin Lee Zirui
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 12/09/2024
Brief		 : Matrix4x4 class and class operation definition
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/


#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <cmath>


const float PI = 3.14159265358979323846f;


namespace ToastBox {
	Matrix4::Matrix4(const float* arr) {
		for (int i{ 0 }; i < 16; i++) {
			matrixArray[i] = *arr++;
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

	Matrix4 Matrix4::operator=(const Matrix4& rhs) {
		Matrix4 result;
		for (int i{ 0 }; i < 16; i++) {
			result.matrixArray[i] = rhs.matrixArray[i];
		}

		result.a = result.matrixArray[0];
		result.b = result.matrixArray[1];
		result.c = result.matrixArray[2];
		result.d = result.matrixArray[3];
		result.e = result.matrixArray[4];
		result.f = result.matrixArray[5];
		result.g = result.matrixArray[6];
		result.h = result.matrixArray[7];
		result.i = result.matrixArray[8];
		result.j = result.matrixArray[9];
		result.k = result.matrixArray[10];
		result.l = result.matrixArray[11];
		result.m = result.matrixArray[12];
		result.n = result.matrixArray[13];
		result.o = result.matrixArray[14];
		result.p = result.matrixArray[15];

		return result;
	}

	void Matrix4::Matrix4Identity(Matrix4& result) {
		Matrix4 id(1.0f, 0.f, 0.f, 0.f,
			0.f, 1.0f, 0.f, 0.f,
			0.f, 0.f, 1.0f, 0.f,
			0.f, 0.f, 0.f, 1.0f);

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

	void Matrix4::Matrix4Translate(float x, float y, float z) {
		Matrix4 id(1.0f, 0.f, 0.f, x,
			0.f, 1.0f, 0.f, y,
			0.f, 0.f, 1.0f, z,
			0.f, 0.f, 0.f, 1.0f);

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

	void Matrix4::Matrix4Scale(float x, float y, float z) {
		Matrix4 id(1.0f * x, 0.f, 0.f, 0.f,
			0.f, 1.0f * y, 0.f, 0.f,
			0.f, 0.f, 1.0f * z, 0.f,
			0.f, 0.f, 0.f, 0.f);

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

	void Matrix4::Matrix4AxisXRotRad(float angle) {
		Matrix4 id(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, (float)cos(angle), (float)sin(angle), 0.0f,
			0.0f, (float)-sin(angle), (float)cos(angle), 0.0f,
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

	void Matrix4::Matrix4AxisYRotRad(float angle) {
		Matrix4 id((float)cos(angle), 0.0f, (float)-sin(angle), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			(float)sin(angle), 0.0f, (float)cos(angle), 0.0f,
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

	void Matrix4::Matrix4AxisZRotRad(float angle) {
		Matrix4 id((float)cos(angle), (float)-sin(angle), 0.0f, 0.0f,
			(float)sin(angle), (float)cos(angle), 0.0f, 0.0f,
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

	void Matrix4::Matrix4Transpose(const Matrix4& matrix) {
		Matrix4 id(matrix.a, matrix.e, matrix.i, matrix.m,
			matrix.b, matrix.f, matrix.j, matrix.n,
			matrix.c, matrix.g, matrix.k, matrix.o,
			matrix.d, matrix.h, matrix.i, matrix.p);

		matrixArray[0] = id.a;
		matrixArray[1] = id.e;
		matrixArray[2] = id.i;
		matrixArray[3] = id.m;
		matrixArray[4] = id.b;
		matrixArray[5] = id.f;
		matrixArray[6] = id.j;
		matrixArray[7] = id.n;
		matrixArray[8] = id.c;
		matrixArray[9] = id.g;
		matrixArray[10] = id.k;
		matrixArray[11] = id.o;
		matrixArray[12] = id.d;
		matrixArray[13] = id.h;
		matrixArray[14] = id.i;
		matrixArray[15] = id.p;

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

	void Matrix4::Matrix4Add(const Matrix4& rhs) {
		a += rhs.a;
		b += rhs.b;
		c += rhs.c;
		d += rhs.d;
		e += rhs.e;
		f += rhs.f;
		g += rhs.g;
		h += rhs.h;
		i += rhs.i;
		j += rhs.j;
		k += rhs.k;
		l += rhs.l;
		m += rhs.m;
		n += rhs.n;
		o += rhs.o;
		p += rhs.p;

		matrixArray[0] = a;
		matrixArray[1] = b;
		matrixArray[2] = c;
		matrixArray[3] = d;
		matrixArray[4] = e;
		matrixArray[5] = f;
		matrixArray[6] = g;
		matrixArray[7] = h;
		matrixArray[8] = i;
		matrixArray[9] = j;
		matrixArray[10] = k;
		matrixArray[11] = l;
		matrixArray[12] = m;
		matrixArray[13] = n;
		matrixArray[14] = o;
		matrixArray[15] = p;
	}

	Matrix4 Matrix4::Matrix4Add2(const Matrix4& lhs, const Matrix4& rhs) {
		Matrix4 result(lhs.a + rhs.a,
			lhs.b + rhs.b,
			lhs.c + rhs.c,
			lhs.d + rhs.d,
			lhs.e + rhs.e,
			lhs.f + rhs.f,
			lhs.g + rhs.g,
			lhs.h + rhs.h,
			lhs.i + rhs.i,
			lhs.j + rhs.j,
			lhs.k + rhs.k,
			lhs.l + rhs.l,
			lhs.m + rhs.m,
			lhs.n + rhs.n,
			lhs.o + rhs.o,
			lhs.p + rhs.p);

		result.matrixArray[0] = result.a;
		result.matrixArray[1] = result.b;
		result.matrixArray[2] = result.c;
		result.matrixArray[3] = result.d;
		result.matrixArray[4] = result.e;
		result.matrixArray[5] = result.f;
		result.matrixArray[6] = result.g;
		result.matrixArray[7] = result.h;
		result.matrixArray[8] = result.i;
		result.matrixArray[9] = result.j;
		result.matrixArray[10] = result.k;
		result.matrixArray[11] = result.l;
		result.matrixArray[12] = result.m;
		result.matrixArray[13] = result.n;
		result.matrixArray[14] = result.o;
		result.matrixArray[15] = result.p;
		return result;
	}

	void Matrix4::Matrix4Sub(const Matrix4& rhs) {
		a -= rhs.a;
		b -= rhs.b;
		c -= rhs.c;
		d -= rhs.d;
		e -= rhs.e;
		f -= rhs.f;
		g -= rhs.g;
		h -= rhs.h;
		i -= rhs.i;
		j -= rhs.j;
		k -= rhs.k;
		l -= rhs.l;
		m -= rhs.m;
		n -= rhs.n;
		o -= rhs.o;
		p -= rhs.p;

		matrixArray[0] = a;
		matrixArray[1] = b;
		matrixArray[2] = c;
		matrixArray[3] = d;
		matrixArray[4] = e;
		matrixArray[5] = f;
		matrixArray[6] = g;
		matrixArray[7] = h;
		matrixArray[8] = i;
		matrixArray[9] = j;
		matrixArray[10] = k;
		matrixArray[11] = l;
		matrixArray[12] = m;
		matrixArray[13] = n;
		matrixArray[14] = o;
		matrixArray[15] = p;
	}

	Matrix4 Matrix4::Matrix4Sub2(const Matrix4& lhs, const Matrix4& rhs) {
		Matrix4 result(lhs.a - rhs.a,
			lhs.b - rhs.b,
			lhs.c - rhs.c,
			lhs.d - rhs.d,
			lhs.e - rhs.e,
			lhs.f - rhs.f,
			lhs.g - rhs.g,
			lhs.h - rhs.h,
			lhs.i - rhs.i,
			lhs.j - rhs.j,
			lhs.k - rhs.k,
			lhs.l - rhs.l,
			lhs.m - rhs.m,
			lhs.n - rhs.n,
			lhs.o - rhs.o,
			lhs.p - rhs.p);

		result.matrixArray[0] = result.a;
		result.matrixArray[1] = result.b;
		result.matrixArray[2] = result.c;
		result.matrixArray[3] = result.d;
		result.matrixArray[4] = result.e;
		result.matrixArray[5] = result.f;
		result.matrixArray[6] = result.g;
		result.matrixArray[7] = result.h;
		result.matrixArray[8] = result.i;
		result.matrixArray[9] = result.j;
		result.matrixArray[10] = result.k;
		result.matrixArray[11] = result.l;
		result.matrixArray[12] = result.m;
		result.matrixArray[13] = result.n;
		result.matrixArray[14] = result.o;
		result.matrixArray[15] = result.p;

		return result;
	}

	void Matrix4::Matrix4Mul(const float scale) {
		a *= scale;
		b *= scale;
		c *= scale;
		d *= scale;
		e *= scale;
		f *= scale;
		g *= scale;
		h *= scale;
		i *= scale;
		j *= scale;
		k *= scale;
		l *= scale;
		m *= scale;
		n *= scale;
		o *= scale;
		p *= scale;

		matrixArray[0] = a;
		matrixArray[1] = b;
		matrixArray[2] = c;
		matrixArray[3] = d;
		matrixArray[4] = e;
		matrixArray[5] = f;
		matrixArray[6] = g;
		matrixArray[7] = h;
		matrixArray[8] = i;
		matrixArray[9] = j;
		matrixArray[10] = k;
		matrixArray[11] = l;
		matrixArray[12] = m;
		matrixArray[13] = n;
		matrixArray[14] = o;
		matrixArray[15] = p;
	}

	Matrix4 Matrix4::Matrix4Mul2(const Matrix4& rhs, const float scale) {
		Matrix4 result(rhs.a * scale,
			rhs.b * scale,
			rhs.c * scale,
			rhs.d * scale,
			rhs.e * scale,
			rhs.f * scale,
			rhs.g * scale,
			rhs.h * scale,
			rhs.i * scale,
			rhs.j * scale,
			rhs.k * scale,
			rhs.l * scale,
			rhs.m * scale,
			rhs.n * scale,
			rhs.o * scale,
			rhs.p * scale
		);

		result.matrixArray[0] = result.a;
		result.matrixArray[1] = result.b;
		result.matrixArray[2] = result.c;
		result.matrixArray[3] = result.d;
		result.matrixArray[4] = result.e;
		result.matrixArray[5] = result.f;
		result.matrixArray[6] = result.g;
		result.matrixArray[7] = result.h;
		result.matrixArray[8] = result.i;
		result.matrixArray[9] = result.j;
		result.matrixArray[10] = result.k;
		result.matrixArray[11] = result.l;
		result.matrixArray[12] = result.m;
		result.matrixArray[13] = result.n;
		result.matrixArray[14] = result.o;
		result.matrixArray[15] = result.p;

		return result;
	}

	void Matrix4::Matrix4Div(const float scale) {
		if (scale == 0) {
			a = scale;
			b = scale;
			c = scale;
			d = scale;
			e = scale;
			f = scale;
			g = scale;
			h = scale;
			i = scale;
			j = scale;
			k = scale;
			l = scale;
			m = scale;
			n = scale;
			o = scale;
			p = scale;
		}
		else {
			a *= scale;
			b *= scale;
			c *= scale;
			d *= scale;
			e *= scale;
			f *= scale;
			g *= scale;
			h *= scale;
			i *= scale;
			j *= scale;
			k *= scale;
			l *= scale;
			m *= scale;
			n *= scale;
			o *= scale;
			p *= scale;
		}

		matrixArray[0] = a;
		matrixArray[1] = b;
		matrixArray[2] = c;
		matrixArray[3] = d;
		matrixArray[4] = e;
		matrixArray[5] = f;
		matrixArray[6] = g;
		matrixArray[7] = h;
		matrixArray[8] = i;
		matrixArray[9] = j;
		matrixArray[10] = k;
		matrixArray[11] = l;
		matrixArray[12] = m;
		matrixArray[13] = n;
		matrixArray[14] = o;
		matrixArray[15] = p;
	}

	Matrix4 Matrix4::Matrix4Div2(const Matrix4& rhs, const float scale) {
		Matrix4 result;
		if (scale == 0) {
			result.a = 0;
			result.b = 0;
			result.c = 0;
			result.d = 0;
			result.e = 0;
			result.f = 0;
			result.g = 0;
			result.h = 0;
			result.i = 0;
			result.j = 0;
			result.k = 0;
			result.l = 0;
			result.m = 0;
			result.n = 0;
			result.o = 0;
			result.p = 0;
		}
		else {
			result.a = rhs.a / scale;
			result.b = rhs.b / scale;
			result.c = rhs.c / scale;
			result.d = rhs.d / scale;
			result.e = rhs.e / scale;
			result.f = rhs.f / scale;
			result.g = rhs.g / scale;
			result.h = rhs.h / scale;
			result.i = rhs.i / scale;
			result.j = rhs.j / scale;
			result.k = rhs.k / scale;
			result.l = rhs.l / scale;
			result.m = rhs.m / scale;
			result.n = rhs.n / scale;
			result.o = rhs.o / scale;
			result.p = rhs.p / scale;
		}

		result.matrixArray[0] = result.a;
		result.matrixArray[1] = result.b;
		result.matrixArray[2] = result.c;
		result.matrixArray[3] = result.d;
		result.matrixArray[4] = result.e;
		result.matrixArray[5] = result.f;
		result.matrixArray[6] = result.g;
		result.matrixArray[7] = result.h;
		result.matrixArray[8] = result.i;
		result.matrixArray[9] = result.j;
		result.matrixArray[10] = result.k;
		result.matrixArray[11] = result.l;
		result.matrixArray[12] = result.m;
		result.matrixArray[13] = result.n;
		result.matrixArray[14] = result.o;
		result.matrixArray[15] = result.p;

		return result;
	}

	Matrix4 Matrix4::getMatrixElements() {
		Matrix4 result(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
		return result;
	}

	Matrix4 Matrix4::getMatrix() {
		return matrixArray;
	}

	Matrix4 Matrix4::setMatrix(float AA, float BB, float CC, float DD, float EE, float FF, float GG, float HH, float II, float JJ, float KK, float LL, float MM, float NN, float OO, float PP) {
		Matrix4 result;
		result.a = AA;
		result.b = BB;
		result.c = CC;
		result.d = DD;
		result.e = EE;
		result.f = FF;
		result.g = GG;
		result.h = HH;
		result.i = II;
		result.j = JJ;
		result.k = KK;
		result.l = LL;
		result.m = MM;
		result.n = NN;
		result.o = OO;
		result.p = PP;

		result.matrixArray[0] = result.a;
		result.matrixArray[1] = result.b;
		result.matrixArray[2] = result.c;
		result.matrixArray[3] = result.d;
		result.matrixArray[4] = result.e;
		result.matrixArray[5] = result.f;
		result.matrixArray[6] = result.g;
		result.matrixArray[7] = result.h;
		result.matrixArray[8] = result.i;
		result.matrixArray[9] = result.j;
		result.matrixArray[10] = result.k;
		result.matrixArray[11] = result.l;
		result.matrixArray[12] = result.m;
		result.matrixArray[13] = result.n;
		result.matrixArray[14] = result.o;
		result.matrixArray[15] = result.p;

		return result;

	}


	float* Matrix4::data()
	{
		return matrixArray;
	}

	const float* Matrix4::data() const
	{
		return matrixArray;
	}



}