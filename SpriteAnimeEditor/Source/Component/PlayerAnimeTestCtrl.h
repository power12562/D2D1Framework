#pragma once
#include "Vector/Vector2.h"

#include "Core/Component/Base/ComponentBase.h"

#include <string>

class PlayerAnimeTestCtrl : public ComponentBase
{
	class SpriteAnimationRenderer* spriteAnimation;
	class DebugUICtrl* debugUI;
	class BoxCollider2D* boxCollider = nullptr;
public:
	PlayerAnimeTestCtrl(GameObjectBase& gameObject);
	virtual ~PlayerAnimeTestCtrl() override;

	std::wstring currentAniPath;
	std::wstring currentImagePath;

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:
	void SelCurrentImage();
	void SelCurrentAni();
	void MakeNewClip();
	void SaveAsCurrentAniToFile();
	void EnableRectMode();

	void PauseAndPlayAni();
	void ReloadAnimation();

	void UpdateDebugText();
	bool rectMode = false;
};