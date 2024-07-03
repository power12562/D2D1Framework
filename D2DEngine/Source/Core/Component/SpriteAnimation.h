#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Framework/ReferenceCounter.h"
#include <list>
#include <map>
#include <string>
#include <d2d1.h>
#include <vector>
#undef LoadImage

struct FrameInfo //������ ����
{
	D2D1_RECT_F source = { 0, };	// �κ������ �̹��� ����
	D2D_VECTOR_2F center = { 0, };
	float frameIntervalTime = 0.1f; //�ش� ������ ��� �ð�
};

class SpriteAnimation : public ComponentBase
{
private:
	class AnimationClip : public ReferenceCounter  //�ִϸ��̼� Ŭ��
	{
		friend class SpriteAnimation; //SpriteAnimationRender�� ���ؼ��� ��ü ���� ����
	public:
		std::vector<FrameInfo> frames; //������ ����
	private:
		AnimationClip() = default;
		~AnimationClip() = default;
	};
	AnimationClip* CurrentClip = nullptr; //���� ���õ� Ŭ��
	int currentFrame = 0; //���� ������� ������
	int lastFrameIndex = 0; //���� ������� �������� ������ �ε���
	bool isCurrentClipEnd = true; //���� ������� Ŭ�� ��������
	float elapsedTime = 0; //�ִϸ��̼� ���� �ð�
	bool isLoop = false; //���� �ִϸ��̼� ���� ����

	/**�ִϸ��̼� Ŭ�� ���� <�̸�, <���, Ŭ��>>*/
	std::map<std::wstring, std::pair<std::wstring, AnimationClip*>> Animations;

	//static :
	/**���ҽ� ������ �� <���, Ŭ��>*/
	static std::map<std::wstring, AnimationClip*> clipResourceMap;
	/** �ߺ� üũ �� �ִϸ��̼� ���ҽ� ����*/
	static AnimationClip* CreateAnimationClipFromFile(const wchar_t* filePath);
	/** ������ �ִϸ��̼� ���ҽ� ����*/
	static void ReleaseAnimationClip(const wchar_t* filePath);

public:
	SpriteAnimation(GameObjectBase& gameObject);
	virtual ~SpriteAnimation() override;

	/** �ش� ����� �ִϸ��̼� Ŭ�� ���� �ε�*/
	void LoadAnimationClip(const wchar_t* path, const wchar_t* clipName);

	/** �ش� �̸��� �ִϸ��̼� Ŭ�� ����*/
	void UnloadAnimationClip(const wchar_t* clipName);

	/** �ε�� �ִϸ��̼� ���*/
	void SetAnimationClip(const wchar_t* clipName, bool isLoop = false);

	/** ������� �ִϸ��̼��� ������ ����*/
	FrameInfo* const GetCurrentFrame();

	/** ���� Ŭ���� ������ �ε���*/
	int GetLastFrameIndex() const { return lastFrameIndex; }
	/** ���� Ŭ���� ������ �ε���. �б� ���� ������Ƽ*/
	__declspec(property(get = GetLastFrameIndex)) int LastFrameIndex;

	/** ���� Ŭ�� ���� ����*/
	bool GetCurrentClipEnd() const { return isCurrentClipEnd; }
	/** ���� Ŭ�� ���� ����. �б� ���� ������Ƽ*/
	__declspec(property(get = GetCurrentClipEnd)) bool CurrentClipEnd;

	/**���� �������� �Ǻ� ��ġ�� transform�� �������ش�.*/
	void UpdateCurrentPivot();

protected:
	virtual void Update() override;

};