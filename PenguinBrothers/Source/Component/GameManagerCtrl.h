#pragma once
#include <Core/Component/Base/ComponentBase.h>

class GameManagerCtrl : public ComponentBase
{
public:
	GameManagerCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject) {}
	virtual ~GameManagerCtrl() override;

	static int CurrentStage;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;
};