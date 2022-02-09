#pragma once

// https://noobtuts.com/cpp/fast-vector3-class
// https://en.wikipedia.org/wiki/Euclidean_vector

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);

	static Vector3 Add(const Vector3 lhs, const Vector3 rhs);
	static Vector3 Sub(const Vector3 lhs, const Vector3 rhs);
	static Vector3 Mul(const Vector3 lhs, const Vector3 rhs);
	static Vector3 Mul(const Vector3 lhs, const float val);
	static Vector3 Div(const Vector3 lhs, const float val);

	static bool Equals(const Vector3 lhs, const Vector3 rhs);
	// #include "cmpf.h" ^^^

	static float Mag(const Vector3 vec);
	static float SqrMag(const Vector3 vec);
	static float Normalized(const Vector3 vec);
	static Vector3 Cross(const Vector3 a, const Vector3 b);
	static float Dot(const Vector3 lhs, const Vector3 rhs);

	static Vector3 Lerp(const Vector3 start, const Vector3 end, float t);

	static Vector3 Direction(const Vector3 from, const Vector3 to);

	static Vector3 Distance(const Vector3 from, const Vector3 to);
	static Vector3 SqrDistance(const Vector3 from, const Vector3 to);
};