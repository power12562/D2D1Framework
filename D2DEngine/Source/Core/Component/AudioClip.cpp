#include "AudioClip.h"

#include <Utility/Debug.h>

using namespace SoundSystem; 

AudioClip::AudioClip(GameObjectBase& gameObject)
	: ComponentBase(gameObject)
{
	playChannel = nullptr;
	sound = nullptr;
	filePath.clear();
	volume = 1.0f;
	group = ChannelGroup::null;
}

AudioClip::~AudioClip()
{
	UnloadAudio();
}

void AudioClip::LoadAudio(const wchar_t* path)
{
	if (sound != nullptr)
	{
		UnloadAudio();
	}
	filePath = path;
	sound = FMODManager::CreateSound(path);
}						  

void AudioClip::UnloadAudio()
{
	if (sound != nullptr)
	{
		sound = nullptr;
		FMODManager::ReleaseSound(filePath.c_str());
		filePath.clear();
	}
}

FMOD_RESULT F_CALLBACK EndOfSoundCallback(FMOD_CHANNELCONTROL* channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void* commanddata1, void* commanddata2)
{
	if (callbacktype == FMOD_CHANNELCONTROL_CALLBACK_END)
	{
		void* userData = nullptr;
		reinterpret_cast<FMOD::Channel*>(channelcontrol)->getUserData(&userData);
		FMOD::Channel** playChannel = static_cast<FMOD::Channel**>(userData);
		*playChannel = nullptr;
	}
	return FMOD_OK;
}

void AudioClip::Play(bool isLoop)
{
	if (sound == nullptr || playChannel != nullptr)
	{
		return;
	}
	int loop = isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	(**sound)->setMode(loop);
	playChannel = FMODManager::PlaySound(sound, group);																						    
	playChannel->setUserData(&playChannel);
	playChannel->setCallback(EndOfSoundCallback);
	playChannel->setVolume(volume);
}

void AudioClip::Pause()
{
	if (playChannel)
	{
		bool isPaused = false;
		if (FMODManager::CheckErr(playChannel->getPaused(&isPaused)))
		{
			playChannel->setPaused(!isPaused);
		}	
	}
}

void AudioClip::Stop()
{
	if (playChannel)
	{
		playChannel->stop();
	}
}

void AudioClip::SetVolume(float _volume)
{
	if (playChannel)
	{
		playChannel->setVolume(_volume);
	}
	volume = _volume;
}
