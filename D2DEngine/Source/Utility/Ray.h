#pragma once
#include <Vector/Vector2.h>
class ColliderBase;

namespace Ray
{
	/** ���޹��� ��ġ�� ray�� �߻��� Collider�� �����մϴ�.*/
	ColliderBase* ShootRayFromPosition(const Vector2& position);
};