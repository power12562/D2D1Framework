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
		audioClip.Play(true, SoundSystem::ChannelGroup::music);
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
		DEBUG_WPRINT(L"존재하지 않는 파일 입니다. %s.\n", jsonPath.c_str());	 
		WinGameApp::End();
	}
}
