#pragma once
#include <Core/Component/Base/ComponentBase.h>

class GameManagerCtrl : public ComponentBase
{
public:
	GameManagerCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject) {}
	virtual ~GameManagerCtrl() override;

	static int CurrentStage;
	static int EnemyCount;

	void LoadNextStage();

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;
};