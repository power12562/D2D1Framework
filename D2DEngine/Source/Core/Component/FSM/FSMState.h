#pragma once
#include <string>

class FiniteStateMachine;

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
	virtual void Enter() = 0;

	/** ���� �϶� ��� ������ ����, ���� ���� �˻� (Check Transition Condition) �� ���� �Ѵ�.*/
	virtual void Update() = 0;

	/** ���� Ż�⶧ ������ ����*/
	virtual void Exit() = 0;

	/** ���� �����ϴ� FSM������Ʈ*/
	FiniteStateMachine& owner;
private:
	std::wstring name; //���� �̸�
};
