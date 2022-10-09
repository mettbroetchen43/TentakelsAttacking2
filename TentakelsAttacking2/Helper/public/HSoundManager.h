//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "EventListener.hpp"
#include "HSoundType.hpp"
#include <raylib.h>
#include <unordered_map>
#include <array>
#include <vector>


class SoundManager : public EventListener {
private:
	std::unordered_map<SoundType, Sound> m_sounds;
	std::array<Sound, 10> m_hoverSounds;
	unsigned int m_hoverIndex;
	std::array<std::string, 5> m_files = {
		"clicked_accepted_std.mp3",
		"clicked_press_std.mp3",
		"clicked_release_std.mp3",
		"clicked_disabled_std.mp3",
		"hovered_std.mp3",
	};

	std::vector<Sound> m_textSounds;

	void LoadSounds();

	void PlaySound(SoundType soundType) const;
	void PlayTextSound() const;

	void OnEvent(Event const& event) override;

public:
	SoundManager();
	~SoundManager();
};