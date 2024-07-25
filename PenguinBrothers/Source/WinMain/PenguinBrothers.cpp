#include "PenguinBrothers.h"
#include "Framework/WorldManager.h"
#include "Source/Scenes/StageEditer.h"

#include <Framework/GameObjectFactory.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    PenguinBrothers app;
    app.Initialize(hInstance);
    WorldManager::LoadWorldToJson(L"Resource/Stage/EditerFile/New.json");
    //WorldManager::LoadWorldToJson(L"Resource/Stage/Stage1.json");
    app.Run();
    app.Uninitialize();
}

PenguinBrothers::PenguinBrothers()
{
#ifdef _DEBUG
    isDebug = true;
#endif // _DEBUG
    windowName = L"Penguin Brothers";
    winClassName = L"PenguinBro";
    windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    bgColor = D2D1::ColorF(D2D1::ColorF::White);
    SetClientSize({ 1196, 896 });
}

PenguinBrothers::~PenguinBrothers()
{

}
