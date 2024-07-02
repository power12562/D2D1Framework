#pragma once
#include "Core/Component/Base/ComponentBase.h"

#include <list>
#include <string>

class Run : public ComponentBase
{
public:
	Run(GameObjectBase& object);
	virtual ~Run() override;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	int instanceCount = 1;
	std::list<std::wstring> runList;
};