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

struct FrameInfo //������ ����
{
	D2D1_RECT_F source = { 0, };	// �κ������ �̹��� ����
	D2D_VECTOR_2F center = { 0, };
	float frameIntervalTime = 0.1f; //�ش� ������ ��� �ð�
};

class AnimationClip : public ReferenceCounter  //�ִϸ��̼� Ŭ��
{
	friend class SpriteAnimationRenderer; //SpriteAnimationRender�� ���ؼ��� ��ü ���� ����
public:
	std::vector<FrameInfo> frames; //������ ����
private:
	AnimationClip() = default;
	~AnimationClip() = default;
};

struct AnimationAsset
{
	/** Ŭ�� ���*/
	std::wstring clipPath;
	/** �ִϸ��̼ǿ� ���Ǵ� Ŭ��*/
	AnimationClip* clip = nullptr;

	/*�̹��� ���*/
	std::wstring imagePath;
	/*�ִϸ��̼ǿ� ���Ǵ� �̹���*/
	ID2D1Bitmap* const* image = nullptr;
};

class SpriteAnimationRenderer : public ComponentBase
{
	friend class WinGameApp;
	Vector2 originPos;
	Vector2 renderPos;

	/** �Ҹ��ڿ��� ���Ǵ� ���ͷ�����*/
	std::list<SpriteAnimationRenderer*>::iterator myIter;
private:

	AnimationAsset* currentAnimation = nullptr; //���� ���õ� �ִϸ��̼�
	int currentFrame = 0; //���� ������� ������
	int lastFrameIndex = 0; //���� ������� �������� ������ �ε���
	bool isCurrentClipEnd = true; //���� ������� Ŭ�� ��������
	float elapsedTime = 0; //�ִϸ��̼� ���� �ð�
	bool isLoop = false; //���� �ִϸ��̼� ���� ����

	/**�ִϸ��̼� ���� ���� <�̸�, <���, Ŭ��, �̹���>*/
	std::unordered_map<std::wstring, AnimationAsset> Animations;

	void SetRenderPos();
	void SetOriginPos();

	//static :

	/**���ҽ� ������ �� <���, Ŭ��>*/
	static std::map<std::wstring, AnimationClip*> clipResourceMap;
	/** �ߺ� üũ �� �ִϸ��̼� ���ҽ� ����*/
	static AnimationClip* CreateAnimationClipFromFile(const wchar_t* filePath);
	/** ������ �ִϸ��̼� ���ҽ� ����*/
	static void ReleaseAnimationClip(const wchar_t* filePath);

	/** ������ ������Ʈ ����Ʈ*/
	static std::list<SpriteAnimationRenderer*> instanceList;

#pragma region WinGameApp->Run()���������� ȣ���ϴ� �Լ���
	/** �׸��� ���� ��ġ�� ����*/
	static void BegineRender();
	/** �׸� ���� ��ġ�� ���� ��ġ�� ����*/
	static void EndRender();
#pragma endregion

public:
	SpriteAnimationRenderer(GameObjectBase& gameObject);
	virtual ~SpriteAnimationRenderer() override;

	/** �ش� ����� �ִϸ��̼� Ŭ�� ���� �ε�*/
	void LoadAnimationClip(const wchar_t* clipPath, const wchar_t* imagePath, const wchar_t* clipName);

	/** �ش� �̸��� �ִϸ��̼� Ŭ�� ����*/
	void UnloadAnimationClip(const wchar_t* clipName);

	/** �ε�� ��� �ִϸ��̼� Ŭ�� ����*/
	void UnloadAllAnimationClip();

	/** �ε�� �ִϸ��̼� ���*/
	void SetAnimation(const wchar_t* clipName, bool isLoop = false);

	/** ���� �ִϸ��̼� ����*/
	const AnimationAsset* GetCurrentAnimation();

	/** ���� ���õ� Ŭ�� ����*/
	AnimationClip* GetCurrentClip();

	/** ������� �ִϸ��̼��� ������ ����*/
	FrameInfo* GetCurrentFrame();

	/** ������� �ִϸ��̼��� �̹��� ������*/
	ID2D1Bitmap* const* GetCurrentImage();

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

	/** ���� ������ �ε���*/
	int GetCurrentFrameIndex() const { return currentFrame; }
	__declspec(property(get = GetCurrentFrameIndex, put = SetCurrentFrameIndex)) int CurrentFrameIndex;

	/** ����� ������ ����*/
	void SetCurrentFrameIndex(int frame);

	/** ���� Animations ������ ���޹��� ��ο� json���� �����մϴ�*/
	void SaveAnimationAssetToJson(const wchar_t* path);

	/** json���� AnimationAsset�� �ε��մϴ�.*/
	void LoadAnimationAssetToJson(const wchar_t* path);

	/** �ִϸ��̼� Ŭ���� ���޹��� ��ο� txt �������� �����մϴ�.*/
	static void SaveAnimationClipToFile(const AnimationClip& clip, const wchar_t* path);

protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;

};

