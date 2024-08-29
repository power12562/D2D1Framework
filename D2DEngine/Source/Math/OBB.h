#pragma once

class BoxCollider2D;
class Vector2;

namespace OBB
{
	bool CheckOverlap(const BoxCollider2D& a, const BoxCollider2D& b);

	bool CheckOverlap(const BoxCollider2D& a, const Vector2& point);
}