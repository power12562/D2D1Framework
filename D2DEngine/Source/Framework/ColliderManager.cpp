#include "ColliderManager.h"
#include <Core/GameObject/Base/GameObjectBase.h>

#include <Core/Component/Collider/Interface/ICollider2DNotify.h>
#include <Core/Component/Collider/Base/ColliderBase.h>

#include <cassert>

std::list<ColliderBase*> ColliderManager::colliderInstanceList;

void ColliderManager::CheckCollision()
{
	for (auto i = colliderInstanceList.begin(); i != colliderInstanceList.end(); ++i)
	{
		auto j = i;
		j++;
		for (; j != colliderInstanceList.end(); j++)
		{
			if ((*i)->isCollide(*j))
			{	  
				size_t StateSize = (*i)->collideStateCurr.size();
				(*i)->collideStateCurr.insert(*j);
				(*j)->collideStateCurr.insert(*i);
				if (StateSize != (*i)->collideStateCurr.size())
				{
					CallEnterEvent(*i, *j);
				}
				else
				{
					CallStayEvent(*i, *j);
				}			
			}
			else
			{
				auto findJ = (*i)->collideStateCurr.find(*j);
				auto findI = (*j)->collideStateCurr.find(*i);
				if (findJ != (*i)->collideStateCurr.end() || findI != (*j)->collideStateCurr.end())
				{
					CallExitEvent(*i, *j);
				}
			}
		}
	}
}

void ColliderManager::CallEnterEvent(ColliderBase* i, ColliderBase* j)
{
	if (i->isTrigger || j->isTrigger)
	{
		for (auto& event : i->gameObject.collider2DNotifyTable)
		{
			event.second->OnTriggerEnter2D(&j->gameObject);

		}
		for (auto& event : j->gameObject.collider2DNotifyTable)
		{
			event.second->OnTriggerEnter2D(&i->gameObject);
		}
	}
	else
	{

		for (auto& event : i->gameObject.collider2DNotifyTable)
		{
			event.second->OnCollisionEnter2D(&j->gameObject);
		}

		for (auto& event : j->gameObject.collider2DNotifyTable)
		{
			event.second->OnCollisionEnter2D(&i->gameObject);
		}
	}
}

void ColliderManager::CallStayEvent(ColliderBase* i, ColliderBase* j)
{
	if (i->isTrigger || j->isTrigger)
	{
		for (auto& event : i->gameObject.collider2DNotifyTable)
		{
			event.second->OnTriggerStay2D(&j->gameObject);

		}
		for (auto& event : j->gameObject.collider2DNotifyTable)
		{
			event.second->OnTriggerStay2D(&i->gameObject);
		}
	}
	else
	{

		for (auto& event : i->gameObject.collider2DNotifyTable)
		{
			event.second->OnCollisionStay2D(&j->gameObject);
		}

		for (auto& event : j->gameObject.collider2DNotifyTable)
		{
			event.second->OnCollisionStay2D(&i->gameObject);
		}
	}
}

void ColliderManager::CallExitEvent(ColliderBase* i, ColliderBase* j)
{
	if (i->isTrigger || j->isTrigger)
	{
		for (auto& event : i->gameObject.collider2DNotifyTable)
		{
			event.second->OnTriggerExit2D(&j->gameObject);

		}
		for (auto& event : j->gameObject.collider2DNotifyTable)
		{
			event.second->OnTriggerExit2D(&i->gameObject);
		}
	}
	else
	{

		for (auto& event : i->gameObject.collider2DNotifyTable)
		{
			event.second->OnCollisionExit2D(&j->gameObject);
		}

		for (auto& event : j->gameObject.collider2DNotifyTable)
		{
			event.second->OnCollisionExit2D(&i->gameObject);
		}
	}	

	i->collideStateCurr.erase(j);
	j->collideStateCurr.erase(i);
}
