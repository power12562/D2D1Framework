#include "Core/Component/Base/ComponentBase.h"
#include <Core/Component/Transform.h>

ComponentBase::ComponentBase(GameObjectBase& gameObject) :
	gameObject(gameObject)
{

}

ComponentBase::~ComponentBase()
{

}

Transform& ComponentBase::GetTransform()
{
	return gameObject.GetTransform();
}

void ComponentBase::Start()
{

}

void ComponentBase::Update()
{

}

void ComponentBase::LateUpdate()
{

}

void ComponentBase::Render()
{

}



