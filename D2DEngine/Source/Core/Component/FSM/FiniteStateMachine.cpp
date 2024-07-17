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
	if (currState)
	{
		currState->Update();
	}
}

void FiniteStateMachine::SetState(const wchar_t* name)
{
	if (enabled && Transition)
	{
		auto find = stateMap.find(name);
		if (find != stateMap.end())
		{
			if (currState != nullptr)
			{
				currState->Exit();
			}
			currState = find->second;
			currState->Enter();
		}
		else
		{
			assert(!"존재하지 않는 상태 입니다.");
		}
	}
}
