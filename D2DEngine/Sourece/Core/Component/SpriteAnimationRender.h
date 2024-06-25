#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <map>
#include <string>
#include <d2d1.h>

struct FrameInfo //������ ����
{
	D2D1_RECT_F source = { 0, };	// �κ������ �̹��� ����
	D2D_VECTOR_2F center = { 0, };
	float frameIntervalTime = 0.1f; //�ش� ������ ��� �ð�
};

class SpriteAnimationRender : public ComponentBase
{	
private:
	class AnimaitionClip //�ִϸ��̼� Ŭ��
	{
	public:
		~AnimaitionClip() { delete[] Frames; }
		std::wstring name; //�ִϸ��̼� Ŭ�� �̸�
		FrameInfo* Frames = nullptr; //������ �����̳�
		int frameCount = 0;			// ��ü ������ ��
	};
	AnimaitionClip* CurrentClip = nullptr; //���� ���õ� Ŭ��
	int CurrentFrame = 0; //���� ������� ������
	bool isCurrentClipEnd = true; //���� ������� Ŭ�� ��������
	float elapsedTime = 0; //�ִϸ��̼� ���� �ð�

	static std::map<std::wstring, AnimaitionClip> resourceMap; //���ҽ� ������ ��

public:
	SpriteAnimationRender(GameObjectBase& gameObject);
	virtual ~SpriteAnimationRender() override;
	
protected:
	virtual void Update() override;
	virtual void Render() override;

};