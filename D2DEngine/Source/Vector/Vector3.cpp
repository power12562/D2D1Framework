#include <Vector/Vector3.h>
#include <Vector/Vector2.h>

const Vector3 Vector3::Zero{ 0,0,0 };
const Vector3 Vector3::Right{ 1,0,0 };
const Vector3 Vector3::Left{ -1,0,0 };
const Vector3 Vector3::Up{ 0, 1,0 };
const Vector3 Vector3::Down{ 0, -1,0 };
const Vector3 Vector3::Front{ 0,0,1 };
const Vector3 Vector3::Back{ 0,0,-1 };

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float Vector3::SqrMagnitude() const
{
	return x * x  + y * y  + z * z;
}

float Vector3::Magnitude() const
{
	return sqrtf(SqrMagnitude());
}

Vector3 Vector3::Normalized() const
{
	float magnitude = Magnitude();
	if (fabs(magnitude) > std::numeric_limits<float>::epsilon())
	{
		Vector3 normal = Vector3{ float(x / magnitude) , float(y / magnitude), float(z / magnitude)};
		return normal;
	}
	return Vector3{};
}

Vector3& Vector3::operator=(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

Vector3 Vector3::operator*(const float scala) const
{
	Vector3 value = Vector3{ this->x, this->y, this->z};
	value.x *= scala;
	value.y *= scala;
	value.z *= scala;

	return value;
}

Vector3 Vector3::operator/(const float scala) const
{
	Vector3 value = Vector3{ this->x, this->y, this->z };
	value.x /= scala;
	value.y /= scala;
	value.z /= scala;

	return value;
}

Vector3& Vector3::operator*=(const float scala)
{
	this->x *= scala;
	this->y *= scala;
	this->z *= scala;

	return *this;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	Vector3 sum = Vector3{ 0, 0, 0 };
	sum.x = this->x + other.x;
	sum.y = this->y + other.y;
	sum.z = this->z + other.z;

	return sum;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	Vector3 sub = Vector3{ 0, 0, 0 };
	sub.x = this->x - other.x;
	sub.y = this->y - other.y;
	sub.z = this->z - other.z;

	return sub;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-this->x, -this->y, -this->z);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return (
		this->x != other.x || 
		this->y != other.y || 
		this->z != other.z
		);
}

bool Vector3::operator==(const Vector3& other) const
{
	return (
		this->x == other.x && 
		this->y == other.y &&
		this->z == other.z
		);
}

Vector3::operator Vector2()
{
	return Vector2{ this->x, this->y };
}

float Vector3::Dot(Vector3 lhs, Vector3 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs)
{
	float x = lhs.y * rhs.z - lhs.z * rhs.y;
	float y = lhs.z * rhs.x - lhs.x * rhs.z;
	float z = lhs.x * rhs.y - lhs.y * rhs.x;

	return Vector3(x, y, z);
}
