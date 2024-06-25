#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <map>
#include <string>
#include <d2d1.h>

struct FrameInfo //프레임 정보
{
	D2D1_RECT_F source = { 0, };	// 부분출력할 이미지 영역
	D2D_VECTOR_2F center = { 0, };
	float frameIntervalTime = 0.1f; //해당 프레임 재생 시간
};

class SpriteAnimationRender : public ComponentBase
{	
private:
	class AnimaitionClip //애니메이션 클립
	{
	public:
		~AnimaitionClip() { delete[] Frames; }
		std::wstring name; //애니메이션 클립 이름
		FrameInfo* Frames = nullptr; //프레임 컨테이너
		int frameCount = 0;			// 전체 프레임 수
	};
	AnimaitionClip* CurrentClip = nullptr; //현재 선택된 클립
	int CurrentFrame = 0; //현재 재생중인 프레임
	bool isCurrentClipEnd = true; //현재 재생중인 클립 끝낫는지
	float elapsedTime = 0; //애니메이션 진행 시간

	static std::map<std::wstring, AnimaitionClip> resourceMap; //리소스 공유용 맵

public:
	SpriteAnimationRender(GameObjectBase& gameObject);
	virtual ~SpriteAnimationRender() override;
	
protected:
	virtual void Update() override;
	virtual void Render() override;

};