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
	static GameObjectBase* player;
protected:
	float trackingDis;
	float attackDis;
	class Movement* movement;
	class SpriteAnimationRenderer* animationRenderer;
};

class EnemySpawn : public EnemyState
{
public:
	EnemySpawn(FiniteStateMachine& _owner, const wchar_t* _name) : EnemyState(_owner, _name) {}
protected:
	virtual void Enter() override {}
	virtual void Update() override;
	virtual void Exit() override {}
};

class EnemyIdle : public EnemyState
{
public:
	EnemyIdle(FiniteStateMachine& _owner, const wchar_t* _name) : EnemyState(_owner, _name) {}
protected:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override {}
};

class EnemyTracking : public EnemyState
{
	Vector2 dir;
public:
	EnemyTracking(FiniteStateMachine& _owner, const wchar_t* _name) : EnemyState(_owner, _name) {}
protected:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override {}
};

class EnemyAttack : public EnemyState
{
	class EnemyDino0Ctrl* dinoCtrl = nullptr;
	bool attackSpawn;
public:
	EnemyAttack(FiniteStateMachine& _owner, const wchar_t* _name);
protected:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override {}

};