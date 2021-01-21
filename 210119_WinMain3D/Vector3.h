#pragma once
#include "pch.h"

class Matrix;
class Vector3
{
public:
	float x, y, z;

public:
	bool operator==(Vector3& vec);	// if (a == b), if (a.operator==(b))
	bool operator!=(Vector3& vec);

	const Vector3 operator+(const Vector3& vec) const;	// a + b
	Vector3& operator+=(const Vector3& vec);
	Vector3& operator-=(const Vector3& vec);
	const Vector3 operator-(const Vector3& vec) const;
	const Vector3 operator*(const float f) const;
	Vector3 operator/(float f);
	float& operator[](int index);

	Vector3() : x(0), y(0), z(0) {};
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3(std::initializer_list<float> l)
		: x(*l.begin())
		, y(*(l.begin()+1))
		, z(*(l.begin()+2))
	{}
	float Length();
	const Vector3 Normalize() const;

	static const float Dot(const Vector3& vec1, const Vector3& vec2);
	static const Vector3 Cross(const Vector3& vec1, const Vector3& vec2);

	static const Vector3 TransformCoord(const Vector3& v, Matrix& mat);		// 포인트 연산
	static Vector3 TransformNormal(Vector3& v, Matrix& mat);	// 벡터 연산
};

