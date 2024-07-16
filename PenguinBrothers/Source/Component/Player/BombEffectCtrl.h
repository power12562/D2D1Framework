#pragma once
#include <Core/Component/Base/ComponentBase.h>

class BombEffectCtrl : public ComponentBase
{
public:
	BombEffectCtrl(GameObjectBase& gameObject);
	virtual ~BombEffectCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;
private:
	class SpriteAnimationRenderer* animationRenderer;
};