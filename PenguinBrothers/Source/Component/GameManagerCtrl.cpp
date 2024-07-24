#include "GameManagerCtrl.h"

#include <filesystem>
#include <string>
#include <Framework/InputSystem.h>
#include <Framework/WorldManager.h>
#include <Utility/Debug.h>


int GameManagerCtrl::CurrentStage = 1;
using namespace InputSystem;
GameManagerCtrl::~GameManagerCtrl()
{
}

void GameManagerCtrl::Start()
{
	

}

void GameManagerCtrl::Update()
{
	if(Input.IsKeyDown(KeyCode::F1))
	{
		std::wstring jsonPath = L"Resource/Stage/Stage" + std::to_wstring(CurrentStage + 1) + L".json";
		if (std::filesystem::exists(jsonPath.c_str()))
		{
			CurrentStage++;
			WorldManager::LoadWorldToJson(jsonPath.c_str());
		}	
		else
		{
			DEBUG_WPRINT(L"�������� �ʴ� ���� �Դϴ�. %s.\n", jsonPath.c_str());
		}
	}


}
