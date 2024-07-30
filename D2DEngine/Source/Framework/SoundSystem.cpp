#include "SoundSystem.h"	
#include "../ThirdParty/fmod/headers/fmod_errors.h"

#include <Utility/Debug.h>
#include <Utility/JsonUtility.h>

#include <cassert>

#undef PlaySound

using namespace SoundSystem;

FMOD::System* FMODManager::system = nullptr;
bool FMODManager::IsInit = false;
std::unordered_map<std::wstring, FMODManager::Sound*> FMODManager::soundMap;
FMOD::ChannelGroup* FMODManager::masterGroup;
FMOD::ChannelGroup* FMODManager::musicGroup;
FMOD::ChannelGroup* FMODManager::sfxGroup;

void FMODManager::Init()
{
	IsInit = true;

	FMOD_RESULT result = FMOD::System_Create(&system);
	if(!CheckErr(result))
	{
		assert(!"FMOD System Create Fail");
	}
	result = system->init(32, FMOD_INIT_NORMAL, nullptr);
	if (!CheckErr(result))
	{
		assert(!"FMOD System init Fail");
	}
	result = system->getMasterChannelGroup(&masterGroup);
	if (!CheckErr(result))
	{
		assert(!"FMOD getMasterChannelGroup Fail");
	}
	system->createChannelGroup("MusicGroup", &musicGroup);
	if (!CheckErr(result))
	{
		assert(!"FMOD createChannelGroup Fail");
	}
	system->createChannelGroup("SFXGroup", &sfxGroup);
	if (!CheckErr(result))
	{
		assert(!"FMOD createChannelGroup Fail");
	}
	result = masterGroup->addGroup(musicGroup);
	if (!CheckErr(result))
	{
		assert(!"FMOD addGroup Fail");
	}
	result = masterGroup->addGroup(sfxGroup);
	if (!CheckErr(result))
	{
		assert(!"FMOD addGroup Fail");
	}
	
}
void FMODManager::UnInit()
{

}

bool FMODManager::CheckErr(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		DEBUG_PRINT("FOMD : %s", FMOD_ErrorString(result));
		return false;
	}
	return true;
}

FMODManager::Sound* FMODManager::CreateSound(const wchar_t* path)
{	
	auto iter = soundMap.find(path);
	if (iter != soundMap.end())
	{
		iter->second->AddRef();
		return iter->second;
	}

	//없으면 생성
	soundMap[path] = new Sound;
	FMOD_RESULT result = system->createSound(JsonConvert::wstring_to_utf8(path).c_str(), FMOD_DEFAULT, 0, (FMOD::Sound**)*soundMap[path]);
	if(!CheckErr(result))
	{
		return nullptr;
	}
	return soundMap[path];
}

void SoundSystem::FMODManager::ReleaseSound(const wchar_t* path)
{
	auto iter = soundMap.find(path);
	if (iter != soundMap.end())
	{
		ULONG refCount = iter->second->Release();
		if (refCount == 0)
		{
			soundMap.erase(iter);
		}
	}
}

FMOD::Channel* SoundSystem::FMODManager::PlaySound(Sound* sound, ChannelGroup group)
{
	FMOD::ChannelGroup* channelGroup;
	switch (group)
	{
	case SoundSystem::ChannelGroup::master:
		channelGroup = masterGroup;
		break;
	case SoundSystem::ChannelGroup::music:
		channelGroup = musicGroup;
		break;
	case SoundSystem::ChannelGroup::sfx:
		channelGroup = sfxGroup;
		break;
	default:
		channelGroup = nullptr;
		break;
	}
	FMOD::Channel* channel;	
	system->playSound(*sound, channelGroup, false, &channel);
	return channel;
}


void SoundSystem::FMODManager::SetVolumeGroup(ChannelGroup group, float volume)
{
	switch (group)
	{
	case SoundSystem::ChannelGroup::master:
		masterGroup->setVolume(volume);
		break;
	case SoundSystem::ChannelGroup::music:
		musicGroup->setVolume(volume);
		break;
	case SoundSystem::ChannelGroup::sfx:
		sfxGroup->setVolume(volume);
		break;
	default:
		DEBUG_PRINT("존재하지 않는 채널 입니다.");
		break;
	}
}

float SoundSystem::FMODManager::GetVolumeGroup(ChannelGroup group)
{
	float volume;
	switch (group)
	{
	case SoundSystem::ChannelGroup::master:
		masterGroup->getVolume(&volume);
		break;
	case SoundSystem::ChannelGroup::music:
		musicGroup->getVolume(&volume);
		break;
	case SoundSystem::ChannelGroup::sfx:
		sfxGroup->getVolume(&volume);
		break;
	default:
		DEBUG_PRINT("존재하지 않는 채널 입니다.");
		volume = 0.f;
		break;
	}
	return volume;
}
