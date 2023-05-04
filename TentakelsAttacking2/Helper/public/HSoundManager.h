//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "EventListener.hpp"
#include "HSoundType.hpp"
#include "CustomRaylib.h"
#include <unordered_map>
#include <array>
#include <vector>
#include <string>

/**
 * contains and managed all sounds.
 */
class SoundManager final : public EventListener {
private:
	std::unordered_map<SoundType, Sound> m_sounds; ///< contains all sounds
	std::array<std::string, 5> m_files = {
		"clicked_accepted_std.mp3",
		"clicked_press_std.mp3",
		"clicked_release_std.mp3",
		"clicked_disabled_std.mp3",
		"hovered_std.mp3",
	};

	std::vector<Sound> m_textSounds; ///< contains the text sounds

	/**
	 * loads all sounds.
	 * stores it in m_sounds and m_textSounds.
	 */
	void LoadSounds();

	/**
	 * plays a sound by the soundtype.
	 * if the sound type is text, the PlayTextSound member function is called.
	 */
	void PlaySound(SoundType soundType) const;
	/**
	 * plays random text sounds.
	 * makes shure no sound is played twice.
	 */
	void PlayTextSound() const;

	/**
	 * mutes the soundleven in the constants and calls the SetMasterSoundLevel member function.
	 */
	void MuteMasterSoundLevel(bool mute) const;
	/**
	 * sets the master sound lebel in the constants and sets it in raylib.
	 * if the master sound is muted in the constats the raylib level is set to 0.
	 */
	void SetMasterSoundLevel(float level) const;

	/**
	 * receives all events and calls the member function.
	 */
	void OnEvent(Event const& event) override;

public:
	/**
	 * ctor.
	 * initialize the sound device.
	 * loas all sounds.
	 */
	SoundManager();
	/**
	 * dtor.
	 * unload all sounds.
	 * cloas the sound device.
	 */
	~SoundManager();
};