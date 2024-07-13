#include "InputBinding.h"

std::list<InputBinding*> InputBinding::instanceList;

InputBinding::InputBinding(GameObjectBase& gameObject) : ComponentBase(gameObject) 
{
	instanceList.push_back(this);
	myIter = std::prev(instanceList.end());
}

InputBinding::~InputBinding()
{
	instanceList.erase(myIter);
}

void InputBinding::BindKey(const char* name, KeyCode keyCode)
{
	auto findIter = bindingMap.find(name);
	if (findIter != bindingMap.end())
	{
		for (auto& code : findIter->second)  //중복 방지
		{
			if (code == keyCode)
				return;
		}	
	}
	bindingMap[name].push_back(keyCode);
}

void InputBinding::UnbindKey(const char* name, KeyCode keyCode)
{
	auto findIter = bindingMap.find(name);
	if (findIter != bindingMap.end())
	{
		for (auto Iter = findIter->second.begin(); Iter != findIter->second.end(); Iter++)
		{
			if (*Iter == keyCode)
			{
				findIter->second.erase(Iter);
				return;
			}
		}
	}
}

void InputBinding::UpdateInputBinding()
{
	for (auto& keyList : bindingMap)
	{
		isKey[keyList.first] = false;
		isKeyDown[keyList.first] = false;
		isKeyUp[keyList.first] = false;
		for (auto& keyCode : keyList.second)
		{
			isKey[keyList.first] |= InputSystem::Input.IsKey(keyCode);
			isKeyDown[keyList.first] |= InputSystem::Input.IsKeyDown(keyCode);
			isKeyUp[keyList.first] |= InputSystem::Input.IsKeyUp(keyCode);
		}
	}
}

void InputBinding::UpdateAllInputBinding()
{
	for (auto& instance : instanceList)
	{
		if (instance->enabled)
		{
			instance->UpdateInputBinding();
		}
	}	
}