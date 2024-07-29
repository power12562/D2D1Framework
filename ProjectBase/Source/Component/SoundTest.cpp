#include "SoundTest.h"
#include <Framework/InputSystem.h>

#include <Core/Component/AudioClip.h>

using namespace InputSystem;
using namespace SoundSystem;

SoundTest::SoundTest(GameObjectBase& gameObject)
	: ComponentBase(gameObject)
{
	audio = nullptr;

}

SoundTest::~SoundTest()
{
}

void SoundTest::Start()
{
	audio = &AddComponent<AudioClip>();
	audio->LoadClip(L"smb_coin.wav");
	
}

void SoundTest::Update()
{
	if (Input.IsKeyDown(KeyCode::Space))
	{
		audio->Play(false, ChannelGroup::sfx);


	}
	if (Input.IsKeyDown(KeyCode::P))
	{
		audio->Pause();
	}
	if (Input.IsKeyDown(KeyCode::Enter))
	{
		audio->Stop();
	}

	if (Input.IsKeyDown(KeyCode::DownArrow))
	{
		SoundSystem::FMODManager::SetVolume(ChannelGroup::music, 0.25f);
	}
	if (Input.IsKeyDown(KeyCode::UpArrow))
	{
		SoundSystem::FMODManager::SetVolume(ChannelGroup::music, 1.0f);
	}
	

}
