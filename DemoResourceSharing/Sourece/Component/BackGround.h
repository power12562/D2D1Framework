#pragma once
#include "Core/Component/Base/ComponentBase.h"

class BackGround : public ComponentBase
{
public:
	BackGround(GameObjectBase& object);
	virtual ~BackGround() override;

protected:
	virtual void Start() override;

};