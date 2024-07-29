#include "SoundSystem.h"	
#include "../ThirdParty/fmod/headers/fmod_errors.h"

#include <Utility/Debug.h>


#include <cassert>

namespace SoundSystem
{
	FMODManager Fmod;
};

using namespace SoundSystem;

void FMODManager::Init()
{
	IsInit = true;

	FMOD_RESULT result = FMOD::System_Create(&system);
	CheckErr(result);

	result = system->init(32, FMOD_INIT_NORMAL, nullptr);

	
}
void FMODManager::CheckErr(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		assert(!"FMOD ERROR");
		DEBUG_PRINT("%s", FMOD_ErrorString(result));
		Fmod.IsInit = false;
	}
}

FMODManager::FMODManager()
{
	system = nullptr;
	IsInit = false;


}

FMODManager::~FMODManager()
{
}
