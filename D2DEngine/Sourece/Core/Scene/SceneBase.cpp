#include "SceneBase.h"
#include "Core/GameObject/GameObjectBase.h"

SceneBase::SceneBase()
{

}

SceneBase::~SceneBase()
{
	if (!gameObjectList.empty())
	{
		for (auto& item : gameObjectList)
		{
			delete item;
		}
	}
}
