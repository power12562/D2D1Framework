#pragma once
#include "Vector/Vector2.h"

#include "Core/Component/Base/ComponentBase.h"

class PlayerCtrl : public ComponentBase
{
	class SpriteAnimation* spriteAnimation;
public:
	enum class State
	{
		Spawn,
		Idle,
		Duck,
		Walk,
		Jump,
		Slide,
		Attack,
		Dead
	};

	PlayerCtrl(GameObjectBase& gameObject);
	virtual ~PlayerCtrl();

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:
	Vector2 dir = Vector2::Right;
	State playerState;
	State animeState;
	float moveSpeed;
	float slideSpeed;
	void SetState(State state);
	void UpdateState();
	void UpdateAnime();

};