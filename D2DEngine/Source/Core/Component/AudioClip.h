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

	/* ����� �׷�*/
	SoundSystem::ChannelGroup group;

	/* ����� Ŭ�� ���*/
	void Play(bool isLoop);

	/* ������� Ŭ���� �Ͻ������մϴ�. �Ͻ����� �߿� ȣ���ϸ� �̾ ����մϴ�.*/
	void Pause();

	/* ������� Ŭ���� �����մϴ�.*/
	void Stop();

	/* ����� Ŭ���� �Ҹ��� �����մϴ�.*/
	void SetVolume(float volume);
	/* ���� ���� ũ��.*/
	float GetVolume() { return volume; }
	/* ����� Ŭ���� �Ҹ� ũ��*/
	__declspec(property(put = SetVolume, get = GetVolume)) float Volume;
	
	
protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;
};
