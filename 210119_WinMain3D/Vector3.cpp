#include "Vector3.h"
#include "Matrix.h"
#include <cmath>

bool Vector3::operator==(Vector3& vec)
{
	return fabs(x - vec.x) < EPSILON && fabs(y - vec.y) < EPSILON && fabs(z - vec.z) < EPSILON;
}

bool Vector3::operator!=(Vector3& vec)
{
	return fabs(x - vec.x) > EPSILON || fabs(y - vec.y) > EPSILON || fabs(z - vec.z) > EPSILON;
}

const Vector3 Vector3::operator+(const Vector3& vec) const
{
	Vector3 ret;
	ret.x = x + vec.x;
	ret.y = y + vec.y;
	ret.z = z + vec.z;
	return ret;
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

const Vector3 Vector3::operator-(const Vector3& vec) const
{
	Vector3 ret;
	ret.x = x - vec.x;
	ret.y = y - vec.y;
	ret.z = z - vec.z;
	return ret;
}

const Vector3 Vector3::operator*(const float f) const
{
	Vector3 ret;
	ret.x = x * f;
	ret.y = y * f;
	ret.z = z * f;
	return ret;
}

Vector3 Vector3::operator/(float f)
{
	Vector3 ret;
	ret.x = x / f;
	ret.y = y / f;
	ret.z = z / f;
	return ret;
}

float& Vector3::operator[](int index)
{
	switch (index)
	{
	case 0:	return x;
	case 1: return y;
	case 2: return z;
	default: throw exception();
	}
}

float Vector3::Length()
{
	return  sqrtf(x * x + y * y + z * z);
}

const Vector3 Vector3::Normalize() const
{
	Vector3 ret;
	float length = sqrtf(x * x + y * y + z * z);
	ret.x = x / length;
	ret.y = y / length;
	ret.z = z / length;
	return ret;
}

const float Vector3::Dot(const Vector3& vec1, const Vector3& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

const Vector3 Vector3::Cross(const Vector3& vec1, const Vector3& vec2)
{
	Vector3 ret;
	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return ret;
}

const Vector3 Vector3::TransformCoord(const Vector3& v, Matrix& mat)
{
	Matrix coordVec = { {v.x, v.y, v.z, 1} };
	Matrix ret = coordVec * mat;

	if (ret[0][3] < EPSILON || ret[0][3] > EPSILON)
	{
		ret[0][0] /= ret[0][3];
		ret[0][1] /= ret[0][3];
		ret[0][2] /= ret[0][3];
	}
	return { ret[0][0], ret[0][1], ret[0][2] };
}

Vector3 Vector3::TransformNormal(Vector3& v, Matrix& mat)
{
	Matrix normalVec = { {v.x, v.y, v.z, 0} };
	Matrix ret = normalVec * mat;

	return { ret[0][0], ret[0][1], ret[0][2] };
}
