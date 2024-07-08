#include "FiniteStateMachine.h"
#include "FSMState.h"

#include <cassert>

FiniteStateMachine::FiniteStateMachine(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

FiniteStateMachine::~FiniteStateMachine()
{
	for (auto& state : stateMap)
	{
		delete state.second;
	}
	stateMap.clear();
}

void FiniteStateMachine::Update()
{
	if (currState != nextState)
	{
		if (currState != nullptr)
		{
			currState->Exit();
		}
		currState = nextState;
		currState->Enter();
	}
	else
	{
		currState->Update();
	}
}

void FiniteStateMachine::SetState(const wchar_t* name)
{
	auto find = stateMap.find(name);
	if (find != stateMap.end())
	{
		nextState = find->second;
	}
	else
	{
		assert(!"�������� �ʴ� ���� �Դϴ�.");
	}
}
