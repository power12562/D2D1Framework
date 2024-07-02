#pragma once
#include "Vector/Vector2.h"
#include <Windows.h>

struct Bounds
{
	/** �߽� ��ġ*/
	Vector2 center;

	/** ������*/
	Vector2 size;

	/** ������ ����*/
	Vector2 extents;

	/** ���� ��*/
	Vector2 leftTop;

	/** ������ �Ʒ�*/
	Vector2 rightBottom;

	/** Bounds���� AABB�� ��ħ ���� �˻�*/
	bool AABB(const Bounds& other) const;

	/** Bounds�� ȸ���� ����� bounds �� ����*/
	static void GetRotationBounds(Bounds& bounds, const float angle);

	/** Bounds���� AABB�� ��ħ ���� �˻�*/
	static bool AABB(const Bounds& A, const Bounds& B);

};