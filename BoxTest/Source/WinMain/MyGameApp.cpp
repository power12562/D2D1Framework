#include "MyGameApp.h"

#include <Framework/WorldManager.h>
#include <Source/Scenes/World1.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    MyGameApp app;
    app.Initialize(hInstance); 
    WorldManager::LoadWorld<World1>();
    app.Run();
    app.Uninitialize();
}

MyGameApp::MyGameApp()
{
#ifdef _DEBUG
    isDebug = true;
#endif // _DEBUG
    SetClientSize({ 1920, 1080 });
    windowName = L"GameApp";
    winClassName = L"GAME_APP";
    bgColor = D2D1::ColorF(D2D1::ColorF::Black);
}

MyGameApp::~MyGameApp()
{
}
