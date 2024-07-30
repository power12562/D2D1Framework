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

		/* ���� ���ҽ��� �����մϴ�.*/
		static Sound* CreateSound(const wchar_t* path);

		/* ���� ���ҽ��� �����մϴ�.*/
		static void ReleaseSound(const wchar_t* path);

		/* ���带 ����մϴ�. ������� ä���� ��ȯ�մϴ�.*/
		static FMOD::Channel* PlaySound(Sound* sound, ChannelGroup group);

		/* Ư�� �׷쿡 �Ҹ��� �����մϴ�.*/
		static void SetVolumeGroup(ChannelGroup group, float volume);
		/* Ư�� �׷쿡 �Ҹ� ũ��.*/
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