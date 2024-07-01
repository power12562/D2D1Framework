#pragma once
#include "Core/Component/Base/ComponentBase.h"

enum PlayerState
{
	Idle,
	Duck,
	Walk,
	Jump,
	Slide,
	Attack
};

class PlayerCtrl : public ComponentBase
{
	PlayerState playerState = PlayerState::Idle;
	class SpriteAnimation* spriteAnimation;
public:
	PlayerCtrl(GameObjectBase& gameObject);
	virtual ~PlayerCtrl();

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:
	float moveSpeed;
	void SetAnime(PlayerState state);

};