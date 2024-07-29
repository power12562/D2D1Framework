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
	
	/* 재생중인 클립을 일시정지합니다. 일시정지 중에 호출하면 이어서 재생합니다.*/
	void Pause();

	/* 재생중인 클립을 정지합니다.*/
	void Stop();
	
protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;
};
