#include "SpriteAnimationRenderer.h"
#include "Framework/WinGameApp.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::map<std::wstring, AnimationClip*> SpriteAnimationRenderer::clipResourceMap;

SpriteAnimationRenderer::SpriteAnimationRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

SpriteAnimationRenderer::~SpriteAnimationRenderer()
{
	for (auto& clip : Animations)
	{
		ReleaseAnimationClip(clip.second.clipPath.c_str());
		D2DRenderer::ReleaseD2D1Bitmap(clip.second.imagePath.c_str());
	}
	Animations.clear();
}

void SpriteAnimationRenderer::LoadAnimation(const wchar_t* clipPath, const wchar_t* imagePath, const wchar_t* clipName)
{
	auto iter = Animations.find(clipName);
	if (iter == Animations.end())
	{
		AnimationAsset asset;
		asset.clipPath = clipPath;
		asset.clip = CreateAnimationClipFromFile(clipPath);

		asset.imagePath = imagePath;
		asset.image = D2DRenderer::CreateD2DBitmapFromFile(imagePath);

		if (asset.clip && asset.image)
		{
			Animations[clipName] = asset;
		}
	}
	else
	{
		MessageBox(WinGameApp::GetHwnd(), L"clipName이 중복됩니다.", L"SpriteAnimationRenderer::LoadAnimation", MB_OK);
	}
}

void SpriteAnimationRenderer::UnloadAnimation(const wchar_t* clipName)
{
	auto iter = Animations.find(clipName);
	if (iter != Animations.end())
	{
		if (currentAnimation == &iter->second)
		{
			currentAnimation = nullptr;
		}
		ReleaseAnimationClip(iter->second.clipPath.c_str());
		D2DRenderer::ReleaseD2D1Bitmap(iter->second.imagePath.c_str());
		Animations.erase(iter);
	}
	else
	{
		MessageBox(WinGameApp::GetHwnd(), L"클립을 찾을 수 없습니다.", L"SpriteAnimationRenderer::UnloadAnimation", MB_OK);
	}
}

void SpriteAnimationRenderer::SetAnimation(const wchar_t* clipName, bool isLoop)
{
	this->isLoop = isLoop;
	this->isCurrentClipEnd = isLoop;
	auto iter = Animations.find(clipName);
	if (iter != Animations.end())
	{
		elapsedTime = 0;
		currentFrame = 0;
		currentAnimation = &iter->second;
		lastFrameIndex = currentAnimation->clip->frames.size() - 1;
		UpdateCurrentPivot();
	}
	else
	{
		MessageBox(WinGameApp::GetHwnd(), L"클립을 찾을 수 없습니다.", L"SpriteAnimationRenderer::SetAnimation", MB_OK);
	}
}

const AnimationAsset* SpriteAnimationRenderer::GetCurrentAnimation()
{
	if (currentAnimation)
		return currentAnimation;

	else
		return nullptr;
}

FrameInfo* const SpriteAnimationRenderer::GetCurrentFrame()
{
	if (currentAnimation)
	{
		return &currentAnimation->clip->frames[currentFrame];
	}
	else
	{
		return nullptr;
	}
}

ID2D1Bitmap* const* SpriteAnimationRenderer::GetCurrentImage()
{
	if (currentAnimation)
	{
		return currentAnimation->image;
	}
	else
	{
		return nullptr;
	}
}



void SpriteAnimationRenderer::Update()
{
	if (currentAnimation && (!isCurrentClipEnd || isLoop))
	{
		elapsedTime += TimeSystem::Time.GetDeltatime();
		while (elapsedTime > currentAnimation->clip->frames[currentFrame].frameIntervalTime)
		{
			elapsedTime -= currentAnimation->clip->frames[currentFrame].frameIntervalTime;
			currentFrame++;
			if (lastFrameIndex < currentFrame)
			{
				if (isLoop)
				{
					currentFrame = 0;
				}		
				else
				{
					isCurrentClipEnd = true;
					currentFrame = lastFrameIndex;
					break;
				}
			}
			UpdateCurrentPivot();
		}
	}
}

