#include "Stage1.h"
#include "Framework/WorldManager.h"

#include "Source/GameObject/Player.h"

Stage1::Stage1()
{
	WorldManager::AddGameObject<Player>(L"Player");
}

Stage1::~Stage1()
{

}
