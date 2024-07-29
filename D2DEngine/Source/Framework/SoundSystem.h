#pragma once
#include <../ThirdParty/fmod/headers/fmod.hpp>

class FMODManager
{
public:
	FMODManager();
	~FMODManager();
	void Init();

	static void CheckErr(FMOD_RESULT result);
private:				
	bool IsInit;

	FMOD::System* system;
};


namespace SoundSystem
{
	extern FMODManager Fmod;
};