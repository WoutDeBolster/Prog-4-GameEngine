#pragma once
#include "SDL_mixer.h"
#include <mutex>

using sound_id = unsigned short;
class SoundSystem
{
public:
	SoundSystem() = default;
	virtual ~SoundSystem() = default;

	SoundSystem(const SoundSystem&) = delete;
	SoundSystem(SoundSystem&&) = delete;
	SoundSystem& operator= (const SoundSystem&) = delete;
	SoundSystem& operator= (const SoundSystem&&) = delete;

	virtual void play(const sound_id id, const float volume) = 0;
};

class ServisLocator final
{
public:
	ServisLocator() = default;
	~ServisLocator() = default;

	ServisLocator(const ServisLocator&) = delete;
	ServisLocator(ServisLocator&&) = delete;
	ServisLocator& operator= (const ServisLocator&) = delete;
	ServisLocator& operator= (const ServisLocator&&) = delete;

	static SoundSystem& GetSoundSystem()
	{
		return *m_ss_Instance.get();
	}
	static void RegisterSoundSystem(std::shared_ptr<SoundSystem> ss)
	{
		m_ss_Instance = ss;
	}

private:
	static std::shared_ptr<NullSoundSystem> m_Default_ss;
	static std::shared_ptr<SoundSystem> m_ss_Instance;
};
std::shared_ptr<NullSoundSystem>  ServisLocator::m_Default_ss;
std::shared_ptr<SoundSystem> ServisLocator::m_ss_Instance = m_Default_ss;

class SdlSoundSystem final : public SoundSystem
{
public:
	SdlSoundSystem() = default;
	virtual ~SdlSoundSystem() = default;

	SdlSoundSystem(const SdlSoundSystem&) = delete;
	SdlSoundSystem(SdlSoundSystem&&) = delete;
	SdlSoundSystem& operator= (const SdlSoundSystem&) = delete;
	SdlSoundSystem& operator= (const SdlSoundSystem&&) = delete;

	//void play(const sound_id id, const float volume) override
	//{

	//}
};

class NullSoundSystem final : public SoundSystem
{
	void play(const sound_id id, const float volume) override {}
};