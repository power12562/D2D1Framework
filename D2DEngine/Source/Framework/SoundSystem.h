#pragma once	 
#undef PlaySound

#include <../ThirdParty/fmod/headers/fmod.hpp>

#include <Framework/ReferenceCounter.h>
#include <unordered_map>
#include <string>

namespace SoundSystem
{
	enum class ChannelGroup
	{
		master,
		music,
		sfx,
		null
	};

	class FMODManager
	{	
		friend class WinGameApp;
	public:
		class Sound : public ReferenceCounter
		{
			friend class FMODManager;
		public:
			FMOD::Sound* operator*()
			{
				return this->fmodSound;
			}
		private:
			Sound()
			{
				fmodSound = nullptr;
			}
			~Sound()
			{
				fmodSound->release();
			}
			operator FMOD::Sound* ()
			{
				return fmodSound;
			}
			operator FMOD::Sound** ()
			{
				return &fmodSound;
			}
			FMOD::Sound* fmodSound;
		};

		static void Init();
		static void UnInit();
		static bool CheckErr(FMOD_RESULT result);

		/* 사운드 리소스를 생성합니다.*/
		static Sound* CreateSound(const wchar_t* path);

		/* 사운드 리소스를 해제합니다.*/
		static void ReleaseSound(const wchar_t* path);

		/* 사운드를 재생합니다. 재생중인 채널을 반환합니다.*/
		static FMOD::Channel* PlaySound(Sound* sound, ChannelGroup group);

		/* 특정 그룹에 소리를 조절합니다.*/
		static void SetVolumeGroup(ChannelGroup group, float volume);
		/* 특정 그룹에 소리 크기.*/
		static float GetVolumeGroup(ChannelGroup group);

	private:
		FMODManager() = delete;
		~FMODManager() = delete;

		static bool IsInit;
		static std::unordered_map<std::wstring, Sound*> soundMap;
		static FMOD::System* system;
		static FMOD::ChannelGroup* masterGroup;
		static FMOD::ChannelGroup* musicGroup;
		static FMOD::ChannelGroup* sfxGroup;
	};

};