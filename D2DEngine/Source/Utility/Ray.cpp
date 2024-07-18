#include "Ray.h"
#include <Framework/WorldManager.h>

#include <Core/Component/Collider/Base/ColliderBase.h>

namespace Ray
{
	ColliderBase* Ray::ShootRayFromPosition(const Vector2& position)
	{
		auto& objList = WorldManager::GetCurrentObjList();
		for (auto iter = objList.rbegin(); iter != objList.rend(); ++iter)
		{
			for (auto& collider : (*iter)->colliderList)
			{
				if (collider->isCollide(position))
				{
					return collider;
				}
			}		
		}
		return nullptr;
	}
};