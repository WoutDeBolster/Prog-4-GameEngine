#include "MiniginPCH.h"
#include "SoundSystem.h"

NullSoundSystem ServisLocator::m_ss_Default;
std::shared_ptr<SoundSystem> ServisLocator::m_ss_Instance = std::make_shared<NullSoundSystem>(m_ss_Default);