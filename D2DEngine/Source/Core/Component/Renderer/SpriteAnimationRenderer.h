#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Framework/ReferenceCounter.h"
#include "Vector/Vector2.h"

#include <list>
#include <unordered_map>
#include <map>
#include <string>
#include <d2d1.h>
#include <vector>
#undef LoadImage

struct FrameInfo //프레임 정보
{
	D2D1_RECT_F source = { 0, };	// 부분출력할 이미지 영역
	D2D_VECTOR_2F center = { 0, };
	float frameIntervalTime = 0.1f; //해당 프레임 재생 시간
};

class AnimationClip : public ReferenceCounter  //애니메이션 클립
{
	friend class SpriteAnimationRenderer; //SpriteAnimationRender를 통해서만 객체 생성 가능
public:
	std::vector<FrameInfo> frames; //프레임 모음
private:
	AnimationClip() = default;
	~AnimationClip() = default;
};

struct AnimationAsset
{
	/** 클립 경로*/
	std::wstring clipPath;
	/** 애니메이션에 사용되는 클립*/
	AnimationClip* clip = nullptr;

	/*이미지 경로*/
	std::wstring imagePath;
	/*애니메이션에 사용되는 이미지*/
	ID2D1Bitmap* const* image = nullptr;
};

class SpriteAnimationRenderer : public ComponentBase
{
	friend class WinGameApp;
	Vector2 originPos;
	Vector2 renderPos;

	/** 소멸자에서 사용되는 이터레이터*/
	std::list<SpriteAnimationRenderer*>::iterator myIter;
private:

	AnimationAsset* currentAnimation = nullptr; //현재 선택된 애니메이션
	int currentFrame = 0; //현재 재생중인 프레임
	int lastFrameIndex = 0; //현재 재생중인 프레임의 마지막 인덱스
	bool isCurrentClipEnd = true; //현재 재생중인 클립 끝낫는지
	float elapsedTime = 0; //애니메이션 진행 시간
	bool isLoop = false; //현재 애니메이션 루프 여부

	/**애니메이션 에셋 모음 <이름, <경로, 클립, 이미지>*/
	std::unordered_map<std::wstring, AnimationAsset> Animations;

	void SetRenderPos();
	void SetOriginPos();

	//static :

	/**리소스 공유용 맵 <경로, 클립>*/
	static std::map<std::wstring, AnimationClip*> clipResourceMap;
	/** 중복 체크 후 애니메이션 리소스 생성*/
	static AnimationClip* CreateAnimationClipFromFile(const wchar_t* filePath);
	/** 안전한 애니메이션 리소스 제거*/
	static void ReleaseAnimationClip(const wchar_t* filePath);

	/** 생성된 컴포넌트 리스트*/
	static std::list<SpriteAnimationRenderer*> instanceList;

#pragma region WinGameApp->Run()루프에서만 호출하는 함수들
	/** 그리기 위해 위치를 조정*/
	static void BegineRender();
	/** 그린 이후 위치를 원복 위치를 조정*/
	static void EndRender();
#pragma endregion

public:
	SpriteAnimationRenderer(GameObjectBase& gameObject);
	virtual ~SpriteAnimationRenderer() override;

	/** 해당 경로의 애니메이션 클립 파일 로드*/
	void LoadAnimationClip(const wchar_t* clipPath, const wchar_t* imagePath, const wchar_t* clipName);

	/** 해당 이름의 애니메이션 클립 해제*/
	void UnloadAnimationClip(const wchar_t* clipName);

	/** 로드된 모든 애니메이션 클립 해제*/
	void UnloadAllAnimationClip();

	/** 로드된 애니메이션 재생*/
	void SetAnimation(const wchar_t* clipName, bool isLoop = false);

	/** 설정 애니메이션 정보*/
	const AnimationAsset* GetCurrentAnimation();

	/** 현재 선택된 클립 정보*/
	AnimationClip* GetCurrentClip();

	/** 재생중인 애니메이션의 프레임 정보*/
	FrameInfo* GetCurrentFrame();

	/** 재생중인 애니메이션의 이미지 포인터*/
	ID2D1Bitmap* const* GetCurrentImage();

	/** 현재 클립의 마지막 인덱스*/
	int GetLastFrameIndex() const { return lastFrameIndex; }
	/** 현재 클립의 마지막 인덱스. 읽기 전용 프로퍼티*/
	__declspec(property(get = GetLastFrameIndex)) int LastFrameIndex;

	/** 현재 클립 종료 여부*/
	bool GetCurrentClipEnd() const { return isCurrentClipEnd; }
	/** 현재 클립 종료 여부. 읽기 전용 프로퍼티*/
	__declspec(property(get = GetCurrentClipEnd)) bool CurrentClipEnd;

	/**현재 프레임의 피봇 위치를 transform에 적용해준다.*/
	void UpdateCurrentPivot();

	/** 현제 프레임 인덱스*/
	int GetCurrentFrameIndex() const { return currentFrame; }
	__declspec(property(get = GetCurrentFrameIndex, put = SetCurrentFrameIndex)) int CurrentFrameIndex;

	/** 재생할 프레임 선택*/
	void SetCurrentFrameIndex(int frame);

	/** 현재 Animations 정보를 전달받은 경로에 json으로 저장합니다*/
	void SaveAnimationAssetToJson(const wchar_t* path);

	/** json으로 AnimationAsset을 로드합니다.*/
	void LoadAnimationAssetToJson(const wchar_t* path);

	/** 애니메이션 클립을 전달받은 경로에 txt 형식으로 저장합니다.*/
	static void SaveAnimationClipToFile(const AnimationClip& clip, const wchar_t* path);

protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;

};

