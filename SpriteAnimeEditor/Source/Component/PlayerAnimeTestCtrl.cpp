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
#include "Core/Component/Collider/SpriteCollider2D.h"
#include "Core/Component/Camera.h"

#include "Source/Component/DebugUICtrl.h"
#include "Source/Component/RectModeCtrl.h"

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

	boxCollider = &gameObject.AddComponent<SpriteCollider2D>();
	boxCollider->isDrawCollider = true;

	debugUI = &WorldManager::FindGameObject(L"DebugUI")->GetComponent<DebugUICtrl>();

	debugUI->Line.resize(12);
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
	if (Input.IsKeyDown(KeyCode::F3))
	{
		MakeNewClip();
	}
	if (Input.IsKeyDown(KeyCode::F4))
	{
		SaveAsCurrentAniToFile();
	}
	if (Input.IsKeyDown(KeyCode::F5))
	{
		 rectMode = !rectMode;
		 EnableRectMode();
	}

	if (Input.IsKeyDown(KeyCode::Inser))
	{
		InsertFrame();
	}
	if (Input.IsKeyDown(KeyCode::Delete))
	{
		DeleteFrame();
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

	UpdateDebugText();
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

void PlayerAnimeTestCtrl::MakeNewClip()
{
	if (!currentImagePath.empty())
	{
		bool result = WinUtility::ShowConfirmationDialog(L"경고!", L"저장하지 않은 내용은 삭제됩니다.");
		if (result)
		{
			if (spriteAnimation->GetCurrentAnimation())
			{
				spriteAnimation->UnloadAnimationClip(L"set");
			}
			spriteAnimation->LoadAnimationClip(L"newClip.txt", currentImagePath.c_str(), L"set");
			spriteAnimation->SetAnimation(L"set", true);
			FrameInfo& frame = spriteAnimation->GetCurrentClip()->frames[0];
			frame.source.right = (*spriteAnimation->GetCurrentImage())->GetSize().width;
			frame.source.bottom = (*spriteAnimation->GetCurrentImage())->GetSize().height;
			currentAniPath = L"new";
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

void PlayerAnimeTestCtrl::EnableRectMode()
{
	if (rectMode)
	{
		RectModeCtrl* rectMode = &WorldManager::FindGameObject(L"RectMode")->GetComponent<RectModeCtrl>();
		rectMode->gameObject.enable = true;
		rectMode->spriteRenderer->LoadImage(currentImagePath.c_str());
		rectMode->spriteAnimation = spriteAnimation;
		spriteAnimation->isDraw = false;
		boxCollider->enabled = false;
	}
	else
	{
		RectModeCtrl* rectMode = &WorldManager::FindGameObject(L"RectMode")->GetComponent<RectModeCtrl>();
		rectMode->gameObject.enable = false;
		spriteAnimation->isDraw = true;
		boxCollider->enabled = true;
	}
}

void PlayerAnimeTestCtrl::InsertFrame()
{
	if (AnimationClip* clip = spriteAnimation->GetCurrentClip())
	{
		const D2D1_SIZE_F& imageSize = (*spriteAnimation->GetCurrentImage())->GetSize();
		clip->frames.push_back({ { 0,0, imageSize.width,imageSize.height }, {0, 0}, 0.2f });
		spriteAnimation->SetAnimation(L"set", true);
	}
}

void PlayerAnimeTestCtrl::DeleteFrame()
{
	if (AnimationClip* clip = spriteAnimation->GetCurrentClip())
	{
		if (clip->frames.size() > 1)
		{
			clip->frames.pop_back();
			spriteAnimation->SetAnimation(L"set", true);
		}
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

void PlayerAnimeTestCtrl::UpdateDebugText()
{
	using namespace InputSystem;
	int currentLine = 0;

	debugUI->Line[currentLine++] = L"Open Image : F1, Open Ani : F2, New Clip : F3, Save clip : F4, RectMode on/off : F5";
	debugUI->Line[currentLine++] = L"Add frame : Insert, Delete frame : delete";
	debugUI->Line[currentLine++] = L"set left top : 1, set right bottom : 2, camera zoom : +, -";
	debugUI->Line[currentLine++] = std::wstring(L"Image : ") + currentImagePath;
	debugUI->Line[currentLine++] = std::wstring(L"AniClip : ") + currentAniPath;

	wchar_t framesSizeWString[30]{ L"frames count :" };
	if (AnimationClip* clip = spriteAnimation->GetCurrentClip())
	{
		int size = clip->frames.size();
		swprintf_s(framesSizeWString, _ARRAYSIZE(framesSizeWString), L"frames count : %d", size);
	}
	debugUI->Line[currentLine++] = framesSizeWString;

	debugUI->Line[currentLine++] = std::wstring(L"current frame : ") + std::to_wstring(spriteAnimation->CurrentFrameIndex);

	wchar_t aniCenterWString[30]{ L"center :" };
	FrameInfo* frame = spriteAnimation->GetCurrentFrame();
	if (frame)
	{
		const D2D1_VECTOR_2F& aniCenter = frame->center;
		swprintf_s(aniCenterWString, _ARRAYSIZE(aniCenterWString), L"center : %01.f, %01.f", aniCenter.x, aniCenter.y);
	}
	debugUI->Line[currentLine++] = aniCenterWString;

	wchar_t sourceWString[35]{ L"source : " };
	if (frame)
	{
		const D2D1_RECT_F& source = frame->source;
		swprintf_s(sourceWString, _ARRAYSIZE(sourceWString), L"source : { %.0f, %.0f, %.0f, %.0f }", source.left, source.top, source.right, source.bottom);
	}
	debugUI->Line[currentLine++] = sourceWString;

	wchar_t camPosWString[30]{};
	const Vector2& camPos = Camera::GetMainCamera()->gameObject.transform.position;
	swprintf_s(camPosWString, _ARRAYSIZE(camPosWString), L"CameraPos : %01.f, %01.f", camPos.x, camPos.y);
	debugUI->Line[currentLine++] = camPosWString;

	wchar_t imagePosWString[30]{};
	if (rectMode)
	{
		const D2D1_SIZE_F imageSize = (*spriteAnimation->GetCurrentImage())->GetSize();
		swprintf_s(imagePosWString, _ARRAYSIZE(imagePosWString), L"ImagePos : %01.f, %01.f", camPos.x + imageSize.width * 0.5f, imageSize.height * 0.5f - camPos.y);
	}
	else
	{
		const Bounds& imageBounds = gameObject.cullingBounds;
		swprintf_s(imagePosWString, _ARRAYSIZE(imagePosWString), L"ImagePos : %01.f, %01.f", camPos.x - imageBounds.leftTop.x, imageBounds.leftTop.y - camPos.y);
	}
	debugUI->Line[currentLine++] = imagePosWString;

	wchar_t mousePosWString[35]{};
	const Vector2& mousePos = Input.GetMouseState().GetWorldPos();
	swprintf_s(mousePosWString, _ARRAYSIZE(mousePosWString), L"MousePos : %01.f, %01.f", mousePos.x, mousePos.y);
	debugUI->Line[currentLine++] = mousePosWString;
}
