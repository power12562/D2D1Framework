#pragma once
#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/FSM/FSMState.h"

class EnemyDino0 : public GameObjectBase
{
public:
	EnemyDino0();
	virtual ~EnemyDino0() override;
};


//FSM State 

class EnemyState : public FSMState
{
public:
	EnemyState(FiniteStateMachine& _owner, const wchar_t* _name);
	GameObjectBase* player;
protected:
	class Movement* movement;
	class SpriteAnimationRenderer* animationRenderer;

};

class EnemyIdle : public EnemyState
{
	const float playerTrackingDis = 200.f;
public:
	EnemyIdle(FiniteStateMachine& _owner, const wchar_t* _name) : EnemyState(_owner, _name) {}
protected:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};