#include "AnimeEditor.h"
#include "Framework/WorldManager.h"

#include "Source/Scenes/AnimeEditScene.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    AnimeEditor app;
    app.Initialize(hInstance);
    WorldManager::LoadWorld<AnimeEditScene>();
    app.Run();
    app.Uninitialize();
}

AnimeEditor::AnimeEditor()
{
#ifdef _DEBUG
    isDebug = true;
#endif // _DEBUG
    windowName = L"AnimeEditer";
    winClassName = L"ANI_EDIT";
    bgColor = D2D1::ColorF(D2D1::ColorF::White);

}

AnimeEditor::~AnimeEditor()
{

}
