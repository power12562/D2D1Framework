#pragma once
#include <string>
class FiniteStateMachine;


/* Derived default

class Derived : public FSMState
{
public:
	Derived(FiniteStateMachine& _owner, const wchar_t* _name) : FSMState(_owner, _name) {}
	virtual ~Derived() override;

  public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

*/

/** FiniteStateMachine에서 사용될 state 추상 클래스*/
class FSMState
{
	friend class FiniteStateMachine;
public:
	FSMState(FiniteStateMachine& _owner, const wchar_t* _name) :
		owner(_owner),
		name(_name)
	{}
	virtual ~FSMState() {}
	const std::wstring& GetName() const { return name; }
protected:
	/** 상태 진입전 실행할 내용*/
	virtual void Enter() {}

	/** 상태 일때 계속 실행할 내용, 전이 조건 검사 (Check Transition Condition) 도 같이 한다.*/
	virtual void Update() {}

	/** 상태 탈출때 실행할 내용*/
	virtual void Exit() {}

	/** 현재 관리하는 FSM컴포넌트*/
	FiniteStateMachine& owner;
private:
	std::wstring name; //상태 이름
};
