//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "SoundType.h"
#include <raylib.h>
#include <unordered_map>


class SoundManager {
private:
	std::unordered_map<SoundType, Sound> m_sounds;

	void LoadSounds();

public:
	void PlaySound(SoundType soundType) const;
};