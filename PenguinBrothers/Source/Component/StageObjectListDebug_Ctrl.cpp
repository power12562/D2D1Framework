#include "StageObjectListDebug_Ctrl.h"
#include <Framework/WorldManager.h>

#include <Core/GameObject/Base/GameObjectBase.h>
#include <Core/Component/Renderer/TextRenderer.h>

#include <list>

StageObjectListDebug_Ctrl::StageObjectListDebug_Ctrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

StageObjectListDebug_Ctrl::~StageObjectListDebug_Ctrl()
{
}

void StageObjectListDebug_Ctrl::Start()
{
	textrenderer = &gameObject.AddComponent<TextRenderer>();
	textrenderer->SetFont(L"Consolas");
	textrenderer->TextColor = D2D1::ColorF(D2D1::ColorF::Blue);
	textrenderer->Size = 20.f;
}

void StageObjectListDebug_Ctrl::Update()
{
	const std::list<GameObjectBase*>& list = WorldManager::GetCurrentObjList();
	std::wstring nameList;
	for (auto& i : list)
	{
		nameList += i->name;
		nameList += L"\n";
	}
	textrenderer->Text = nameList;
}


