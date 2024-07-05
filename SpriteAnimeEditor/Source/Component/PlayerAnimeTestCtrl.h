#pragma once
#include "Vector/Vector2.h"

#include "Core/Component/Base/ComponentBase.h"

#include <string>

class PlayerAnimeTestCtrl : public ComponentBase
{
	class SpriteAnimation* spriteAnimation;
	class SpriteRenderer* spriteRenderer;
	class DebugUICtrl* debugUI;
public:

	PlayerAnimeTestCtrl(GameObjectBase& gameObject);
	virtual ~PlayerAnimeTestCtrl() override;

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:
	std::wstring currentAniPath;
	std::wstring currentImagePath;

};