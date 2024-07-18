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
	class StageEditer* world = nullptr;
	GameObjectBase* grabObject = nullptr;
	bool editMode = true;

	void SetObjectPos(GameObjectBase* object);
};