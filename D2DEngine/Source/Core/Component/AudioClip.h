#pragma once
#include <Core/Component/Base/ComponentBase.h>

#include <Framework/SoundSystem.h>

class AudioClip : public ComponentBase
{
	SoundSystem::FMODManager::Sound* sound;
	std::wstring filePath;
	FMOD::Channel* playChannel;
	float volume;
public:
	AudioClip(GameObjectBase& gameObject);
	virtual ~AudioClip() override;

	void LoadAudio(const wchar_t* path);
	void UnloadAudio();

	/* 재생할 그룹*/
	SoundSystem::ChannelGroup group;

	/* 오디오 클립 재생*/
	void Play(bool isLoop);

	/* 재생중인 클립을 일시정지합니다. 일시정지 중에 호출하면 이어서 재생합니다.*/
	void Pause();

	/* 재생중인 클립을 정지합니다.*/
	void Stop();

	/* 재생할 클립의 소리를 설정합니다.*/
	void SetVolume(float volume);
	/* 현재 볼륨 크기.*/
	float GetVolume() { return volume; }
	/* 재생할 클립의 소리 크기*/
	__declspec(property(put = SetVolume, get = GetVolume)) float Volume;
	
	
protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;
};
