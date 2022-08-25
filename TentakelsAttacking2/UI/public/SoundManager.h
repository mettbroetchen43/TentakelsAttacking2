//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "SoundType.h"
#include <raylib.h>
#include <unordered_map>
#include <array>


class SoundManager {
private:
	std::unordered_map<SoundType, Sound> m_sounds;
	const std::array<std::string, 5> m_files = {
		"clicked_accepted_std.mp3",
		"clicked_press_std.mp3",
		"clicked_release_std.mp3",
		"clicked_disabled_std.mp3",
		"hovered_std.mp3",
	};

	void LoadSounds();

public:
	SoundManager();
	~SoundManager();
	void PlaySound(SoundType soundType) const;
};