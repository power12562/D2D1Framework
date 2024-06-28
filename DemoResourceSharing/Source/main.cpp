#include "DemoResourceSharing.h"
#include "Framework/SceneManager.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	DemoResourceSharing app;
	app.Initialize(hInstance);
	SceneManager::LoadScene<Scene1>();
	app.Run();
	app.Uninitialize();

	return 0;
}