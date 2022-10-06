//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "MainEvent.hpp"
#include "SoundType.h"
#include <string>

class StringCell;
class IntCell;
class FloatCell;
class DoubleCell;
class ColorCell;
class Focusable;
class PopUp;
enum class SceneType;

class CloseWindowEvent :public Event {
};

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
class ClearFocusEvent : public Event {
};

class SwitchSceneEvent :public Event {
private:
	SceneType m_sceneType;
public:
	SwitchSceneEvent(SceneType sceneType)
		:m_sceneType(sceneType) { }
	[[nodiscard]] SceneType GetSceneType() const {
		return m_sceneType;
	}
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
class ShowStringCellPopUpEvent: public PopUpEvent{
private:
	StringCell* m_cell;

public:
	ShowStringCellPopUpEvent(std::string const& title,
		StringCell* cell)
		: PopUpEvent(title, ""), m_cell(cell) { }

	[[nodiscard]] StringCell* GetCell() const {
		return m_cell;
	}

};
class ShowIntCellPopUpEvent : public PopUpEvent {
private:
	IntCell* m_cell;

public:
	ShowIntCellPopUpEvent(std::string const& title,
		IntCell* cell)
		: PopUpEvent(title, ""), m_cell(cell) { }

	[[nodiscard]] IntCell* GetCell() const {
		return m_cell;
	}

};
class ShowFloatCellPopUpEvent : public PopUpEvent {
private:
	FloatCell* m_cell;

public:
	ShowFloatCellPopUpEvent(std::string const& title,
		FloatCell* cell)
		: PopUpEvent(title, ""), m_cell(cell) { }

	[[nodiscard]] FloatCell* GetCell() const {
		return m_cell;
	}

};
class ShowDoubleCellPopUpEvent : public PopUpEvent {
private:
	DoubleCell* m_cell;

public:
	ShowDoubleCellPopUpEvent(std::string const& title,
		DoubleCell* cell)
		: PopUpEvent(title, ""), m_cell(cell) { }

	[[nodiscard]] DoubleCell* GetCell() const {
		return m_cell;
	}

};
class ShowColorCellPopUpEvent : public PopUpEvent {
private:
	ColorCell* m_cell;

public:
	ShowColorCellPopUpEvent(std::string const& title,
		ColorCell* cell)
		: PopUpEvent(title, ""), m_cell(cell) { }

	[[nodiscard]] ColorCell* GetCell() const {
		return m_cell;
	}

};
