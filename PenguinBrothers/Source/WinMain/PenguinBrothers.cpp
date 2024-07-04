#include "PenguinBrothers.h"
#include "Framework/WorldManager.h"

#include "Source/Scenes/Stage1.h"
#include "Source/Scenes/AnimeEditScene.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    PenguinBrothers app;
    app.Initialize(hInstance);
    WorldManager::LoadWorld<AnimeEditScene>();
    app.Run();
    app.Uninitialize();
}

PenguinBrothers::PenguinBrothers()
{
#ifdef _DEBUG
    isDebug = true;
#endif // _DEBUG
    windowName = L"PenguinBrothers";
    winClassName = L"PenguinBro";
    bgColor = D2D1::ColorF(D2D1::ColorF::White);

}

PenguinBrothers::~PenguinBrothers()
{

}
