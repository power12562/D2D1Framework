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

	/* 키를 이름과 함께 바인딩 합니다.*/
	void BindKey(const char* name, KeyCode keyCode);
	
	/* 바인딩된 키를 제거 합니다.*/
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
	/* 바인딩된 키들에 bool 값을 업데이트 합니다. UpdateAllInputBinding()에서 한번에 처리합니다.*/
	void UpdateInputBinding();

	std::list<InputBinding*>::iterator myIter;

	/*모든 InputBinding 컴포넌트의 바인딩된 키들에 bool 값을 업데이트 해주는 함수.WinGameApp->Run() 루프에서만 호출합니다.*/
	static void UpdateAllInputBinding();

	/* 생성된 컴포넌트 리스트*/
	static std::list<InputBinding*> instanceList;

};

