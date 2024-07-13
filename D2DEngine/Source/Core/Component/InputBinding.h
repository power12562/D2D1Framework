#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Framework/InputSystem.h>
#include <unordered_map>
#include <list>

using KeyCode = InputSystem::KeyCode;

class InputBinding : public ComponentBase
{
	friend class WinGameApp;
public:
	InputBinding(GameObjectBase& gameObject);
	virtual ~InputBinding() override;

	/* Ű�� �̸��� �Բ� ���ε� �մϴ�.*/
	void BindKey(const char* name, KeyCode keyCode);
	
	/* ���ε��� Ű�� ���� �մϴ�.*/
	void UnbindKey(const char* name, KeyCode keyCode);

	inline bool IsKey(const char* name) { return isKey[name]; }
	inline bool IsKeyDown(const char* name) { return isKeyDown[name]; }
	inline bool IsKeyUp(const char* name) { return  isKeyUp[name]; }

protected:
	//virtual void Start();
	//virtual void Update();
	//virtual void LateUpdate();
	//virtual void Render();

private:
	std::unordered_map<std::string, std::vector<KeyCode>> bindingMap;

	std::unordered_map<std::string, bool> isKey;
	std::unordered_map<std::string, bool> isKeyDown;
	std::unordered_map<std::string, bool> isKeyUp;
	/* ���ε��� Ű�鿡 bool ���� ������Ʈ �մϴ�. UpdateAllInputBinding()���� �ѹ��� ó���մϴ�.*/
	void UpdateInputBinding();

	std::list<InputBinding*>::iterator myIter;

	/*��� InputBinding ������Ʈ�� ���ε��� Ű�鿡 bool ���� ������Ʈ ���ִ� �Լ�.WinGameApp->Run() ���������� ȣ���մϴ�.*/
	static void UpdateAllInputBinding();

	/* ������ ������Ʈ ����Ʈ*/
	static std::list<InputBinding*> instanceList;

};

