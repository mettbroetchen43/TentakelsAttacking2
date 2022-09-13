//
// Purpur Tentakel
// 24.08.2022
//

#include "SoundManager.h"
#include "Events.h"
#include "Random.h"
#include <filesystem>

void SoundManager::LoadSounds() {
	for (int i = 0; i < m_files.size(); ++i) {
		Sound sound = LoadSound(("Sounds/" + m_files[i]).c_str());
		m_sounds[static_cast<SoundType>(i)] = sound;
	}

	std::string files = "Sounds/TextSounds";
	for (auto const& entry : std::filesystem::directory_iterator(files)) {
		Sound sound = LoadSound(entry.path().string().c_str());
		m_textSounds.push_back(sound);
	}
}

void SoundManager::OnEvent(Event const& event) {
	if (auto const soundEvent = dynamic_cast<PlaySoundEvent const*>(&event)) {
		PlaySound(soundEvent->GetSoundType());
	}
	if (auto const soundEvent = dynamic_cast<PlayTextSoundEvent const*>(&event)) {
		PlayTextSound();
	}
}

SoundManager::SoundManager() {
	InitAudioDevice();
	LoadSounds();
}
SoundManager::~SoundManager() {
	for (auto& [_,sound] : m_sounds) {
		UnloadSound(sound);
	}
	CloseAudioDevice();
}

void SoundManager::PlaySound(SoundType soundType) const {
	::PlaySound(m_sounds.at(soundType));
}
void SoundManager::PlayTextSound() const {
	static unsigned long long lastIndex = 0;
	Random& random = Random::GetInstance();

	unsigned long long nextIndex;
	do {
		nextIndex = random.random(m_textSounds.size());
	} while (lastIndex == nextIndex);

	::PlaySound(m_textSounds.at(nextIndex));
	lastIndex = nextIndex;
}
