#pragma once
#include "Vector/Vector2.h"

#include "Core/Component/Base/ComponentBase.h"

#include <string>

class PlayerAnimeTestCtrl : public ComponentBase
{
	class SpriteAnimationRenderer* spriteAnimation;
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

	void SelCurrentImage();
	void SelCurrentAni();
	
	void SaveAsCurrentAniToFile();
	void PauseAndPlayAni();
	void ReloadAnimation();

	bool rectMode = false;
};