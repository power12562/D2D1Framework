#include "SoundTest.h"
#include <Framework/InputSystem.h>
#include <Utility/Debug.h>

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
	audio->LoadAudio(L"smb_coin.wav");
	
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
	if (Input.IsKeyDown(KeyCode::Delete))
	{
		Destroy(gameObject);
	}

	if (Input.IsKeyDown(KeyCode::DownArrow))
	{
		audio->Volume = 0.5f;
	}
	if (Input.IsKeyDown(KeyCode::UpArrow))
	{
		audio->Volume = 1.0f;
	}
	DEBUG_PRINT("Volume : %f\n", audio->Volume);
	

}
