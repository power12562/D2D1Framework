#pragma once
#include "Framework/WinGameApp.h"
#include "Core/Scene/SceneBase.h"

class DemoObjectCulling : public WinGameApp
{
public:
	DemoObjectCulling();
	virtual ~DemoObjectCulling() override;

	virtual void Render() override;

private:

};

class Scene1 : public SceneBase
{
public:
	Scene1();
	virtual ~Scene1() override;

};