#include "GameManagerCtrl.h"
#include <Core/Component/AudioClip.h>

#include <filesystem>
#include <string>
#include <Framework/InputSystem.h>
#include <Framework/WinGameApp.h>
#include <Framework/WorldManager.h>
#include <Utility/Debug.h>


int GameManagerCtrl::CurrentStage = 1;
int	GameManagerCtrl::EnemyCount = -1;

using namespace InputSystem;
GameManagerCtrl::~GameManagerCtrl()
{
	EnemyCount = -1;
}

void GameManagerCtrl::Start()
{
	bgm = WorldManager::FindGameObject(L"BGM");
	if (bgm == nullptr)
	{
		bgm = WorldManager::AddGameObject(L"BGM");
		AudioClip& audioClip = bgm->AddComponent<AudioClip>();
		audioClip.LoadAudio(L"Resource/level.mp3");
		audioClip.group = SoundSystem::ChannelGroup::music;
		audioClip.Play(true);
		WorldManager::DontDestroyOnLoad(bgm);
	}
}

void GameManagerCtrl::Update()
{
	if(Input.IsKeyDown(KeyCode::F1))
	{
		LoadNextStage();
	}

	//DEBUG_PRINT("Enemy : %d\n", GameManagerCtrl::EnemyCount);
}

void GameManagerCtrl::LoadNextStage()
{
	if (gameObject.Find(L"editer"))
		return;

	std::wstring jsonPath = L"Resource/Stage/Stage" + std::to_wstring(CurrentStage + 1) + L".json";
	if (std::filesystem::exists(jsonPath.c_str()))
	{
		CurrentStage++;
		WorldManager::LoadWorldToJson(jsonPath.c_str());
	}
	else
	{
		CurrentStage = 1;
		jsonPath = L"Resource/Stage/Stage" + std::to_wstring(CurrentStage) + L".json";
		WorldManager::LoadWorldToJson(jsonPath.c_str());
	}
}
