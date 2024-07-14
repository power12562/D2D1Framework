#pragma once
#include <Core/Component/Base/ComponentBase.h>

class RectModeCtrl : public ComponentBase
{
public:
	RectModeCtrl(GameObjectBase& gameObject);
	virtual ~RectModeCtrl() override;

	class SpriteRenderer* spriteRenderer = nullptr;
	class SpriteAnimationRenderer* spriteAnimation = nullptr;
protected:
	virtual void Start();
	virtual void Update();
	//virtual void LateUpdate();
	virtual void Render();

private:
	void SetSourceLeftTop();
	void SetSourceRightBottom();
};
