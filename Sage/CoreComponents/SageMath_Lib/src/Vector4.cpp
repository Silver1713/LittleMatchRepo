#include "Vector4.h"

#include <cmath>

namespace ToastBox
{
	Vec4::Vec4(const Vec4& pVec0)
	{
		x = pVec0.x;
		y = pVec0.y;
		z = pVec0.z;
		w = pVec0.w;
	}



	Vec4::Vec4(float const& x, float const& y, float const& z, float const& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vec4& Vec4::operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	Vec4& Vec4::operator+=(const Vec4& pVec0)
	{
		x += pVec0.x;
		y += pVec0.y;
		z += pVec0.z;
		w += pVec0.w;
		return *this;
	}

	Vec4& Vec4::operator%=(const Vec4& pVec0)
	{
		// Cross product
		Vec4 result{};
		result.x = y * pVec0.z - z * pVec0.y;
		result.y = z * pVec0.x - x * pVec0.z;
		result.z = x * pVec0.y - y * pVec0.x;

		x = result.x;
		y = result.y;
		z = result.z;

		return *this;
	}

	Vec4& Vec4::operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	}

	Vec4& Vec4::operator-=(const Vec4& pVec0)
	{
		x -= pVec0.x;
		y -= pVec0.y;
		z -= pVec0.z;
		w -= pVec0.w;
		return *this;
	}


	Vec4& Vec4::operator/=(const Vec4& pVec0)
	{
		x /= pVec0.x;
		y /= pVec0.y;
		z /= pVec0.z;
		w /= pVec0.w;
		return *this;
	}

	Vec4& Vec4::operator/=(const float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	Vec4& Vec4::operator=(const Vec4& pVec0)
	{
		x = pVec0.x;
		y = pVec0.y;
		z = pVec0.z;
		w = pVec0.w;
		return *this;
	}


	float& Vec4::operator[](int index)
	{
		return (&x)[index];
	}

	float Vec4::operator[](int index) const
	{
		return (&x)[index];
	}



	float Vec4::magnitude() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}


	float Vec4::magnitudeSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}


	void Vec4::normalize(Vec4& pResult, const Vec4& pVec0)
	{
		const Vec4 result{ pVec0 };

		pResult = result / result.magnitude();


	}


	Vec4 operator*(const float value, const Vector4& pVec0)
	{
		Vec4 res{ pVec0 };
		res *= value;

		return res;
	}

	Vec4 operator*(const Vector4& pVec0, const float value)
	{
		Vec4 res{ pVec0 };
		res *= value;

		return res;
	}


	Vec4 operator/(const Vector4& pVec0, const float value)
	{
		Vec4 res{ pVec0 };
		res /= value;

		return res;
	}


	Vec4 operator/(const Vector4& pVec0, const Vector4& pVec1)
	{
		Vec4 res{ pVec0 };
		res /= pVec1;

		return res;
	}


	Vector4 operator%(const Vector4& pVec0, const Vector4& pVec1)
	{
		Vec4 res{ pVec0 };

		res %= pVec1;
		return res;
	}


	Vector4 operator+(const Vector4& pVec0, const Vector4& pVec1)
	{
		Vector4 res{ pVec0 };
		res += pVec1;
		return res;
	}


	Vector4 operator-(const Vector4& pVec0, const Vector4& pVec1)
	{
		Vec4 newVec{ pVec0 };

		newVec -= pVec1;

		return newVec;

	}

	float operator*(const Vector4& pVec0, const Vector4& pVec1)
	{
		return pVec0.x * pVec1.x + pVec0.y * pVec1.y + pVec0.z * pVec1.z + pVec0.w * pVec1.w;
	}


	Vector4 operator/(const float value, const Vector4& pVec0)
	{
		Vec4 res{ pVec0 };
		res /= value;

		return res;
	}

	float* Vec4::data()
	{
		return &x;
	}


}






















