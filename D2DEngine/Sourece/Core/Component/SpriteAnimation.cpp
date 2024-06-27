#include "SpriteAnimation.h"
#include "Framework/WinGameApp.h"
#include "Framework/TimeSystem.h"
#include "Core/GameObject/GameObjectBase.h"

#include <iostream>
#include <fstream>
#include <sstream>

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
		AnimationClip* newClip = CreateAnimationClipFromFile(path);
		if (newClip)
		{
			Animations[clipName] = std::pair<std::wstring, AnimationClip*>(path, newClip);
		}
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
		gameObject.GetTransform().pivot = Vector2{ frame.source.right - frame.source.left, frame.source.bottom - frame.source.top };
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
			gameObject.GetTransform().pivot = Vector2{ frame.source.right - frame.source.left, frame.source.bottom - frame.source.top };
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

	//csv 파싱 로직
	std::wifstream file(filePath);
	if (!file.is_open()) 
	{
		wchar_t message[100];
		swprintf_s(message, _ARRAYSIZE(message), L"%s 경로를 찾을수 없습니다.", filePath);
		MessageBox(WinGameApp::GetHwnd(), message, L"SpriteAnimation Load Error", MB_OK);
		return nullptr;
	}
	AnimationClip* newClip = new AnimationClip;
	if(newClip == nullptr)
	{
		MessageBox(WinGameApp::GetHwnd(), L"메모리 할당 실패", L"SpriteAnimation Load Error", MB_OK);
		return nullptr; //할당 실패
	}	
	std::wstring line;			// 한줄의 문자열
	int FrameCount = 0;			// 프레임의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	newClip->frames.reserve(FrameCount);
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
		}
	}
	clipResourceMap[filePath] = newClip;
	
	return newClip;
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

