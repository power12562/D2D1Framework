#pragma once
#include <Core/Component/Base/ComponentBase.h>

class FireEffectCtrl : public ComponentBase
{
public:
	FireEffectCtrl(GameObjectBase& gameObject);
	virtual ~FireEffectCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	class SpriteAnimationRenderer* animationRenderer = nullptr;
};