//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "MainEvent.h"
#include "SoundType.h"

class PlaySoundEvent : public Event {
public:
	PlaySoundEvent(SoundType soundType)
		:m_soundType(soundType) {}
	[[nodiscard]] SoundType GetSoundType() const {
		return m_soundType;
	}

private:
	SoundType m_soundType;
};