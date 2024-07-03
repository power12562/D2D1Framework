#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Framework/ReferenceCounter.h"
#include <list>
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

class SpriteAnimation : public ComponentBase
{
private:
	class AnimationClip : public ReferenceCounter  //애니메이션 클립
	{
		friend class SpriteAnimation; //SpriteAnimationRender를 통해서만 객체 생성 가능
	public:
		std::vector<FrameInfo> frames; //프레임 모음
	private:
		AnimationClip() = default;
		~AnimationClip() = default;
	};
	AnimationClip* CurrentClip = nullptr; //현재 선택된 클립
	int currentFrame = 0; //현재 재생중인 프레임
	int lastFrameIndex = 0; //현재 재생중인 프레임의 마지막 인덱스
	bool isCurrentClipEnd = true; //현재 재생중인 클립 끝낫는지
	float elapsedTime = 0; //애니메이션 진행 시간
	bool isLoop = false; //현재 애니메이션 루프 여부

	/**애니메이션 클립 모음 <이름, <경로, 클립>>*/
	std::map<std::wstring, std::pair<std::wstring, AnimationClip*>> Animations;

	//static :
	/**리소스 공유용 맵 <경로, 클립>*/
	static std::map<std::wstring, AnimationClip*> clipResourceMap;
	/** 중복 체크 후 애니메이션 리소스 생성*/
	static AnimationClip* CreateAnimationClipFromFile(const wchar_t* filePath);
	/** 안전한 애니메이션 리소스 제거*/
	static void ReleaseAnimationClip(const wchar_t* filePath);

public:
	SpriteAnimation(GameObjectBase& gameObject);
	virtual ~SpriteAnimation() override;

	/** 해당 경로의 애니메이션 클립 파일 로드*/
	void LoadAnimationClip(const wchar_t* path, const wchar_t* clipName);

	/** 해당 이름의 애니메이션 클립 해제*/
	void UnloadAnimationClip(const wchar_t* clipName);

	/** 로드된 애니메이션 재생*/
	void SetAnimationClip(const wchar_t* clipName, bool isLoop = false);

	/** 재생중인 애니메이션의 프레임 정보*/
	FrameInfo* const GetCurrentFrame();

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

protected:
	virtual void Update() override;

};