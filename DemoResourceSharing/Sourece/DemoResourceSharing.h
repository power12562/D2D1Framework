#pragma once
#include "Framework/WinGameApp.h"
#include "Core/Scene/SceneBase.h"

class DemoResourceSharing : public WinGameApp
{
public:
	DemoResourceSharing();
	virtual ~DemoResourceSharing() override;

private:


};

class Scene1 : public SceneBase
{
public:
	Scene1();
	virtual ~Scene1() override;

};