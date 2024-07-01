#include "SpriteAnimation.h"
#include "Framework/WinGameApp.h"
#include "Framework/TimeSystem.h"
#include "Core/GameObject/Base/GameObjectBase.h"

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
		elapsedTime = 0;
		currentFrame = 0;
		CurrentClip = iter->second.second;
		lastFrameIndex = CurrentClip->frames.size() - 1;
		UpdateCurrentPivot();
	}
	else
	{
		MessageBox(WinGameApp::GetHwnd(), L"클립을 찾을 수 없습니다.", L"SpriteAnimationRenderer::SetAnimationClip", MB_OK);
	}
}

FrameInfo* const SpriteAnimation::GetCurrentFrame()
{
	if (CurrentClip)
	{
		return &CurrentClip->frames[currentFrame];
	}
	else
	{
		return nullptr;
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

void SpriteAnimation::UpdateCurrentPivot()
{
	FrameInfo* frame = GetCurrentFrame();
	Vector2 currentPivot = Vector2{ frame->source.right - frame->source.left, frame->source.bottom - frame->source.top };
	currentPivot *= 0.5f;
	currentPivot.x += frame->center.x;
	currentPivot.y += frame->center.y;
	gameObject.GetTransform().pivot = currentPivot;
}

SpriteAnimation::AnimationClip* SpriteAnimation::CreateAnimationClipFromFile(const wchar_t* filePath)
{
	auto iter = clipResourceMap.find(filePath);
	if (iter != clipResourceMap.end())
	{
		iter->second->AddRef();
		return iter->second; //기존에 있던 리소스 반환
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

