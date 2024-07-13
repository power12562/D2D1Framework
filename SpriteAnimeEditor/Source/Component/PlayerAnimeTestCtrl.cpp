#include "PlayerAnimeTestCtrl.h"
#include "Utility/WinUtility.h"
#include "Framework/InputSystem.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"
#include "Framework/WorldManager.h"

#include "Core/GameObject/Base/GameObjectBase.h"
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"
#include "Core/Component/Renderer/SpriteRenderer.h"
#include "Core/Component/Collider/BoxCollider2D.h"
#include "Core/Component/Camera.h"

#include "Source/Component/DebugUICtrl.h"

PlayerAnimeTestCtrl::PlayerAnimeTestCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	
}

PlayerAnimeTestCtrl::~PlayerAnimeTestCtrl()
{

}

void PlayerAnimeTestCtrl::Start()
{
	gameObject.AddComponent<SpriteAnimationRenderer>();
	spriteAnimation = &gameObject.GetComponent<SpriteAnimationRenderer>();

	BoxCollider2D& boxCollider2D = gameObject.AddComponent<BoxCollider2D>();
	boxCollider2D.isDrawCollider = true;

	debugUI = &WorldManager::FindGameObject(L"DebugUI")->GetComponent<DebugUICtrl>();

	debugUI->Line.resize(8);
}

void PlayerAnimeTestCtrl::Update()
{
	using namespace TimeSystem;
	using namespace InputSystem;

	if (Input.IsKeyDown(KeyCode::F1))
	{
		SelCurrentImage();
	}
	if (Input.IsKeyDown(KeyCode::F2))
	{
		SelCurrentAni();
	}
	if (Input.IsKeyDown(KeyCode::F4))
	{
		SaveAsCurrentAniToFile();
	}
	if (Input.IsKeyDown(KeyCode::F5))
	{
		 rectMode = !rectMode;
	}

	if (Input.IsKeyDown(KeyCode::Space))
	{
		PauseAndPlayAni();
	}
	if (Input.IsKeyDown(KeyCode::R))
	{
		ReloadAnimation();
	}

	bool isShift = Input.IsKey(KeyCode::Shift);
	if (Input.IsKeyDown(KeyCode::LeftArrow))
	{		
		if (isShift)
		{
			spriteAnimation->CurrentFrameIndex = 0;
		}
		else
		{
			spriteAnimation->CurrentFrameIndex = spriteAnimation->CurrentFrameIndex - 1;
		}	
	}
	else if (Input.IsKeyDown(KeyCode::RightArrow))
	{
		if (isShift)
		{
			spriteAnimation->CurrentFrameIndex = spriteAnimation->LastFrameIndex;
		}
		else
		{
			spriteAnimation->CurrentFrameIndex = spriteAnimation->CurrentFrameIndex + 1;
		}
	}
	if (Input.IsKeyDown(KeyCode::X))
	{
		gameObject.transform.FlipX();
	}
	if (Input.IsKeyDown(KeyCode::Y))
	{
		gameObject.transform.FlipY();
	}

	debugUI->Line[0] = L"F1 : OpenImage, F2 : OpenAni, F3 : Save Asset, F4 : Save clip, F5 : RectMode on/off";
	debugUI->Line[1] = std::wstring(L"Image : ") + currentImagePath + L" (F1)";
	debugUI->Line[2] = std::wstring(L"AniClip : ") + currentAniPath + L" (F2)";
	debugUI->Line[3] = std::wstring(L"CurrentFrame : ") + std::to_wstring(spriteAnimation->CurrentFrameIndex);

	wchar_t aniCenterWString[30]{L"center :"};
	if (FrameInfo* frame = spriteAnimation->GetCurrentFrame())
	{
		const D2D1_VECTOR_2F& aniCenter = frame->center;
		swprintf_s(aniCenterWString, _ARRAYSIZE(aniCenterWString), L"center : %01.f, %01.f", aniCenter.x, aniCenter.y);
	}
	debugUI->Line[4] = aniCenterWString;
	
	wchar_t camPosWString[30]{};
	const Vector2& camPos = Camera::GetMainCamera()->gameObject.transform.position;
	swprintf_s(camPosWString, _ARRAYSIZE(camPosWString), L"CameraPos : %01.f, %01.f", camPos.x, camPos.y);
	debugUI->Line[5] = camPosWString;

	wchar_t imagePosWString[30]{};
	const Bounds& imageBounds = gameObject.bounds;
	swprintf_s(imagePosWString, _ARRAYSIZE(imagePosWString), L"ImagePos : %01.f, %01.f", camPos.x - imageBounds.leftTop.x, imageBounds.leftTop.y - camPos.y);
	debugUI->Line[6] = imagePosWString;

	wchar_t mousePosWString[35]{};
	const Vector2& mousePos = Input.GetMouseState().GetWorldPos();
	swprintf_s(mousePosWString, _ARRAYSIZE(mousePosWString), L"MousePos : %01.f, %01.f", mousePos.x, mousePos.y);
	debugUI->Line[7] = mousePosWString;

	
}

void PlayerAnimeTestCtrl::Render()
{


}

void PlayerAnimeTestCtrl::SelCurrentImage()
{
	std::wstring inputPath = WinUtility::GetOpenFilePath(L"png");
	if (L"" != inputPath)
	{
		currentImagePath = inputPath;
		if (!currentAniPath.empty())
		{
			if (spriteAnimation->GetCurrentAnimation())
				spriteAnimation->UnloadAnimationClip(L"set");
			spriteAnimation->LoadAnimationClip(currentAniPath.c_str(), currentImagePath.c_str(), L"set");
			spriteAnimation->SetAnimation(L"set", true);
		}
	}
}

void PlayerAnimeTestCtrl::SelCurrentAni()
{
	std::wstring inputPath = WinUtility::GetOpenFilePath(L"txt");
	if (L"" != inputPath)
	{
		currentAniPath = inputPath;
		if (!currentImagePath.empty())
		{
			if (spriteAnimation->GetCurrentAnimation())
				spriteAnimation->UnloadAnimationClip(L"set");
			spriteAnimation->LoadAnimationClip(currentAniPath.c_str(), currentImagePath.c_str(), L"set");
			spriteAnimation->SetAnimation(L"set", true);
		}
	}
}

void PlayerAnimeTestCtrl::SaveAsCurrentAniToFile()
{
	if (spriteAnimation->GetCurrentAnimation())
	{
		std::wstring savePath = WinUtility::GetSaveAsFilePath(L"txt");
		if (savePath != L"")
			SpriteAnimationRenderer::SaveAnimationClipToFile(*spriteAnimation->GetCurrentAnimation()->clip, savePath.c_str());
	}
}

void PlayerAnimeTestCtrl::PauseAndPlayAni()
{
	TimeSystem::Time.timeScale = TimeSystem::Time.timeScale == 0 ? 1.f : 0.f;
}

void PlayerAnimeTestCtrl::ReloadAnimation()
{
	//다시 로드
	if (!currentAniPath.empty() && !currentImagePath.empty())
	{
		int currentIndex = spriteAnimation->CurrentFrameIndex;
		if (spriteAnimation->GetCurrentAnimation())
			spriteAnimation->UnloadAnimationClip(L"set");
		spriteAnimation->LoadAnimationClip(currentAniPath.c_str(), currentImagePath.c_str(), L"set");
		spriteAnimation->SetAnimation(L"set", true);
		spriteAnimation->CurrentFrameIndex = currentIndex;
	}
}
