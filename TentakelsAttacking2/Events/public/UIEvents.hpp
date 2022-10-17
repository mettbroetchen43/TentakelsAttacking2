//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "MainEvent.hpp"
#include "HSoundType.hpp"
#include <string>
#include <functional>
#include <raylib.h>

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
class NewFocusPopUpElementEvent : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
class DeleteFocusElementEvent : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
class DeleteFocusPopUpElementEvent : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
class SelectFocusElementEvent : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
class SelectFocusPopUpElementEvent : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
class NewFocusPopUpLayerEvent :public Event {
};
class NewFocusLayerEvent :public Event {
};
class DeleteFocusPopUpLayerEvent : public Event {
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
	std::string m_currentValue;
	std::function<void(std::string)> m_onClick = [](std::string) {};

public:
	ShowStringCellPopUpEvent(std::string const& title,
		std::string const& currentValue, std::function<void(std::string)> onClick)
		: PopUpEvent(title, ""), m_currentValue(currentValue),
		m_onClick(onClick) { }

	[[nodiscard]] std::string GetCurrentValue() const {
		return m_currentValue;
	}
	[[nodiscard]] std::function<void(std::string)> GetOnClick() const {
		return m_onClick;
	}


};
class ShowIntCellPopUpEvent : public PopUpEvent {
private:
	int m_currentValue;
	std::function<void(int)> m_onClick = [](int) {};

public:
	ShowIntCellPopUpEvent(std::string const& title,
		int currentValue, std::function<void(int)> onClick)
		: PopUpEvent(title, ""), m_currentValue(currentValue),
		m_onClick(onClick) { }

	[[nodiscard]] int GetCurrentValue() const {
		return m_currentValue;
	}
	[[nodiscard]] std::function<void(int)> GetOnClick() const {
		return m_onClick;
	}

};
class ShowFloatCellPopUpEvent : public PopUpEvent {
private:
	float m_currentValue;
	std::function<void(float)> m_onClick = [](float) {};

public:
	ShowFloatCellPopUpEvent(std::string const& title,
		double currentValue, std::function<void(float)> onClick)
		: PopUpEvent(title, ""),m_currentValue(currentValue),
		m_onClick(onClick) { }

	[[nodiscard]] float GetCurrentValue() const {
		return m_currentValue;
	}
	[[nodiscard]] std::function<void(float)> GetOnClick() const {
		return m_onClick;
	}

};
class ShowDoubleCellPopUpEvent : public PopUpEvent {
private:
	double m_currentValue;
	std::function<void(double)> m_onClick = [](double) {};

public:
	ShowDoubleCellPopUpEvent(std::string const& title,
		double currentValue, std::function<void(double)> onClick)
		: PopUpEvent(title, ""), m_currentValue(currentValue),
		m_onClick(onClick) { }

	[[nodiscard]] double GetCurrentValue() const {
		return m_currentValue;
	}
	[[nodiscard]] std::function<void(double)> GetOnClick() const {
		return m_onClick;
	}


};
class ShowColorCellPopUpEvent : public PopUpEvent {
private:
	Color m_currentColor;
	std::function<void(Color)> m_onClick = [](Color) {};

public:
	ShowColorCellPopUpEvent(std::string const& title,
		Color currentColor, std::function<void(Color)> onClick)
		: PopUpEvent(title, ""), m_currentColor(currentColor),
		m_onClick(onClick) { }

	[[nodiscard]] Color GetCurrentColor() const {
		return m_currentColor;
	}
	[[nodiscard]] std::function<void(Color)> GetOnClick() const {
		return m_onClick;
	}
};

class ShowDeletePlayerEvent : public PopUpEvent {
	std::function<void(unsigned int)> m_onClick = [](unsigned int) {};

public:
	ShowDeletePlayerEvent(std::string const& title,
		std::string const& subTitle, std::function<void(unsigned int)> onClick)
		: PopUpEvent(title, subTitle), m_onClick(onClick) { }

	[[nodiscard]] std::function<void(unsigned int)> GetOnClick() const {
		return m_onClick;
	}
};
