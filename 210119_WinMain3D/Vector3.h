#pragma once
class Vector3
{
public:
	float x, y, z;

public:
	bool operator==(Vector3& vec);	// if (a == b), if (a.operator==(b))
	bool operator!=(Vector3& vec);

	Vector3 operator+(Vector3& vec);	// a + b
	Vector3 operator-(Vector3& vec);
	Vector3 operator*(float f);
	Vector3 operator/(float f);

	float Length();
	Vector3 Normalize();

	static float Dot(Vector3& vec1, Vector3& vec2);
	static Vector3 Cross(Vector3& vec1, Vector3& vec2);
};

