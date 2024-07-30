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

/** FiniteStateMachine���� ���� state �߻� Ŭ����*/
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
	/** ���� ������ ������ ����*/
	virtual void Enter() {}

	/** ���� �϶� ��� ������ ����, ���� ���� �˻� (Check Transition Condition) �� ���� �Ѵ�.*/
	virtual void Update() {}

	/** ���� Ż�⶧ ������ ����*/
	virtual void Exit() {}

	/** ���� �����ϴ� FSM������Ʈ*/
	FiniteStateMachine& owner;
private:
	std::wstring name; //���� �̸�
};
