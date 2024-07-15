#include "StageScene.h"
#include "Framework/WorldManager.h"
#include "Core/Component/Renderer/SpriteRenderer.h"

#include "Source/GameObject/Player/Player.h"
#include "Source/GameObject/Enemy/EnemyDino0.h"

StageScene::StageScene() : StageEditer(false)
{
	LoadStageToJson();
	SpawnSceneObjects();
}

StageScene::~StageScene()
{

}
