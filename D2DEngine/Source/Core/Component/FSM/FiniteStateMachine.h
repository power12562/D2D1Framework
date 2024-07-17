#pragma once
#include "Core/Component/Base/ComponentBase.h"

#include <map>
#include <string>

class FSMState;
class FiniteStateMachine : public ComponentBase
{
public:
	FiniteStateMachine(GameObjectBase& gameObject);
	virtual ~FiniteStateMachine() override;

	template<typename T> void CreateState(const wchar_t* name);
	void SetState(const wchar_t* name);

	/** 현재 상태*/
	const FSMState* GetCurrState() { return currState; }

	/** 전이 가능 여부*/
	bool Transition = true;
protected:
	FSMState* currState = nullptr;  // 현재 상태	

	std::map<std::wstring, FSMState*> stateMap;	// 생성된 FSMState들을 저장하는 컨테이너

	virtual void Update() override;

};

template<typename T>
inline void FiniteStateMachine::CreateState(const wchar_t* name)
{
	static_assert(std::is_base_of<FSMState, T>::value, "Is not FSMState");

	T* newState = new T(*this, name);
	stateMap[name] = newState;
}
