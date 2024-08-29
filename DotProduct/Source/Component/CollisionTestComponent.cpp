#include "CollisionTestComponent.h"
#include <Framework/TimeSystem.h>
#include <Framework/WorldManager.h>
#include <Framework/InputSystem.h>
#include <Utility/Debug.h>
#include <Math/OBB.h>

#include <Core/Component/Collider/SpriteCollider2D.h>
#include <Core/Component/Collider/BoxCollider2D.h>
#include <Core/Component/Rigidbody2D.h>

using namespace TimeSystem;
using namespace InputSystem;

CollisionTestComponent::CollisionTestComponent(GameObjectBase& gameObject)
	: ComponentBase(gameObject), ICollider2DNotify(this)
{

}

CollisionTestComponent::~CollisionTestComponent()
{

}

void CollisionTestComponent::Start()
{
	GameObjectBase* testObj = WorldManager::AddGameObject(L"test");
	testBox = &testObj->AddComponent<BoxCollider2D>();
	testBox->isDrawCollider = true;
	testBox->ColliderSize = {100, 100};
	testBox->transform.rotation = 25.f;

	boxCollider = &AddComponent<SpriteCollider2D>();
	boxCollider->isDrawCollider = true;
	boxCollider->isTrigger = true;
	//boxCollider->ColliderSize = { 220, 229 };

	rb = &AddComponent<Rigidbody2D>();
	rb->useGravity = false;
}

void CollisionTestComponent::Update()
{
	//transform.rotation += 45 * Time.GetDeltatime();
	const MouseState& mouse = Input.GetMouseState();
	if (mouse.isLeftClickDown)
	{
		if (OBB::CheckOverlap(*testBox, mouse.GetWorldPos()))
		{
			//DEBUG_PRINT("Click!\n");
		}
	}
}

void CollisionTestComponent::OnTriggerStay2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	//DEBUG_PRINT("Stay\n");
}

void CollisionTestComponent::OnTriggerExit2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	//system("cls");
}
