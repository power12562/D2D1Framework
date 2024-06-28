#include "Stage1.h"
#include "Framework/SceneManager.h"

#include "Source/GameObject/Player.h"

Stage1::Stage1()
{
	SceneManager::AddGameObject<Player>(L"Player");

}

Stage1::~Stage1()
{

}
