#include "Vector3.h"
#include "../tobcore.h"


Vector3::Vector3()
	:x(0), y(0), z(0) {}
Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z) {}
Vector3::Vector3(const Vector3& vec)
	:x(vec.x), y(vec.y), z(vec.z) {}
//^^^ prob not necessary but doing it anyways

Vector3 Vector3::Add(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}
Vector3 Vector3::Sub(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
Vector3 Vector3::Mul(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}
Vector3 Vector3::Mul(const Vector3& lhs, const float val)
{
	return Vector3(lhs.x * val, lhs.y * val, lhs.z * val);
}
Vector3 Vector3::Div(const Vector3& lhs, const float val)
{
	if (cmpf(val, 0)) return Vector3(999999, 999999, 999999);
	return Vector3(lhs.x / val, lhs.y / val, lhs.z / val);
}
Vector3 Vector3::Invert(const Vector3& vec)
{
	return Vector3(-vec.x, -vec.y, -vec.z);
}


bool Vector3::Equals(const Vector3& lhs, const Vector3& rhs)
{
	return cmpf(lhs.x, rhs.x) && cmpf(lhs.y, rhs.y) && cmpf(lhs.z, rhs.z);
}

float Vector3::Mag(const Vector3& vec)
{
	return sqrtf(SqrMag(vec));
}
float Vector3::SqrMag(const Vector3& vec)
{
	return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}
Vector3 Vector3::Normalize(const Vector3& vec)
{
	float mag = Mag(vec);
	return Div(vec, mag);
}
Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
	return Vector3((a.y * b.z - a.z * b.y), (a.z * b.x - a.z * b.z), (a.x * b.y - a.y * b.x));
	//https://en.wikipedia.org/wiki/Euclidean_vector#Cross_product
}
float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float Vector3::Angle(const Vector3& a, const Vector3& b)
{
	// https://forums.unrealengine.com/t/vector3-angle-analog-in-c/462742
	float angleCos = Dot(a, b) / (Mag(a) * Mag(b));
	float radians = acosf(angleCos);
	return radians * Rad2Deg;
}

Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, float t)
{
	
}

Vector3 Vector3::Direction(const Vector3& from, const Vector3& to)
{
	return Normalize(Sub(to, from));
}

Vector3 Vector3::Direction_NoNormalize(const Vector3& from, const Vector3& to)
{
	return Sub(to, from);
}

float Vector3::Distance(const Vector3& from, const Vector3& to)
{
	return Mag(Sub(from, to));
}
float Vector3::SqrDistance(const Vector3& from, const Vector3& to)
{
	return SqrMag(Sub(from, to));
}