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
	bounds.leftTop.y = max.y;
	bounds.rightBottom.x = max.x;
	bounds.rightBottom.y = min.y;

	bounds.size.x = max.x - min.x;
	bounds.size.y = max.y - min.y;

	bounds.extents.x = bounds.size.x * 0.5f;
	bounds.extents.y = bounds.size.y * 0.5f;
}

bool Bounds::AABB(const Bounds& A, const Bounds& B)
{
	return A.AABB(B);
}

bool Bounds::PointCollision(const Bounds& a, const Vector2& p)
{
	return a.PointCollision(p);
}

bool Bounds::AABB(const Bounds& other) const
{
	// Check for no overlap conditions
	if (this->rightBottom.x < other.leftTop.x ||  // 오른쪽에 있으면 겹칠수가 없음
		this->leftTop.x > other.rightBottom.x ||  // 왼쪽에 있으면 겹칠수가 없음
		this->leftTop.y < other.rightBottom.y ||  // 아래에 있으면 겹칠수가 없음
		this->rightBottom.y > other.leftTop.y)	  // 위에 있으면 겹칠수가 없음
	{
		return false;
	}
	return true;
}

bool Bounds::PointCollision(const Vector2& p) const
{
	// Check for no overlap conditions
	if (this->rightBottom.x < p.x ||  // 오른쪽에 있으면 겹칠수가 없음
		this->leftTop.x > p.x ||  // 왼쪽에 있으면 겹칠수가 없음
		this->leftTop.y < p.y ||  // 아래에 있으면 겹칠수가 없음
		this->rightBottom.y > p.y)	  // 위에 있으면 겹칠수가 없음
	{
		return false;
	}
	return true;
}

