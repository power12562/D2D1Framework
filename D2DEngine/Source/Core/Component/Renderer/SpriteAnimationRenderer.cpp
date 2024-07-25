#include "SpriteAnimationRenderer.h"
#include "Framework/WinGameApp.h"
#include "Framework/TimeSystem.h"
#include "Framework/D2DRenderer.h"
#include <Utility/JsonUtility.h>

#include "Core/GameObject/Base/GameObjectBase.h"

#include <cassert>
#include <iostream>
#include <ios>
#include <istream>
#include <fstream>
#include <sstream>
#include <iosfwd>
#include <filesystem>

std::map<std::wstring, AnimationClip*> SpriteAnimationRenderer::clipResourceMap;
std::list<SpriteAnimationRenderer*> SpriteAnimationRenderer::instanceList;

SpriteAnimationRenderer::SpriteAnimationRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	instanceList.push_back(this);
	myIter = std::prev(instanceList.end()); //�ڽ��� ���ͷ����͸� ������ ���
}

SpriteAnimationRenderer::~SpriteAnimationRenderer()
{
	for (auto& clip : Animations)
	{
		ReleaseAnimationClip(clip.second.clipPath.c_str());
		D2DRenderer::ReleaseD2D1Bitmap(clip.second.imagePath.c_str());
	}
	Animations.clear();
	instanceList.erase(myIter);
}

void SpriteAnimationRenderer::LoadAnimationClip(const wchar_t* clipPath, const wchar_t* imagePath, const wchar_t* clipName)
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
		MessageBox(WinGameApp::GetHwnd(), L"clipName�� �ߺ��˴ϴ�.", L"SpriteAnimationRenderer::LoadAnimation", MB_OK);
		assert(false);
	}
}

void SpriteAnimationRenderer::UnloadAnimationClip(const wchar_t* clipName)
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
		MessageBox(WinGameApp::GetHwnd(), L"Ŭ���� ã�� �� �����ϴ�.", L"SpriteAnimationRenderer::UnloadAnimation", MB_OK);
		assert(false);
	}
}

void SpriteAnimationRenderer::UnloadAllAnimationClip()
{
	for (auto& item : Animations)
	{
		ReleaseAnimationClip(item.second.clipPath.c_str());
		D2DRenderer::ReleaseD2D1Bitmap(item.second.imagePath.c_str());
	}
	Animations.clear();
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
		MessageBox(WinGameApp::GetHwnd(), L"Ŭ���� ã�� �� �����ϴ�.", L"SpriteAnimationRenderer::SetAnimation", MB_OK);
		assert(false);
	}
}

const AnimationAsset* SpriteAnimationRenderer::GetCurrentAnimation()
{
	if (currentAnimation)
		return currentAnimation;

	else
		return nullptr;
}

AnimationClip* SpriteAnimationRenderer::GetCurrentClip()
{
	if (currentAnimation)
		return currentAnimation->clip;

	return nullptr;
}

FrameInfo* SpriteAnimationRenderer::GetCurrentFrame()
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
		if (0 >= currentAnimation->clip->frames[currentFrame].frameIntervalTime)
		{
			assert(!"�߸��� ������ �ð� ���� �Դϴ�.");
		}

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


void SpriteAnimationRenderer::Render()
{
	if (isDraw)
	{
		if (ID2D1Bitmap* const* image = this->GetCurrentImage())
		{
			FrameInfo* const frame = this->GetCurrentFrame();

			D2D1_MATRIX_3X2_F objMatrix = D2D1::Matrix3x2F::Translation(frame->center.x, -frame->center.y) *
				gameObject.transform.GetInvertPivotMatrix() * 
				gameObject.transform.GetCameraMatrix();
			D2DRenderer::DrawBitmap(*image, objMatrix, frame->source);
		}
	}
}

