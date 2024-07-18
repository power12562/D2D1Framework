#pragma once
#include <Vector/Vector2.h>
class ColliderBase;

namespace Ray
{
	/** 전달받은 위치에 ray를 발사해 Collider를 감지합니다.*/
	ColliderBase* ShootRayFromPosition(const Vector2& position);
};