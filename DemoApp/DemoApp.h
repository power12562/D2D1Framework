#pragma once
#include "Framework/WinGameApp.h"

class DemoApp : public WinGameApp
{
public:
	DemoApp(bool _Debug = false);
	~DemoApp();

	virtual void Update() override;
	virtual void Render() override;

private:
};

