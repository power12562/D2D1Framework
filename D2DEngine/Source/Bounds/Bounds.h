#pragma once
#include "Vector/Vector2.h"
#include <Windows.h>
#include <float.h>

struct Bounds
{
	/** 중심 위치*/
	Vector2 center{ -FLT_MAX, -FLT_MAX };

	/** 사이즈*/
	Vector2 size;

	/** 사이즈 절반*/
	Vector2 extents;

	/** 왼쪽 위*/
	Vector2 leftTop{ -FLT_MAX, -FLT_MAX };;

	/** 오른쪽 아래*/
	Vector2 rightBottom{ -FLT_MAX, -FLT_MAX };;

	/** Bounds끼리 AABB로 겹침 여부 검사*/
	bool AABB(const Bounds& other) const;

	/** Bounds와 점의 겹침 여부 검사*/
	bool PointCollision(const Vector2& p) const;

	/** Bounds에 회전이 적용된 bounds 값 리턴*/
	static void GetRotationBounds(Bounds& bounds, const float angle);

	/** Bounds끼리 AABB로 겹침 여부 검사*/
	static bool AABB(const Bounds& A, const Bounds& B);

	/** Bounds와 점의 겹침 여부 검사*/
	static bool PointCollision(const Bounds& a, const Vector2& p);

};