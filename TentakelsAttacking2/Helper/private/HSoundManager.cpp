//
// Purpur Tentakel
// 24.08.2022
//

#include "HSoundManager.h"
#include "UIEvents.hpp"
#include "HRandom.h"
#include <filesystem>

void SoundManager::LoadSounds() {
	for (int i = 0; i < m_files.size(); ++i) {
		Sound sound = LoadSound(("Sounds/" + m_files[i]).c_str());
		m_sounds[static_cast<SoundType>(i)] = sound;
	}

	for (int i = 0; i < m_hoverSounds.size(); ++i) {
		Sound sound = LoadSound("Sounds/hovered_std.mp3");
		m_hoverSounds.at(i) = sound;
	}

	std::string files = "Sounds/TextSounds";
	for (auto const& entry : std::filesystem::directory_iterator(files)) {
		Sound sound = LoadSound(entry.path().string().c_str());
		m_textSounds.push_back(sound);
	}
}

void SoundManager::PlaySound(SoundType soundType) {
	if (soundType == SoundType::HOVER_STD) {
		PlayHoveredSound();
		return;
	}
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
void SoundManager::PlayHoveredSound() {
	if (m_hoverIndex >= m_hoverSounds.size()) {
		m_hoverIndex = 0;
	}

	::PlaySound(m_hoverSounds.at(m_hoverIndex));
	++m_hoverIndex;
}

SoundManager::SoundManager() {
	InitAudioDevice();
	LoadSounds();
}
SoundManager::~SoundManager() {
	for (auto& [_, sound] : m_sounds) {
		UnloadSound(sound);
	}
	CloseAudioDevice();
}

void SoundManager::OnEvent(Event const& event) {
	if (auto const soundEvent = dynamic_cast<PlaySoundEvent const*>(&event)) {
		PlaySound(soundEvent->GetSoundType());
	}
	if (auto const soundEvent = dynamic_cast<PlayTextSoundEvent const*>(&event)) {
		PlayTextSound();
	}
}
