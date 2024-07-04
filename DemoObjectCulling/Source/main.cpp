#include "DemoObjectCulling.h"
#include "Framework/WorldManager.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	DemoObjectCulling app;
	app.Initialize(hInstance);
	WorldManager::LoadWorld<Scene1>();
	app.Run();
	app.Uninitialize();

	return 0;
}