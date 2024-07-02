#include "Bounds/Bounds.h"

#include <float.h>
#include <cmath>

void Bounds::GetRotationBounds(Bounds& bounds, const float angle)
{
	Vector2 point[4];
	point[0] = bounds.leftTop;

	point[1].x = bounds.leftTop.x;
	point[1].y = bounds.rightBottom.y;

	point[2].x = bounds.rightBottom.x;
	point[2].y = bounds.leftTop.y;

	point[3] = bounds.rightBottom;

	for (int i = 0; i < 4; i++)
	{
		point[i] = Vector2::GetRotatedPoint(point[i], angle, bounds.center);
	}
	Vector2 min = Vector2{ FLT_MAX, FLT_MAX }, max = Vector2{ -FLT_MAX, -FLT_MAX };
	for (int i = 0; i < 4; i++)
	{
		min.x = (min.x > point[i].x) ? point[i].x : min.x;
		min.y = (min.y > point[i].y) ? point[i].y : min.y;

		max.x = (max.x < point[i].x) ? point[i].x : max.x;
		max.y = (max.y < point[i].y) ? point[i].y : max.y;
	}

	bounds.leftTop.x = min.x;
	bounds.leftTop.y = min.y;
	bounds.rightBottom.x = max.x;
	bounds.rightBottom.y = max.y;

	bounds.size.x = max.x - min.x;
	bounds.size.y = max.y - min.y;

	bounds.extents.x = bounds.size.x * 0.5f;
	bounds.extents.y = bounds.size.y * 0.5f;
}

bool Bounds::AABB(const Bounds& other)
{
	// Check for no overlap conditions
	if (this->rightBottom.x < other.leftTop.x ||  // �����ʿ� ������ ��ĥ���� ����
		this->leftTop.x > other.rightBottom.x ||  // ���ʿ� ������ ��ĥ���� ����
		this->leftTop.y < other.rightBottom.y ||  // �Ʒ��� ������ ��ĥ���� ����
		this->rightBottom.y > other.leftTop.y)	  // ���� ������ ��ĥ���� ����
	{
		return false;
	}
	return true;
}

