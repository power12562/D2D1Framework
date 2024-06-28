#include "PenguinBrothers.h"
#include "Framework/SceneManager.h"

#include "Source/Scenes/Stage1.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    PenguinBrothers app;
    app.Initialize(hInstance);
    SceneManager::LoadScene<Stage1>();
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
