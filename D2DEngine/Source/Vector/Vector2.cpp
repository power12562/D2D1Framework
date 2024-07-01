#include "Vector/Vector2.h"

#include "Framework/WinGameApp.h"
#include "Math/Mathf.h"

#include <math.h>

const Vector2 Vector2::Right{ 1,0 };
const Vector2 Vector2::Left{ -1,0 };
const Vector2 Vector2::Up{ 0, 1 };
const Vector2 Vector2::Down{ 0, -1 };

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(double x, double y)
{
	this->x = (float)x;
	this->y = (float)y;
}

Vector2::Vector2(int x, int y)
{
	this->x = float(x);
	this->y = float(y);
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
	float magnitude = sqrtf(SqrMagnitude());
	return magnitude;
}

Vector2 Vector2::Normalized()
{
	Vector2 normal = Vector2{ float(x / Magnitude()) , float(y / Magnitude()) };
	return normal;
}

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

Vector2 Vector2::operator*(const float scala) const
{
	Vector2 value = Vector2{ this->x, this->y };
	value.x *= scala;
	value.y *= scala;

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

Vector2 Vector2::operator+(const Vector2& other)
{
	Vector2 sum = Vector2{ 0, 0 };
	sum.x = this->x + other.x;
	sum.y = this->y + other.y;

	return sum;
}

Vector2 Vector2::operator-(const Vector2& other)
{
	Vector2 sub = Vector2{ 0, 0 };
	sub.x = this->x - other.x;
	sub.y = this->y - other.y;

	return sub;
}

bool Vector2::operator!=(const Vector2& other)
{
	return (this->x != other.x || this->y != other.y);
}

bool Vector2::operator==(const Vector2& other)
{
	return (this->x == other.x && this->y == other.y);
}


//static:

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

Vector2 Vector2::GetRotatedPoint(const Vector2& point, const float angle, const Vector2& center)
{
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
