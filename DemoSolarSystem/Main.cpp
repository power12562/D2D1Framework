#include "DemoSolarSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    DemoSolarSystem demoApp(hInstance);
    demoApp.Run();
    demoApp.Uninitialize();

    return 0;
}