//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "MainEvent.h"
#include "SoundType.h"

class Focusable;

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

class FocusEvent : public Event {
protected:
	Focusable* m_focusable;
	FocusEvent(Focusable* focusable)
		: m_focusable(focusable) { }

public:
	[[nodiscard]] Focusable* GetFocusable() const {
		return m_focusable;
	}
};
class NewFocusEvent : public FocusEvent {
public:
	NewFocusEvent(Focusable* focusable)
		: FocusEvent(focusable) { }
};
class DeleteFocusEvent : public FocusEvent {
public:
	DeleteFocusEvent(Focusable* focusable)
		: FocusEvent(focusable) { }
};