#include "Movement.h"
#include "Framework/TimeSystem.h"

#include "Core/GameObject/Base/GameObjectBase.h"


Movement::Movement(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	direction = Vector2::Right;
	speed = 0.f;
}

Movement::~Movement()
{

}


void Movement::Update()
{
	using namespace TimeSystem;

	gameObject.transform.position += direction * speed * Time.GetDeltatime();
}
