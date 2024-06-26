#include "SpriteAnimationRenderer.h"

std::map<std::wstring, SpriteAnimationRenderer::AnimationClip*> SpriteAnimationRenderer::clipResourceMap;

SpriteAnimationRenderer::SpriteAnimationRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject)
{

}

SpriteAnimationRenderer::~SpriteAnimationRenderer()
{

}

void SpriteAnimationRenderer::LoadAnimationClip(const wchar_t* path, const wchar_t* clipName)
{
	Animations[clipName] = std::pair<std::wstring, AnimationClip*>(path, CreateAnimationClipFromFile(path));
}

void SpriteAnimationRenderer::UnloadAnimationClip(const wchar_t* clipName)
{
	ReleaseAnimationClip(Animations[clipName].first.c_str());
}

void SpriteAnimationRenderer::SetAnimationClip(const wchar_t* clipName)
{
	CurrentClip = Animations[clipName].second;
}


void SpriteAnimationRenderer::Update()
{

}

void SpriteAnimationRenderer::Render()
{
	
}


SpriteAnimationRenderer::AnimationClip* SpriteAnimationRenderer::CreateAnimationClipFromFile(const wchar_t* filePath)
{
	auto iter = clipResourceMap.find(filePath);
	if (iter != clipResourceMap.end())
	{
		iter->second->AddRef();
		return iter->second; //기존에 있던 리소스 반환
	}

	//csv파싱 로직 필요. (임시 클립임)
	if (filePath == L"Bg")
	{
		AnimationClip* newClip = new AnimationClip;
		newClip->frames.resize(4);
		newClip->frames[0] = { 0,0, 784, 320, 0,0,0.2 };
		newClip->frames[1] = {789, 0, 1573, 320, 0, 0, 0.2};
		newClip->frames[2] = { 0,325,  784,645 ,0,0,0.2 };
		newClip->frames[3] = { 789,325, 1573,645 ,0,0,0.2 };

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
		return newClip;
	}

	return nullptr;
}

void SpriteAnimationRenderer::ReleaseAnimationClip(const wchar_t* filePath)
{
	auto iter = clipResourceMap.find(filePath);
	if (iter != clipResourceMap.end())
	{
		iter->second->Release();
	}
}