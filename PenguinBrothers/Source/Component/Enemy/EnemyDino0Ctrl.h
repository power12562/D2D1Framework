#pragma once
#include "Core/Component/Base/ComponentBase.h"

class EnemyDino0Ctrl : public ComponentBase
{
	class TextRenderer* stateDebugText;
	class FiniteStateMachine* fsm;
public:
	EnemyDino0Ctrl(GameObjectBase& gameObject);
	virtual ~EnemyDino0Ctrl();

	void SpawnFire();
protected:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

