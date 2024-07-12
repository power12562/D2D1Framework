#include "EditerCtrl.h"
#include <Framework/WorldManager.h>
#include <Framework/TimeSystem.h>
#include <Framework/InputSystem.h>

#include "Source/Scenes/StageEditer.h"

EditerCtrl::EditerCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject) 
{

}


EditerCtrl::~EditerCtrl()
{

}

void EditerCtrl::Start()
{
	world = (StageEditer*)WorldManager::GetCurrentWorld();
}

void EditerCtrl::Update()
{
	using namespace InputSystem;
	if (Input.IsKeyDown(KeyCode::F4))
	{
		world->SaveStageToJson();
	}


}
