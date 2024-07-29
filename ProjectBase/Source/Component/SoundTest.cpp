#include "SoundTest.h"
#include <Framework/SoundSystem.h>
#include <Framework/InputSystem.h>

using namespace InputSystem;

SoundTest::SoundTest(GameObjectBase& gameObject)
	: ComponentBase(gameObject)
{

}

SoundTest::~SoundTest()
{
}

void SoundTest::Update()
{

	if (Input.IsKeyDown(KeyCode::Space))
	{
		//Play

	}
	

}
