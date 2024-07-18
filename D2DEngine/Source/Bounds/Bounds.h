#pragma once
#include "Vector/Vector2.h"
#include <Windows.h>
#include <float.h>

struct Bounds
{
	/** �߽� ��ġ*/
	Vector2 center{ -FLT_MAX, -FLT_MAX };

	/** ������*/
	Vector2 size;

	/** ������ ����*/
	Vector2 extents;

	/** ���� ��*/
	Vector2 leftTop{ -FLT_MAX, -FLT_MAX };;

	/** ������ �Ʒ�*/
	Vector2 rightBottom{ -FLT_MAX, -FLT_MAX };;

	/** Bounds���� AABB�� ��ħ ���� �˻�*/
	bool AABB(const Bounds& other) const;

	/** Bounds�� ���� ��ħ ���� �˻�*/
	bool PointCollision(const Vector2& p) const;

	/** Bounds�� ȸ���� ����� bounds �� ����*/
	static void GetRotationBounds(Bounds& bounds, const float angle);

	/** Bounds���� AABB�� ��ħ ���� �˻�*/
	static bool AABB(const Bounds& A, const Bounds& B);

	/** Bounds�� ���� ��ħ ���� �˻�*/
	static bool PointCollision(const Bounds& a, const Vector2& p);

};