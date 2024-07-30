#include "BombSoundCtrl.h"
#include <Framework/WorldManager.h>

#include <Core/Component/AudioClip.h>

BombSoundCtrl::BombSoundCtrl(GameObjectBase& gameObject)
	: ComponentBase(gameObject)
{
	audioClip = &GetComponent<AudioClip>();
	audioClip->LoadAudio(L"Resource/bomb/bomb.wav");
	audioClip->group = SoundSystem::ChannelGroup::sfx;
	audioClip->Volume = 2.0f;
}
BombSoundCtrl::~BombSoundCtrl()
{
}

void BombSoundCtrl::Start()
{
	audioClip->Play();
}

void BombSoundCtrl::Update()
{
	if (audioClip->IsPlay() == false)
	{
		WorldManager::DelGameObject(gameObject);
	}
}
