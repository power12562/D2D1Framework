#include "SpriteAnimation.h"
#include "Framework/WinGameApp.h"
#include "Framework/TimeSystem.h"
#include "Core/GameObject/GameObjectBase.h"

std::map<std::wstring, SpriteAnimation::AnimationClip*> SpriteAnimation::clipResourceMap;

SpriteAnimation::SpriteAnimation(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::LoadAnimationClip(const wchar_t* path, const wchar_t* clipName)
{
	auto iter = Animations.find(clipName);
	if (iter == Animations.end())
	{
		Animations[clipName] = std::pair<std::wstring, AnimationClip*>(path, CreateAnimationClipFromFile(path));
	}
	else
	{
		MessageBox(WinGameApp::GetHwnd(), L"clipName이 중복됩니다.", L"SpriteAnimationRenderer::LoadAnimationClip", MB_OK);
	}
}

void SpriteAnimation::UnloadAnimationClip(const wchar_t* clipName)
{
	auto iter = Animations.find(clipName);
	if (iter != Animations.end())
	{
		if (CurrentClip == iter->second.second)
		{
			CurrentClip = nullptr;
		}

		ReleaseAnimationClip(iter->second.first.c_str());
		Animations.erase(iter);
	}
	else
	{
		MessageBox(WinGameApp::GetHwnd(), L"클립을 찾을 수 없습니다.", L"SpriteAnimationRenderer::UnloadAnimationClip", MB_OK);
	}
}

void SpriteAnimation::SetAnimationClip(const wchar_t* clipName, bool isLoop)
{
	this->isLoop = isLoop;
	this->isCurrentClipEnd = isLoop;
	auto iter = Animations.find(clipName);
	if (iter != Animations.end())
	{
		CurrentClip = iter->second.second;
		lastFrameIndex = CurrentClip->frames.size() - 1;
		const FrameInfo& frame = GetCurrentFrame();
		gameobject.transform().pivot = Vector2{ frame.source.right - frame.source.left, frame.source.bottom - frame.source.top };
	}
	else
	{
		MessageBox(WinGameApp::GetHwnd(), L"클립을 찾을 수 없습니다.", L"SpriteAnimationRenderer::SetAnimationClip", MB_OK);
	}
}


void SpriteAnimation::Update()
{
	if (!isCurrentClipEnd || isLoop)
	{
		elapsedTime += TimeSystem::Time.GetDeltatime();
		while (elapsedTime > CurrentClip->frames[currentFrame].frameIntervalTime)
		{
			elapsedTime -= CurrentClip->frames[currentFrame].frameIntervalTime;
			currentFrame++;
			if (lastFrameIndex < currentFrame)
			{
				if (isLoop)
					currentFrame = 0;
				else
				{
					isCurrentClipEnd = true;
					currentFrame = lastFrameIndex;
					break;
				}
			}
			const FrameInfo& frame = GetCurrentFrame();
			gameobject.transform().pivot = Vector2{ frame.source.right - frame.source.left, frame.source.bottom - frame.source.top };
		}
	}
}

SpriteAnimation::AnimationClip* SpriteAnimation::CreateAnimationClipFromFile(const wchar_t* filePath)
{
	auto iter = clipResourceMap.find(filePath);
	if (iter != clipResourceMap.end())
	{
		iter->second->AddRef();
		return iter->second; //기존에 있던 리소스 반환
	}

	//(임시 클립임)
	if (filePath == L"Bg")
	{
		AnimationClip* newClip = new AnimationClip;
		newClip->frames.resize(4);
		newClip->frames[0] = { 0,0, 784, 320, 0,0, 0.2f };
		newClip->frames[1] = {789, 0, 1573, 320, 0, 0, 0.2f};
		newClip->frames[2] = { 0,325,  784,645 ,0,0, 0.2f };
		newClip->frames[3] = { 789,325, 1573,645 ,0,0, 0.2f };

		clipResourceMap[filePath] = newClip;
		return newClip;
	}
	else if (filePath == L"Run")
	{
		AnimationClip* newClip = new AnimationClip;
		newClip->frames.resize(10);
		newClip->frames[0] = { 28, 36, 131, 120, 0, 0, 0.1f };
		newClip->frames[1] = { 148, 36, 234, 120, 0, 0, 0.1f };
		newClip->frames[2] = { 255, 34, 342, 120, 0, 0, 0.1f };
		newClip->frames[3] = { 363, 32, 439, 120, 0, 0, 0.1f };
		newClip->frames[4] = { 458, 31, 549, 120, 0, 0, 0.1f };
		newClip->frames[5] = { 567, 40, 670, 120, 0, 0, 0.1f };
		newClip->frames[6] = { 686, 32, 771, 120, 0, 0, 0.1f };
		newClip->frames[7] = { 792, 32, 878, 120, 0, 0, 0.1f };
		newClip->frames[8] = { 899, 31, 975, 120, 0, 0, 0.1f };
		newClip->frames[9] = { 993, 33, 1085, 120, 0, 0, 0.1f };

		clipResourceMap[filePath] = newClip;
		return newClip;
	}

	/*
	AnimationClip* newClip = new AnimationClip;
	파싱 로직 들어가야 함.
	clipResourceMap[filePath] = newClip;
	*/
	return nullptr;
}

void SpriteAnimation::ReleaseAnimationClip(const wchar_t* filePath)
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

