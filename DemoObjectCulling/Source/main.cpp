#include "DemoObjectCulling.h"
#include "Framework/SceneManager.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	DemoObjectCulling app;
	app.Initialize(hInstance);
	SceneManager::LoadScene<Scene1>();
	app.Run();
	app.Uninitialize();

	return 0;
}