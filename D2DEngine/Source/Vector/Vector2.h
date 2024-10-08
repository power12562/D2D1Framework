#pragma once
#include <d2d1.h>
#include <vector>
#include <memory>

class Vector3;
class Vector2
{
public:
	float x;
	float y;

	explicit Vector2(float x = 0, float y = 0);
	explicit Vector2(std::vector<float>&& vec);
	explicit Vector2(const Vector3& vector3);

	virtual ~Vector2() = default;

	Vector2(const Vector2& other);

	float Magnitude() const;
	float SqrMagnitude() const;

	Vector2 Normalized() const;
	void Normalize();

	Vector2& operator=(const Vector2& other);
	/*Json으로 읽은 position 값을 초기화 하기 위한 대입 연산자.*/
	Vector2& operator=(const std::vector<float>& vec);
	Vector2& operator=(std::vector<float>&& vec);

	Vector2 operator*(const float scala) const;
	Vector2 operator/(const float scala) const;
	Vector2& operator*=(const float scala);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator-() const;
	bool operator!=(const Vector2& other) const;
	bool operator==(const Vector2& other) const;
	explicit operator Vector3();

	//static:

	/** Zero Vector2(0, 0) */
	static const Vector2 Zero;
	/** Right Vector2(1, 0) */
	static const Vector2 Right; 
	/** Left Vector2(-1, 0) */
	static const Vector2 Left;
	/** Up Vector2(0, 1) */
	static const Vector2 Up;
	/** Down Vector2(0, -1) */
	static const Vector2 Down;

	/**내적 */
	static float Dot(const Vector2& lhs, const Vector2& rhs);

	/**외적 */
	static float Cross(const Vector2& lhs, const Vector2& rhs);

	/** 해당 매트릭스의 sclaeX 요소 추출하기*/
	static Vector2 GetScaleFromMatrix(const D2D1_MATRIX_3X2_F& matrix);

	/** 화면 좌표로 변환*/
	static Vector2 WorldToScreenPoint(const Vector2& pos);

	/** 선형 보간*/
	static Vector2 Lerp(const Vector2& startPos, const Vector2& endPos, const float t);

	/** 베지에 곡선*/
	static Vector2 BezierCurve(const Vector2& startPos, const Vector2& middlePos, const Vector2& endPos, const float t);

	/** 라그랑주 보간법. 시간 복잡도 : O(pointArraySize^2)*/
	static Vector2 LagranCurve(float x, Vector2* pointArray, int pointArraySize);

	/** Vertex 회전 위치 리턴*/
	static Vector2 GetRotatedPoint(const Vector2& point, const float angle, const Vector2& center);
	
};