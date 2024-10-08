#include "Vector/Vector2.h"

#include "Framework/WinGameApp.h"
#include "Math/Mathf.h"

#include <Vector/Vector3.h>
#include <assert.h>

const Vector2 Vector2::Zero{ 0,0 };
const Vector2 Vector2::Right{ 1,0 };
const Vector2 Vector2::Left{ -1,0 };
const Vector2 Vector2::Up{ 0, 1 };
const Vector2 Vector2::Down{ 0, -1 };

Vector2::Vector2(float x, float y)
{
	this->x = (float)x;
	this->y = (float)y;
}

Vector2::Vector2(std::vector<float>&& vec)
{
	if (vec.size() != 2)
	{
		assert(!"요소가 2개인 vector만 Vector2 타입으로 대입 가능 합니다.");
	}
	this->x = vec[0];
	this->y = vec[1];
}

Vector2::Vector2(const Vector3& vector3)
{
	this->x = vector3.x;
	this->y = vector3.y;
}

Vector2::Vector2(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
}

float Vector2::SqrMagnitude() const
{
	return x * x + y * y;
}

float Vector2::Magnitude() const
{
	return sqrtf(SqrMagnitude());
}

Vector2 Vector2::Normalized() const
{
	float magnitude = Magnitude();
	if (std::abs(magnitude) > std::numeric_limits<float>::epsilon())
	{
		Vector2 normal = Vector2{ float(x / magnitude) , float(y / magnitude) };
		return normal;
	}
	return Vector2{ 0,0 };
}

void Vector2::Normalize()
{
	float magnitude = Magnitude();
	if (std::abs(magnitude) > std::numeric_limits<float>::epsilon())
	{
		this->x = float(x / magnitude);
		this->y	= float(y / magnitude);
	}
}

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

Vector2& Vector2::operator=(const std::vector<float>& vec)
{
	if (vec.size() != 2)
	{
		assert(!"요소가 2개인 vector만 Vector2 타입으로 대입 가능 합니다.");
	}
	this->x = vec[0];
	this->y = vec[1];

	return *this;
}

Vector2& Vector2::operator=(std::vector<float>&& vec)
{
	if (vec.size() != 2)
	{
		assert(!"요소가 2개인 vector만 Vector2 타입으로 대입 가능 합니다.");
	}
	this->x = vec[0];
	this->y = vec[1];

	return *this;
}

Vector2 Vector2::operator*(const float scala) const
{
	Vector2 value = Vector2{ this->x, this->y };
	value.x *= scala;
	value.y *= scala;

	return value;
}

Vector2 Vector2::operator/(const float scala) const
{
	Vector2 value = Vector2{ this->x, this->y };
	value.x /= scala;
	value.y /= scala;

	return value;
}

Vector2& Vector2::operator*=(const float scala)
{
	this->x *= scala;
	this->y *= scala;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	Vector2 sum = Vector2{ 0, 0 };
	sum.x = this->x + other.x;
	sum.y = this->y + other.y;

	return sum;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	Vector2 sub = Vector2{ 0, 0 };
	sub.x = this->x - other.x;
	sub.y = this->y - other.y;

	return sub;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-this->x, -this->y);
}

bool Vector2::operator!=(const Vector2& other) const
{
	return (this->x != other.x || this->y != other.y);
}

bool Vector2::operator==(const Vector2& other) const
{
	return (this->x == other.x && this->y == other.y);
}

Vector2::operator Vector3()
{
	return Vector3{ this->x, this->y, 0 };
}

//static:

Vector2 Vector2::GetScaleFromMatrix(const D2D1_MATRIX_3X2_F& matrix)
{
	float x = sqrtf(matrix._11 * matrix._11 + matrix._12 * matrix._12);
	float y = sqrtf(matrix._21 * matrix._21 + matrix._22 * matrix._22);
	return Vector2(x, y);
}

Vector2 Vector2::WorldToScreenPoint(const Vector2& pos)
{
	return Vector2{ pos.x, (float)WinGameApp::GetClientSize().cy - pos.y};
}

Vector2 Vector2::Lerp(const Vector2& startPos, const Vector2& endPos, const float t)
{
	Vector2 Lerp = Vector2{ (1.f - t) * startPos.x + t * endPos.x, (1.f - t) * startPos.y + t * endPos.y };

	return Lerp;
}

Vector2 Vector2::BezierCurve(const Vector2& startPos, const Vector2& middlePos, const Vector2& endPos, const float t)
{
	Vector2 bezierCurve = Lerp(Lerp(startPos, middlePos, t), Lerp(middlePos, endPos, t), t);
	
	return bezierCurve;
}

Vector2 Vector2::LagranCurve(float x, Vector2* pointArray, int pointArraySize)
{
	float* L = new float[pointArraySize] {};
	for (int i = 0; i < pointArraySize; i++)
	{
		float temp1 = 1;
		float temp2 = 1;
		for (int j = 0; j < pointArraySize; j++)
		{
			if (j == i)
				continue;
			temp1 *= (x - pointArray[j].x);
		}
		for (int j = 0; j < pointArraySize; j++)
		{
			if (j == i)
				continue;
			temp2 *= (pointArray[i].x - pointArray[j].x);
		}
		L[i] = temp1 / temp2;
	}
	float y = 0;
	for (int i = 0; i < pointArraySize; i++)
	{
		y += L[i] * pointArray[i].y;
	}
	delete[] L;
	return Vector2(x, y);
}

Vector2 Vector2::GetRotatedPoint(const Vector2& point, const float angle, const Vector2& center)
{
	if (std::abs(angle) < 1e-9)
		return point;

	float radian = angle * Mathf::Deg2Rad;

	float cos = cosf(radian);
	float sin = sinf(radian);

	// 평행 이동: 중점 기준으로 이동
	float translatedX = point.x - center.x;
	float translatedY = point.y - center.y;

	// 회전 변환 적용
	float rotX = translatedX * cos - translatedY * sin;
	float rotY = translatedX * sin + translatedY * cos;

	// 다시 원래 위치로 평행 이동
	rotX += center.x;
	rotY += center.y;

	return Vector2{ rotX , rotY };
}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::Cross(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.y - lhs.y * rhs.x;
}
