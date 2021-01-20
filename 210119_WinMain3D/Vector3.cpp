#include "Vector3.h"
#include <cmath>

bool Vector3::operator==(Vector3& vec)
{
	return fabs(x - vec.x) < EPSILON && fabs(y - vec.y) < EPSILON && fabs(z - vec.z) < EPSILON;
}

bool Vector3::operator!=(Vector3& vec)
{
	return fabs(x - vec.x) > EPSILON || fabs(y - vec.y) > EPSILON || fabs(z - vec.z) > EPSILON;
}

Vector3 Vector3::operator+(Vector3& vec)
{
	Vector3 ret;
	ret.x = x + vec.x;
	ret.y = y + vec.y;
	ret.z = z + vec.z;
	return ret;
}

Vector3 Vector3::operator-(Vector3& vec)
{
	Vector3 ret;
	ret.x = x - vec.x;
	ret.y = y - vec.y;
	ret.z = z - vec.z;
	return ret;
}

Vector3 Vector3::operator*(float f)
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

float Vector3::Length()
{
	return  sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::Normalize()
{
	Vector3 ret;
	ret.x = x / Length();
	ret.y = y / Length();
	ret.z = z / Length();
	return ret;
}

float Vector3::Dot(Vector3& vec1, Vector3& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vector3 Vector3::Cross(Vector3& vec1, Vector3& vec2)
{
	Vector3 ret;
	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return ret;
}
