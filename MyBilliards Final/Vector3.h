#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

//=================== Includes Above ====================|==================== Classes Below ========================

class Vector3
{
public:
	//---------------------------------------------------------------------------------------------------------------
	// Name: Vector3()
	// Desc: default constructor, sets vector to 0, 0, 0
	//
	inline Vector3() {
		m_fX = 0.0f;
		m_fY = 0.0f;
		m_fZ = 0.0f;
	} //Vector3

	//---------------------------------------------------------------------------------------------------------------
	// Name: Vector3()
	// Desc: default contructor, sets vector to disired value
	//
	inline Vector3(float x, float y, float z) {
		m_fX = x;
		m_fY = y;
		m_fZ = z;
	} //Vector3

	//---------------------------------------------------------------------------------------------------------------
	// Name: ~Vector3()
	// Desc: default destructor
	//
	virtual ~Vector3() {}

	//---------------------------------------------------------------------------------------------------------------
	// Name: operator*()
	// Desc: scale a vector by a scalar value using operator overloading: ie Vector * Scalar
	//
	inline Vector3 operator*(const float &fValue) const {

		return Vector3(m_fX * fValue, m_fY * fValue, m_fX * fValue);

	} //operator*

	//---------------------------------------------------------------------------------------------------------------
	// Name: operator*()
	// Desc: scale a vector by a scalar value using operator overloading: ie Scalar * Vector
	//
	inline friend Vector3 operator*(const float &fValue, const Vector3 v) {

		return Vector3(fValue * v.m_fX, fValue * v.m_fY, fValue * v.m_fZ);

	} //operator*

	//---------------------------------------------------------------------------------------------------------------
	// Name: operator+()
	// Desc: add two vectors using operator overloading: ie Vector1 + Vector2
	//
	inline Vector3 operator+(const Vector3 &v) const {

		return Vector3(m_fX + v.m_fX, m_fY + v.m_fY, m_fZ + v.m_fZ);

	} //operator+

	//---------------------------------------------------------------------------------------------------------------
	// Name: operator-()
	// Desc: subtract two vectors using operator overloading: ie Vector1 + Vector2
	//
	inline Vector3 operator-(const Vector3 &v) const {

		return Vector3(m_fX - v.m_fX, m_fY - v.m_fY, m_fZ - v.m_fZ);

	} //operator-

	//---------------------------------------------------------------------------------------------------------------
	// Name: operator+=()
	// Desc: assign a vector by addition using operator overloading: ie Vector1 += Vector2
	//
	inline Vector3& operator+=(const Vector3 &vec3) {

		m_fX += vec3.m_fX;
		m_fY += vec3.m_fY;
		m_fZ += vec3.m_fZ;

		return *this;

	} //operator+=

	//---------------------------------------------------------------------------------------------------------------
	// Name: operator-=()
	// Desc: assign a vector by subtraction using operator overloading: ie Vector1 -= Vector2
	//
	inline Vector3& operator-=(const Vector3 &vec3) {

		m_fX -= vec3.m_fX;
		m_fY -= vec3.m_fY;
		m_fZ -= vec3.m_fZ;

		return *this;

	} //operator-=

	//---------------------------------------------------------------------------------------------------------------
	// Name: Cross()
	// Desc: find the cross product of two vectors
	//
	inline Vector3 Cross(Vector3 v1) {

		Vector3 result;

		result.m_fX = m_fY * v1.m_fZ - v1.m_fY * m_fZ;
		result.m_fY = m_fZ * v1.m_fX - v1.m_fZ * m_fX;
		result.m_fZ = m_fX * v1.m_fY - v1.m_fX * m_fY;

		return result;

	} //Cross

	//---------------------------------------------------------------------------------------------------------------
	// Name: Dot()
	// Desc: find the dot product of two vectors
	//
	inline float Dot(Vector3 v1) {

		return m_fX * v1.m_fX + m_fY * v1.m_fY + m_fZ * v1.m_fZ;

	} //Cross

	//---------------------------------------------------------------------------------------------------------------
	// Name: Magnitude()
	// Desc: find the magnitude of a vector
	//
	inline float Magnitude() {

		return sqrt(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);

	} //Magnitude

	//---------------------------------------------------------------------------------------------------------------
	// Name: Normalise()
	// Desc: normalise a vector
	//
	inline Vector3 Normalise() {

		float fMagnitude = sqrt(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);
		m_fX = m_fX * (1.0f/fMagnitude);
		m_fY = m_fY * (1.0f/fMagnitude);
		m_fZ = m_fZ * (1.0f/fMagnitude);

		Vector3 result(m_fX, m_fY, m_fZ);

		return result;

	} //Normalise

	//public member variables
	float m_fX;
	float m_fY;
	float m_fZ;

};

#endif //VECTOR3_H