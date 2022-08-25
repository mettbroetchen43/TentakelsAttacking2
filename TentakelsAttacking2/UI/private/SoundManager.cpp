//
// Purpur Tentakel
// 24.08.2022
//

#include "SoundManager.h"
#include <iostream>
#include <filesystem>

void SoundManager::LoadSounds() {
	for (int i = 0; i < m_files.size(); ++i) {
		Sound sound = LoadSound(("Sounds/" + m_files[i]).c_str());
		m_sounds[static_cast<SoundType>(i)] = sound;
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
