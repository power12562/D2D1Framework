#pragma once
#include "Vector/Vector2.h"

#include "Core/Component/Base/ComponentBase.h"

class PlayerAnimeTestCtrl : public ComponentBase
{
	class SpriteAnimation* spriteAnimation;
public:

	PlayerAnimeTestCtrl(GameObjectBase& gameObject);
	virtual ~PlayerAnimeTestCtrl() override;

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:


};