#include "ColliderManager.h"
#include <Math/Mathf.h>
#include <Core/GameObject/Base/GameObjectBase.h>

#include <Core/Component/Collider/Interface/ICollider2DNotify.h>
#include <Core/Component/Collider/Base/ColliderBase.h>
#include <Core/Component/Rigidbody2D.h>

#include <cassert>

std::list<ColliderBase*> ColliderManager::colliderInstanceList;

void ColliderManager::DeleteCollider(ColliderBase* collider)
{
	for (auto& j : collider->collideStateCurr)
	{
		if (j == collider)
		{
			CallExitEvent(collider, j);
			j->collideStateCurr.erase(collider);
			break;
		}	
	}	
	collider->collideStateCurr.clear();
}

void ColliderManager::CheckCollision()
{
	for (auto i = colliderInstanceList.begin(); i != colliderInstanceList.end(); ++i)
	{
		if ((*i)->gameObject.enable == false)
			continue;

		auto j = i;
		++j;	
		for (; j != colliderInstanceList.end(); ++j)
		{
			bool isException = false;
			for (auto& excTag : (*i)->ExceptionTag)
			{
				if (excTag == (*j)->gameObject.tag)
				{
					isException = true;
					break;
				}
			}
			if (isException == false)
			{
				for (auto& excTag : (*j)->ExceptionTag)
				{
					if (excTag == (*i)->gameObject.tag)
					{
						isException = true;
						break;
					}
				}
			}
			if ((*j)->gameObject.enable == false || isException)
				continue;

			if (((*i)->gameObject.pRigidbody && (*i)->gameObject.pRigidbody->enabled) ||
				((*j)->gameObject.pRigidbody && (*j)->gameObject.pRigidbody->enabled))			
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
					bool find = false;
					if (findJ != (*i)->collideStateCurr.end())
					{
						(*i)->collideStateCurr.erase(*j);
						find = true;
					}
					if (findI != (*j)->collideStateCurr.end())
					{
						(*j)->collideStateCurr.erase(*i);
						find = true;
					}
					if (find)
					{
						CallExitEvent(*i, *j);
					}
				}
			}		
		}
	}	
}

void ColliderManager::CallEnterEvent(ColliderBase* i, ColliderBase* j)
{
	if (i->isTrigger || j->isTrigger)
	{
		if(i->gameObject.enable == true)
		{
			for (auto& event : i->gameObject.collider2DNotifyTable)
			{
				event.second->OnTriggerEnter2D(i, j);

			}
		}
		if (j->gameObject.enable == true)
		{
			for (auto& event : j->gameObject.collider2DNotifyTable)
			{
				event.second->OnTriggerEnter2D(j, i);
			}
		}	
	}
	else
	{
		if(i->gameObject.enable == true)
		{
			if (i->gameObject.pRigidbody)
			{
				i->gameObject.pRigidbodyEvent->OnCollisionEnter2D(i, j);
			}
			for (auto& event : i->gameObject.collider2DNotifyTable)
			{
				event.second->OnCollisionEnter2D(i, j);
			}
		}
		if (j->gameObject.enable == true)
		{
			if (j->gameObject.pRigidbody)
			{
				j->gameObject.pRigidbodyEvent->OnCollisionEnter2D(j, i);
			}
			for (auto& event : j->gameObject.collider2DNotifyTable)
			{
				event.second->OnCollisionEnter2D(j, i);
			}
		}		
	}
}

void ColliderManager::CallStayEvent(ColliderBase* i, ColliderBase* j)
{
	if (i->isTrigger || j->isTrigger)
	{
		if(i->gameObject.enable == true)
		{
			for (auto& event : i->gameObject.collider2DNotifyTable)
			{
				event.second->OnTriggerStay2D(i, j);
			}
		}
		if(j->gameObject.enable == true)
		{
			for (auto& event : j->gameObject.collider2DNotifyTable)
			{
				event.second->OnTriggerStay2D(j, i);
			}
		}
	}
	else
	{
		if (i->gameObject.enable == true)
		{
			if (i->gameObject.pRigidbody)
			{
				i->gameObject.pRigidbodyEvent->OnCollisionStay2D(i, j);
			}
			for (auto& event : i->gameObject.collider2DNotifyTable)
			{
				event.second->OnCollisionStay2D(i, j);
			}
		}
		if (j->gameObject.enable == true)
		{
			if (j->gameObject.pRigidbody)
			{
				j->gameObject.pRigidbodyEvent->OnCollisionStay2D(j, i);
			}
			for (auto& event : j->gameObject.collider2DNotifyTable)
			{
				event.second->OnCollisionStay2D(j, i);
			}
		}
	}
}

void ColliderManager::CallExitEvent(ColliderBase* i, ColliderBase* j)
{
	if (i->isTrigger || j->isTrigger)
	{
		if (i->gameObject.enable == true)
		{
			for (auto& event : i->gameObject.collider2DNotifyTable)
			{
				event.second->OnTriggerExit2D(i, j);

			}
		}
		if (j->gameObject.enable == true)
		{
			for (auto& event : j->gameObject.collider2DNotifyTable)
			{
				event.second->OnTriggerExit2D(j, i);
			}
		}	
	}
	else
	{
		if (i->gameObject.enable == true)
		{
			if (i->gameObject.pRigidbody)
			{
				i->gameObject.pRigidbodyEvent->OnCollisionExit2D(i, j);
			}
			for (auto& event : i->gameObject.collider2DNotifyTable)
			{
				event.second->OnCollisionExit2D(i, j);
			}
		}
		if (j->gameObject.enable == true)
		{
			if (j->gameObject.pRigidbody)
			{
				j->gameObject.pRigidbodyEvent->OnCollisionExit2D(j, i);
			}
			for (auto& event : j->gameObject.collider2DNotifyTable)
			{
				event.second->OnCollisionExit2D(j, i);
			}
		}
	}	
}
