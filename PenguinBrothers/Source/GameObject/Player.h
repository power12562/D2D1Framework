#pragma once
#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/FSM/FSMState.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"

class Player : public GameObjectBase
{
public:
	Player();
	virtual ~Player() override;
};
	

//FSMState:

class PlayerState : public  FSMState
{
public:
	PlayerState(FiniteStateMachine& _owner, const wchar_t* _name);
	virtual ~PlayerState() override {};

protected:
	class Movement* movement;
	class SpriteAnimationRenderer* spriteAnimation;
	class PlayerCtrl* playerCtrl;
};

class Spawn : public PlayerState
{
public:
	Spawn(FiniteStateMachine& _owner, const wchar_t* _name) : PlayerState(_owner, _name) {}
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override {}
};


class Idle : public PlayerState
{
public:
	Idle(FiniteStateMachine& _owner, const wchar_t* _name) : PlayerState(_owner, _name) {}
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override {}
};

class Walk : public PlayerState
{
public:
	Walk(FiniteStateMachine& _owner, const wchar_t* _name) : PlayerState(_owner, _name) {}
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

class Duck : public PlayerState
{
public:
	Duck(FiniteStateMachine& _owner, const wchar_t* _name) : PlayerState(_owner, _name) {}
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override {}
};

class Slide : public PlayerState
{
public:
	Slide(FiniteStateMachine& _owner, const wchar_t* _name) : PlayerState(_owner, _name) {}
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

class Attack : public PlayerState
{
public:
	Attack(FiniteStateMachine& _owner, const wchar_t* _name) : PlayerState(_owner, _name) {}
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override {}
};