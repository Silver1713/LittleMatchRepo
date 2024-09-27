#ifndef TOAST_VEC4_HPP
#define TOAST_VEC4_HPP
namespace ToastBox
{
	class Vec4;
	using Vector4 =  Vec4;

	class Vec4
	{
	public:
		union
		{
			float x, r, s;
		};
		union
		{
			float y, g, t;
		};

		union
		{
			float z, b, p;
		};

		union
		{
			float w, a, q;
		};

		Vec4() :x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {}

		Vec4( float const& x,  float const& y,  float const& z,  float const& w);
		Vec4(const Vec4& pVec0);

		Vec4& operator-();
		Vec4& operator*=(const float value);


		Vec4& operator/=(const Vec4& pVec0);
		Vec4& operator/=(const float value);

		Vec4& operator+=(const Vec4& pVec0);

		Vec4& operator-=(const Vec4& pVec0);

		Vec4& operator=(const Vec4& pVec0);

		Vec4& operator%=(const Vec4& pVec0);


		float& operator[](int index);
		float operator[](int index) const;

		float magnitude() const;
		float magnitudeSquared() const;
		void normalize(Vec4& pResult, const Vec4& pVec0);

		float* data();
		

	};



	Vector4 operator+(const Vector4& pVec0, const Vector4& pVec1);
	Vector4 operator-(const Vector4& pVec0, const Vector4& pVec1); 

	Vector4 operator*(const Vector4& pVec0, const float value); // scale
	Vector4 operator*(const float value, const Vector4& pVec0);
	
	Vector4 operator/(const float value, const Vector4& pVec0);
	Vector4 operator/(const Vector4& pVec0, const float value); // division


	float operator*(const Vector4& pVec0, const Vector4& pVec1); // dot
	Vector4 operator/(const Vector4& pVec0, const Vector4& pVec1); // division

	Vector4 operator%(const Vector4& pVec0, const Vector4& pVec1); // cross

	

}
#endif