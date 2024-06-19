#include "Core/Component/Base/ComponentBase.h"
#include "Core/GameObject/GameObjectBase.h"

ComponentBase::ComponentBase(GameObjectBase& gameObject) :
	gameobject(gameObject)
{

}

ComponentBase::~ComponentBase()
{
	
}


