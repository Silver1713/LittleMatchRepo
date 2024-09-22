/******************************************************************************
File name	 : Vector3.cpp
Project		 : Memory's Flame
Author       : Edwin Lee Zirui
E-mail		 : edwinzirui.lee@digipen.edu
Data		 : 09/09/2024
Brief		 : Vector3 class and class operation defination
*
* \copyright	All content 2024 DigiPen Institute of Technology Singapore. All
				rights reserved.
******************************************************************************/


#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3x3.h"

namespace ToastBox {
	Vec3::Vec3() :x{ 0 }, y{ 0 }, z{ 0 } {}
	Vec3::Vec3(const float x, const float y, const float z) : x{ x }, y{ y }, z{ z } {}

	/*
	Function: invert
	Desc: Invert the vector
	Example: -a = -1 *a = <-x,-y,-z>
	*/
	void Vec3::invert() {
		x = -x;
		y = -y;
		z = -z;
	}

	/*
	Function magnitude
	Desc: Return magnitude of the vector
	*/
	float Vec3::magnitude() const {
		return real_sqrt(x * x + y * y + z * z);
	}

	/*
	Function: magnitudeSquared
	Desc: Return squared magnitude of the vector
	*/
	float Vec3::magnitudeSquared() const {
		return x * x + y * y + z * z;
	}

	/*
	Function: normalize
	Param: pResult -> For returning of normalized vector
	Param: pVec0   -> The vector to be normalized
	Desc: Normlized vector
	*/
	void Vec3::normalize(Vec3& pResult, const Vec3& pVec0) {
		Vec3 result;
		result.x = pVec0.x * pVec0.x;
		result.y = pVec0.y * pVec0.y;
		result.z = pVec0.z * pVec0.z;

		float addition{ result.x + result.y + result.z };
		float magnitude{ static_cast<float>(sqrt(addition)) };
		pResult.x = pVec0.x / magnitude;
		pResult.y = pVec0.y / magnitude;
		pResult.z = pVec0.z / magnitude;

	}

	/*
	Function: operator *=
	Param: value
	Desc: Multiplies vector by param <value>
	*/
	void Vec3::operator*= (const float value) {
		x *= value;
		y *= value;
		z *= value;
	}

	/*
	Function: operator *
	Param: value
	Desc: Return a  a copy of the vector scaled to param <value>. Not to be confused by dot product
	*/
	Vec3 Vec3::operator*(const float value) const {
		return Vec3(x * value, y * value, z * value);
	}

	/*
	Function: operator/=
	Param: pVec0
	Desc: Divides the vector by param pVec0 component level
	*/
	void Vec3::operator/=(const Vec3& pVec0) {
		if (pVec0.x == 0) {
			x = 0;
		}
		else {
			x /= pVec0.x;
		}

		if (pVec0.y == 0) {
			y = 0;
		}
		else {
			y /= pVec0.y;
		}

		if (pVec0.z == 0) {
			z = 0;
		}
		else {
			z /= pVec0.z;
		}
	}

	/*
	Function: operator/
	Param: value
	Desc: Return a new vector by dividing current vector with param<value> component level division
	Example: c = a / b = <a.x, a.y> / <b.x, b.y > = <a.x / b.x, a.y / b.y*/
	Vec3 Vec3::operator/(const float value) const {
		if (value == 0) {
			return Vec3(0, 0, 0);
		}
		else {
			return Vec3(x / value, y / value, z / value);
		}
	}

	/*
	Function: operator+=
	Param: pVec0
	Desc: Return a new vector by adding current vector with param<pVec0> vector
	Example: c = a + b = <a.x, a.y, a.z> + <b.x, b.y, b.z> = <a.x + b.x, a.y + b.y, a.z + b.z>*/
	void Vec3::operator+=(const Vec3& pVec0) {
		x += pVec0.x;
		y += pVec0.y;
		z += pVec0.z;
	}

	/*
	Function: operator+
	Param: pVec0
	Desc: Return a new vector by adding current vector with param<pVec0> vector
	Example: c = a + b = <a.x, a.y, a.z> + <b.x, b.y, b.z> = <a.x + b.x, a.y + b.y, a.z + b.z>*/
	Vec3 Vec3::operator+(const Vec3& pVec0) const {
		return Vec3(x + pVec0.x, y + pVec0.y, z + pVec0.z);
	}

	/*
	Function: addition
	Param: vec1, vec2
	Desc: Return addition result of 2 vector vec1 and vec2*/
	Vec3 Vec3::addition(const Vec3& vec1, const Vec3& vec2) {
		return Vec3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
	}

	/*
	Function: operator-=
	Param: pVec0
	Desc: Return a new vector by subracting current vector with param<pVec0> vector
	Example: c = a - b = <a.x, a.y,a.z> - <b.x, b.y,b.z> = <a.x - b.x, a.y - b.y, a.z - b.z>*/
	void Vec3::operator-=(const Vec3& pVec0) {
		x -= pVec0.x;
		y -= pVec0.y;
		z -= pVec0.z;
	}

