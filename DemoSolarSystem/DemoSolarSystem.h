#pragma once
#include "Framework/WinGameApp.h"
#include <vector>

class DemoSolarSystem : public WinGameApp
{
public:
	DemoSolarSystem(HINSTANCE hinstance);
	~DemoSolarSystem();

	virtual void Update() override;
	virtual void Render() override;

private:
	std::vector<class GameObjectBase*> gameObjectList;
};

