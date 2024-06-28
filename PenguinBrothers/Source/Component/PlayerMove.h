#pragma once
#include "Core/Component/Base/ComponentBase.h"

class PlayerMove : public ComponentBase
{
public:
	PlayerMove(GameObjectBase& gameObject);
	virtual ~PlayerMove();

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:
	float moveSpeed;

};