void SpriteAnimationRenderer::LateUpdate()
{
	if (FrameInfo* frame = GetCurrentFrame()) //바운드 영역 애니메이션 중심 값 만큼 이동.
	{
		Bounds& bounds = gameObject.bounds;
		bounds.center.x += frame->center.x;
		bounds.center.y += frame->center.y;

		bounds.leftTop.x += frame->center.x;
		bounds.leftTop.y += frame->center.y;

		bounds.rightBottom.x += frame->center.x;;
		bounds.rightBottom.y += frame->center.y;
	}
}

void SpriteAnimationRenderer::Render()
{
	if (ID2D1Bitmap* const* image = this->GetCurrentImage())
	{
		FrameInfo* const frame = this->GetCurrentFrame();

		D2D1_MATRIX_3X2_F objMatrix = gameObject.transform.GetInvertPivotMatrix() * gameObject.transform.GetCameraMatrix();

		int flipX = (0 < gameObject.transform.scale.x) ? 1 : -1;
		int flipY = (0 < gameObject.transform.scale.y) ? 1 : -1;
		objMatrix = D2D1::Matrix3x2F::Translation(flipX * frame->center.x, flipY * -frame->center.y) * objMatrix;
		D2DRenderer::DrawBitmap(*image, objMatrix, frame->source);
	}
}

void SpriteAnimationRenderer::UpdateCurrentPivot()
{
	if (FrameInfo* frame = GetCurrentFrame())
	{
		Vector2 currentPivot = Vector2{ frame->source.right - frame->source.left, frame->source.bottom - frame->source.top };
		currentPivot *= 0.5f;
		gameObject.GetTransform().pivot = currentPivot;
	}
}

void SpriteAnimationRenderer::SetCurrentFrameIndex(int frame)
{
	if (0 <= frame && frame <= lastFrameIndex)
	{
		currentFrame = frame;
		UpdateCurrentPivot();
	}
}

AnimationClip* SpriteAnimationRenderer::CreateAnimationClipFromFile(const wchar_t* filePath)
{
	auto iter = clipResourceMap.find(filePath);
	if (iter != clipResourceMap.end())
	{
		iter->second->AddRef();
		return iter->second; //기존에 있던 리소스 반환
	}

	//csv 파싱 로직 예정
	std::wifstream file(filePath);
	if (!file.is_open()) 
	{
		wchar_t message[100];
		swprintf_s(message, _ARRAYSIZE(message), L"%s 경로를 찾을수 없습니다.", filePath);
		MessageBox(WinGameApp::GetHwnd(), message, L"SpriteAnimationRenderer Load Error", MB_OK);
		return nullptr;
	}
	AnimationClip* newClip = new AnimationClip;
	if(newClip == nullptr)
	{
		MessageBox(WinGameApp::GetHwnd(), L"메모리 할당 실패", L"SpriteAnimationRenderer Load Error", MB_OK);
		return nullptr; //할당 실패
	}	
	std::wstring line;			// 한줄의 문자열
	int FrameCount = 0;			// 프레임의 개수
	while (std::getline(file, line)) 
	{
			++FrameCount;
	}
	newClip->frames.resize(FrameCount);
	// 파일 스트림 재설정
	file.clear(); // 스트림의 상태 플래그를 리셋
	file.seekg(0); // 파일의 처음으로 이동	
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// 한줄 읽기
		std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
			newClip->frames[j].source.left = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			newClip->frames[j].source.top = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			newClip->frames[j].source.right = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			newClip->frames[j].source.bottom = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			newClip->frames[j].center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			newClip->frames[j].center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			newClip->frames[j].frameIntervalTime = (float)_wtof(token.c_str());
		}
	}
	clipResourceMap[filePath] = newClip;
	
	return newClip;
}

void SpriteAnimationRenderer::ReleaseAnimationClip(const wchar_t* filePath)
{
	auto iter = clipResourceMap.find(filePath);
	if (iter != clipResourceMap.end())
	{
		ULONG refCount = iter->second->Release();
		if (refCount == 0)
		{
			clipResourceMap.erase(iter);
		}
	}
}

