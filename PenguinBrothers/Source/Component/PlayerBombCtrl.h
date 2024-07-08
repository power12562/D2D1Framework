#pragma once
#include "Core/Component/Base/ComponentBase.h"

class PlayerBombCtrl : public ComponentBase
{
public:
	PlayerBombCtrl(GameObjectBase& gameObject);
	virtual ~PlayerBombCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	class SpriteRenderer* spriteRenderer = nullptr;
	class SpriteAnimation* spriteAnimation = nullptr;

	float elapsedTime = 0;

};