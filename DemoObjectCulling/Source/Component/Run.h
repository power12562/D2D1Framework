#pragma once
#include "Core/Component/Base/ComponentBase.h"

class Run : public ComponentBase
{
public:
	Run(GameObjectBase& object);
	virtual ~Run() override;

protected:
	virtual void Start() override;
	virtual void Update() override;

};