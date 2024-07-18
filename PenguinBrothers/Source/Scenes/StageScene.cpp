#include "StageScene.h"
#include "Framework/WorldManager.h"
#include "Core/Component/Renderer/SpriteRenderer.h"

#include "Source/GameObject/Player/Player.h"
#include "Source/GameObject/Enemy/EnemyDino0.h"


StageScene::StageScene() : StageEditer([](StageScene* asd)->bool { 
	asd->stagePath = L"Resource/Stage/Stage1.json"; 
	return false; }(this))
{

}

StageScene::~StageScene()
{

}