void SpriteAnimationRenderer::UpdateCurrentPivot()
{
	if (FrameInfo* frame = GetCurrentFrame())
	{
		Vector2 currentPivot = Vector2{ frame->source.right - frame->source.left, frame->source.bottom - frame->source.top };
		//currentPivot.x -= frame->center.x;
		//currentPivot.y += frame->center.y;
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

void SpriteAnimationRenderer::SaveAnimationAssetToJson(const wchar_t* path)
{
	ordered_json objJson;
	for (auto& item : Animations)
	{
		ordered_json assetJson;
		std::wstring clipName(item.first);
		assetJson["clipName"] = clipName;
		assetJson["clipPath"] = item.second.clipPath;
		assetJson["imagePath"] = item.second.imagePath;
		objJson["Ainmations"].push_back(assetJson);
	}

	std::ofstream ofs(path);
	ofs << objJson.dump(2);
	ofs.close();
}

void SpriteAnimationRenderer::LoadAnimationAssetToJson(const wchar_t* path)
{
	ordered_json objJson;
	if (JsonUtility::ordered_jsonLoadToFile(path, objJson))
	{
		for (auto& item : objJson["Ainmations"])
		{
			std::wstring clipName = item["clipName"].get<std::wstring>();

			std::wstring clipPath = item["clipPath"].get<std::wstring>();

			std::wstring imagePath = item["imagePath"].get<std::wstring>();

			LoadAnimationClip(clipPath.c_str(), imagePath.c_str(), clipName.c_str());
		}
	}
	else
	{
		assert(!"LoadAnimationAssetToJson : �ִϸ��̼� ������ �ƴմϴ�.");
	}
}

void SpriteAnimationRenderer::SetRenderPos()
{
	originPos = gameObject.transform.position;
	if (FrameInfo* const frame = this->GetCurrentFrame())
	{
		renderPos = originPos + Vector2(frame->center.x * gameObject.transform.scale.x, frame->center.y * gameObject.transform.scale.y);
		gameObject.transform.position = renderPos;
	}
}

void SpriteAnimationRenderer::SetOriginPos()
{
	gameObject.transform.position = originPos;
}

AnimationClip* SpriteAnimationRenderer::CreateAnimationClipFromFile(const wchar_t* filePath)
{
	auto iter = clipResourceMap.find(filePath);
	if (iter != clipResourceMap.end())
	{
		iter->second->AddRef();
		return iter->second; //������ �ִ� ���ҽ� ��ȯ
	}

	//csv �Ľ� ���� ����
	std::wifstream file(filePath);
	if (!file.is_open()) 
	{
		wchar_t message[100];
		swprintf_s(message, _ARRAYSIZE(message), L"%s ��θ� ã���� �����ϴ�.", filePath);
		MessageBox(WinGameApp::GetHwnd(), message, L"SpriteAnimationRenderer Load Error", MB_OK);
		assert(false);
		return nullptr;
	}
	AnimationClip* newClip = new AnimationClip;
	if(newClip == nullptr)
	{
		MessageBox(WinGameApp::GetHwnd(), L"�޸� �Ҵ� ����", L"SpriteAnimationRenderer Load Error", MB_OK);
		return nullptr; //�Ҵ� ����
	}	
	std::wstring line;			// ������ ���ڿ�
	int FrameCount = 0;			// �������� ����
	while (std::getline(file, line)) 
	{
		++FrameCount;
	}
	newClip->frames.resize(FrameCount);
	// ���� ��Ʈ�� �缳��
	file.clear(); // ��Ʈ���� ���� �÷��׸� ����
	file.seekg(0); // ������ ó������ �̵�	
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// ���� �б�
		std::wstringstream wss(line);    // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
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

void SpriteAnimationRenderer::SaveAnimationClipToFile(const AnimationClip& clip, const wchar_t* path)
{
	std::ofstream outFile(path, std::ios::trunc); // append mode
	if (outFile.is_open())
	{
		for (int i = 0; i < clip.frames.size(); i++)
		{
			outFile << clip.frames[i].source.left << "," << clip.frames[i].source.top << ","
				<< clip.frames[i].source.right << "," << clip.frames[i].source.bottom << ","
				<< clip.frames[i].center.x << "," << clip.frames[i].center.y << ","
				<< clip.frames[i].frameIntervalTime << "\n";
		}
		outFile.close();
	}
	else
	{
		std::cerr << "Unable to open file";
	}
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



