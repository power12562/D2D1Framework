#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Framework/ReferenceCounter.h"
#include <map>
#include <string>
#include <d2d1.h>
#include <vector>

struct FrameInfo //������ ����
{
	D2D1_RECT_F source = { 0, };	// �κ������ �̹��� ����
	D2D_VECTOR_2F center = { 0, };
	float frameIntervalTime = 0.1f; //�ش� ������ ��� �ð�
};

class SpriteAnimationRenderer : public ComponentBase
{	
private:
	class AnimationClip : public ReferenceCounter  //�ִϸ��̼� Ŭ��
	{
		friend class SpriteAnimationRenderer; //SpriteAnimationRender�� ���ؼ��� ��ü ���� ����
	public:
		std::vector<FrameInfo> frames; //������ ����
	private:
		AnimationClip() = default;
		~AnimationClip() = default;
	};
	AnimationClip* CurrentClip = nullptr; //���� ���õ� Ŭ��
	int currentFrame = 0; //���� ������� ������
	bool isCurrentClipEnd = true; //���� ������� Ŭ�� ��������
	float elapsedTime = 0; //�ִϸ��̼� ���� �ð�

	/**�ִϸ��̼� Ŭ�� ���� <�̸�, Ŭ��>*/
	std::map<std::wstring, std::pair<std::wstring ,AnimationClip*>> Animations;

	/**���ҽ� ������ �� <���, Ŭ��>*/
	static std::map<std::wstring, AnimationClip*> clipResourceMap; 
	/** �ߺ� üũ �� �ִϸ��̼� ���ҽ� ����*/
	static AnimationClip* CreateAnimationClipFromFile(const wchar_t* filePath);
	/** ������ �ִϸ��̼� ���ҽ� ����*/
	static void ReleaseAnimationClip(const wchar_t* filePath);
public:
	SpriteAnimationRenderer(GameObjectBase& gameObject);
	virtual ~SpriteAnimationRenderer() override;

	/** �ش� ����� �ִϸ��̼� Ŭ�� ���� �ε�*/
	void LoadAnimationClip(const wchar_t* path, const wchar_t* clipName);

	/** �ش� �̸��� �ִϸ��̼� Ŭ�� ����*/
	void UnloadAnimationClip(const wchar_t* clipName);

	/** �ε�� �ִϸ��̼� ���*/
	void SetAnimationClip(const wchar_t* clipName);

protected:
	virtual void Update() override;
	virtual void Render() override;

};