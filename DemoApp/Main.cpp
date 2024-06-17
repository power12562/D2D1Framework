#include "DemoApp.h"

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
#ifdef _DEBUG
	DemoApp App(true);
#else 
	DemoApp App(false);
#endif
	App.Initialize(hInstance);
	App.Run();
	App.Uninitialize();

	return EXIT_SUCCESS;
}