#pragma once
#include <Core/Component/Base/ComponentBase.h>

#include <Framework/SoundSystem.h>

class AudioClip : public ComponentBase
{
	SoundSystem::FMODManager::Sound* sound;
	std::wstring filePath;
	FMOD::Channel* playChannel;

public:
	AudioClip(GameObjectBase& gameObject);
	virtual ~AudioClip() override;

	void LoadClip(const wchar_t* path);
	void UnloadClip();
	void Play(bool isLoop, SoundSystem::ChannelGroup group);
	
	/* ������� Ŭ���� �Ͻ������մϴ�. �Ͻ����� �߿� ȣ���ϸ� �̾ ����մϴ�.*/
	void Pause();

	/* ������� Ŭ���� �����մϴ�.*/
	void Stop();
	
protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;
};
