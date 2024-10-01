/******************************************************************************
File name	 : Vector3.h
Project		 : Memory's Flame
Author       : Edwin Lee Zirui
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 09/09/2024
Brief		 : Vector3 class and class operation declaration
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/
#pragma once

namespace ToastBox {
	class Matrix3x3;
	class Vec3 {
	public:
		float x{}, y{}, z{};
	private:
		float padding{};
	public:
		//Construction
		Vec3();
		Vec3(const float x, const float y, const float z);

		//Invert
		void invert();

		//Size
		float magnitude() const;
		float magnitudeSquared() const;
		void normalize(Vec3& pResult, const Vec3& pVec0);

		//Scalar operation
		void operator*= (const float value);
		Vec3 operator*(const float value) const;

		void operator/=(const Vec3& pVec0);
		Vec3 operator/(const float value) const;

		void operator+=(const Vec3& pVec0);
		Vec3 operator+(const Vec3& pVec0) const;
		Vec3 addition(const Vec3& vec1, const Vec3& vec2);

		void operator-=(const Vec3& pVec0);
		Vec3 operator-(const Vec3& pVec0) const;
		
		Vec3 subtraction(const Vec3& vec1, const Vec3& vec2);

		void scaledVectorAdding(const Vec3& pVec0, float k);

		//Vector multiplication
		Vec3 productComponent(const Vec3& pVec0) const;
		void productComponentUpdate(const Vec3& pVec0);

		float productScalar(const Vec3& pVec0) const;
		float operator*(const Vec3& pVec0) const;

		Vec3 productCross(const Vec3& pVec0) const;
		void operator%=(const Vec3& pVec0);
		Vec3 operator%(const Vec3& pVec0) const;

		void clear();

		friend Vec3 operator*(const Matrix3x3& pMtx0, const Vec3& pVec0);


	};

	bool operator==(Vec3 const& lhs, Vec3 const& rhs);



}