	/*
	Function: operator-
	Param: pVec0
	Desc: Return a new vector by subracting current vector with param<pVec0> vector
	Example: c = a - b = <a.x, a.y,a.z> - <b.x, b.y,b.z> = <a.x - b.x, a.y - b.y, a.z - b.z>*/
	Vec3 Vec3::operator-(const Vec3& pVec0) const {
		return Vec3(x - pVec0.x, y - pVec0.y, z - pVec0.z);
	}

	/*
	Function: subtraction
	Param: vec1, vec2
	Desc: Return the result of subraction between vec1 and vec2 as in vec1 - vec2 = result
	*/
	Vec3 Vec3::subtraction(const Vec3& vec1, const Vec3& vec2) {
		return Vec3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
	}

	/*
	Function: scaledVectorAdding
	Param: value
	Desc: Return a copy of the vector scaled to param <value>
	Example: a + kb = <a.x, a.y,a.z> + k<b.x, b.y,b.z > = <a.x + kb.x, a.y + kb.y,a.z + kb.z>
	Notes: This function can be used update position of point as in
	position = (velocity * time) + acceleration * time^2 * 0.5
	can be calulated with
	object.position = scaledVectorAdding(object.velocity,time) and
	object.position = scaledVectorAdding(object.acceleration,time*time*0.5)
	*/
	void Vec3::scaledVectorAdding(const Vec3& pVec0, float k) {
		x += pVec0.x * k;
		y += pVec0.y * k;
		z += pVec0.z * k;
	}

	/*
	Function: productComponent
	Param: pVec0
	Desc: Multiples individual component of a vector by param<pVec0> corresponding component value
	Example: c = a productComponent b = <a.x, a.y, a.z> productComponent <b.x, b.y, b.z> = <a.x * b.x, a.y * b.y, a.z * b.z> */
	Vec3 Vec3::productComponent(const Vec3& pVec0) const {
		return Vec3(x * pVec0.x, y * pVec0.y, z * pVec0.z);
	}

	/*
	Function: productComponentUpdate
	Param: pVec0
	Desc: Multiples individual component of a vector by param<pVec0> corresponding component value
	Example: c = a productComponent b = <a.x, a.y, a.z> productComponent <b.x, b.y, b.z> = <a.x * b.x, a.y * b.y, a.z * b.z> */
	void Vec3::productComponentUpdate(const Vec3& pVec0) {
		x *= pVec0.x;
		y *= pVec0.y;
		z *= pVec0.z;
	}

	/*
	Function: productScalar
	Param: pVec0
	Desc: Dot-Product Operation
	Return scalar product of current vector with another vector <pVec3>.
	Example: a * b = <a.x, a.y, a.z> * <b.x, b.y, b.z> = a.x * b.x + a.y * b.y + a.z * b.z*/
	float Vec3::productScalar(const Vec3& pVec0) const {
		return x * pVec0.x + y * pVec0.y + z * pVec0.z;
	}

	/*
	Function: operator*
	Param: pVec0
	Desc: Dot-Product Operation
	Return scalar product of current vector with another vector <pVec3>.
	Example: a * b = <a.x, a.y, a.z> * <b.x, b.y, b.z> = a.x * b.x + a.y * b.y + a.z * b.z */
	float Vec3::operator*(const Vec3& pVec0) const {
		return x * pVec0.x + y * pVec0.y + z * pVec0.z;
	}

	/*
	Function: productCross
	Param: pVec0
	Desc: Return cross product vector */
	Vec3 Vec3::productCross(const Vec3& pVec0) const {
		return Vec3(y * pVec0.z - z * pVec0.y,
			z * pVec0.x - x * pVec0.z,
			x * pVec0.y - y * pVec0.x);
	}

	/*
	Function: operator%=
	Param: pVec0
	Desc: Return cross product vector */
	void Vec3::operator%=(const Vec3& pVec0) {
		productCross(pVec0);
	}

	/*
	Function: operator%
	Param: pVec0
	Desc: Return cross product vector */
	Vec3 Vec3::operator%(const Vec3& pVec0) const {
		return Vec3(y * pVec0.z - z * pVec0.y,
			z * pVec0.x - x * pVec0.z,
			x * pVec0.y - y * pVec0.x);
	}

	/*
	Function: clear
	Desc: Reset the points*/
	void Vec3::clear() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vec3 operator*(const Matrix3x3& pMtx0, const Vec3& pVec0)
	{
		Matrix3x3 pTrans{};
		pTrans.Matrix3Transpose(pMtx0);
		Vec3 result;
		result.x = pTrans.m00 * pVec0.x + pTrans.m01 * pVec0.y + pTrans.m02 * pVec0.z;
		result.y = pTrans.m10 * pVec0.x + pTrans.m11 * pVec0.y + pTrans.m12 * pVec0.z;
		result.z = pTrans.m20 * pVec0.x + pTrans.m21 * pVec0.y + pTrans.m22 * pVec0.z;
		return result;
		
	}


}