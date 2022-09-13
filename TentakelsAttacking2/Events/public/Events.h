//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "MainEvent.h"
#include "SoundType.h"
#include <string>

class Focusable;
class PopUp;

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
class PlayTextSoundEvent :public Event {

};

class FocusEvent : public Event {
protected:
	Focusable* m_focusable;
	
public:
	FocusEvent(Focusable* focusable)
		: m_focusable(focusable) { }

	[[nodiscard]] Focusable* GetFocusable() const {
		return m_focusable;
	}
};
class NewFocusElementEvent : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
class DeleteFocusElementEvent : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
class SelectFocusElementEvent : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
class NewFocusLayerEvent :public Event {
};
class DeleteFocusLayerEvent : public Event {
};

class ClosePopUpEvent : public Event {
private:
	PopUp* m_popUp;

public:
	ClosePopUpEvent(PopUp* popUp)
		:m_popUp(popUp) {}
	PopUp* GetPop() const {
		return m_popUp;
	}
};
class PopUpEvent : public Event {
private:
	std::string m_title;
	std::string m_subTitle;

public:
	PopUpEvent(std::string const& title, std::string const& subTile)
		:m_title(title), m_subTitle(subTile) {}

	[[nodiscard]] std::string const& GetTitle() const {
		return m_title;
	}
	[[nodiscard]] std::string const& GetSubTitle() const {
		return m_subTitle;
	}
};
class ShowMessagePopUpEvent : public PopUpEvent {
public:
	using PopUpEvent::PopUpEvent;
};