#pragma once
#include <Core/Component/Base/ComponentBase.h>

class EnemyDino0AttackCtrl : public ComponentBase
{
	class SpriteAnimationRenderer* animation;
public:
	EnemyDino0AttackCtrl(GameObjectBase& gameObject);
	virtual ~EnemyDino0AttackCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:

};

