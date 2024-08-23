#pragma once
#include <d2d1.h>
#include <vector>
#include <memory>

class Vector2;
class Vector3
{
public:
	float x;
	float y;
	float z;

	explicit Vector3(float x = 0, float y = 0, float z = 0);

	virtual ~Vector3() = default;

	Vector3(const Vector3& other);

	float Magnitude() const;
	float SqrMagnitude() const;

	Vector3 Normalized() const;



	Vector3& operator=(const Vector3& other);
	Vector3 operator*(const float scala) const;
	Vector3 operator/(const float scala) const;
	Vector3& operator*=(const float scala);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-() const;
	bool operator!=(const Vector3& other) const;
	bool operator==(const Vector3& other) const;
	explicit operator Vector2();

	//static:
public:
	/** Zero Vector3(0, 0, 0) */
	static const Vector3 Zero;
	/** Right Vector3(1, 0, 0) */
	static const Vector3 Right;
	/** Left Vector3(-1, 0, 0) */
	static const Vector3 Left;
	/** Up Vector3(0, 1, 0) */
	static const Vector3 Up;
	/** Down Vector3(0, -1, 0) */
	static const Vector3 Down;
	/** Front Vector3(0, 0, 1) */
	static const Vector3 Front;
	/** Back Vector3(0, 0, -1) */
	static const Vector3 Back;

	static float Dot(Vector3 lhs, Vector3 rhs);
	static Vector3 Cross(Vector3 lhs, Vector3 rhs);
};
