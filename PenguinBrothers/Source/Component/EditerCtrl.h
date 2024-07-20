#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Core/GameObject/Base/GameObjectBase.h>

class EditerCtrl : public ComponentBase
{
public:
	EditerCtrl(GameObjectBase& gameObject);
	virtual ~EditerCtrl() override;

protected:
	virtual void Start();
	virtual void Update();
	//virtual void LateUpdate();
	//virtual void Render();

private:
	bool editMode = true;
	class StageEditer* world = nullptr;
	GameObjectBase* grabObject = nullptr;
	GameObjectBase* selObject = nullptr;
	
	void EnableEditMode(bool enable);
	void deleteSelObject();
	void SetObjectPos(GameObjectBase* object);
	void SetDino0();
	void AddGround();
};