#pragma once
#include "SDL_mixer.h"
#include <mutex>
#include "AudioClip.h"
#include <vector>
#include <memory>

using sound_id = unsigned short;
class SoundSystem
{
public:
	virtual ~SoundSystem() = default;

	virtual void play(const sound_id id, const int volume) = 0;
	virtual void RegisterSound(const sound_id id, const std::string& path) = 0;
	virtual void InitSoundSystem() = 0;
};

class SdlSoundSystem final : public SoundSystem
{
public:
	SdlSoundSystem() = default;
	virtual ~SdlSoundSystem()
	{
		Mix_CloseAudio();
	}

	void AddAudio(std::shared_ptr<AudioClip> audio)
	{
		m_AudioClips.push_back(audio);
	}

	void InitSoundSystem()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "coudnt open mixerAudio" << Mix_GetError() << std::endl;
		}
		m_AudioClips.resize(50);
	}

	void play(const sound_id id, const int volume) override
	{
		auto audioClip = m_AudioClips[id];
		if (audioClip->IsLoaded() == false)
		{
			audioClip->LoadSound();
		}
		audioClip->SetVolume(volume);
		audioClip->PlaySound();
	}

	void RegisterSound(const sound_id id, const std::string& path)
	{
		auto audioClip = std::make_shared<AudioClip>(path);
		m_AudioClips[id] = audioClip;
	};
private:
	std::vector<std::shared_ptr<AudioClip>> m_AudioClips;
};

class NullSoundSystem final : public SoundSystem
{
private:
	void InitSoundSystem() override {}
	void play(const sound_id, const int) override {}
	void RegisterSound(const sound_id, const std::string&) {}
};

class ServisLocator final
{
public:
	static SoundSystem& GetSoundSystem()
	{
		return *m_ss_Instance.get();
	}
	static void RegisterSoundSystem(std::shared_ptr<SoundSystem> ss)
	{
		m_ss_Instance = ss;
	}

private:
	static NullSoundSystem m_ss_Default;
	static std::shared_ptr<SoundSystem> m_ss_Instance;
};

class LogginSoundSystem final : public SoundSystem
{
public:
	LogginSoundSystem(std::shared_ptr<SoundSystem> ss) : m_ss_real(ss) {}
	~LogginSoundSystem() = default;

	void InitSoundSystem() override
	{
		m_ss_real->InitSoundSystem();
	}
	void RegisterSound(const sound_id id, const std::string& path) override
	{
		m_ss_real->RegisterSound(id, path);
	}
	void play(const sound_id id, const int volume) override
	{
		m_ss_real->play(id, volume);
	}

private:
	std::shared_ptr<SoundSystem> m_ss_real;
};