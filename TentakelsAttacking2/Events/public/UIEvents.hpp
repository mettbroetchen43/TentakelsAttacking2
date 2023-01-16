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
enum class Resolution;

/**
 * use this to close the program at the end of one cyclus.
 */
class CloseWindowEvent final : public Event { };
/**
 * use this to set the target fps in the constatns an the raylib.
 */
class SetTargetFPSEvent final : public Event {
private:
	size_t m_fps;

public:
	SetTargetFPSEvent(size_t fps)
		:m_fps(fps) { }

	[[nodiscard]] size_t GetFPS() const {
		return m_fps;
	}
};
/**
 * use this to trigger the appcontext to toggle fullscreen.
 */
class ToggleFullscreenEvent final : public Event { };
/**
 * use this for setting a new resolutionan the AppContext.
 */
class SetNewResolutionEvent final : public Event {
private:
	Resolution m_resolution;

public:
	SetNewResolutionEvent(Resolution resolution )
		: m_resolution(resolution ){ }

	[[nodiscard]] Resolution GetResolution ( ) const {
		return m_resolution;
	}
};

/**
 * use this to play any sound inside the sound manager.
 */
class PlaySoundEvent final : public Event {
public:
	PlaySoundEvent(SoundType soundType)
		:m_soundType(soundType) {}
	[[nodiscard]] SoundType GetSoundType() const {
		return m_soundType;
	}

private:
	SoundType m_soundType;
};
/**
 * use this to set the master volume in the constants and the raylib.
 */
class SetMasterVolumeEvent final : public Event {
private:
	float m_level;

public:
	SetMasterVolumeEvent(float level)
		: m_level(level) {};

	[[nodiscard]] float GetLevel() const {
		return m_level;
	}
};
/**
 * use this to set the mute in the constants and the set the volume of raylib to 0.
 */
class MuteMasterVolumeEvent final : public Event {
private:
	bool m_mute;

public:
	MuteMasterVolumeEvent(bool mute)
		: m_mute(mute){ }

	[[nodiscard]] bool GetMute() const {
		return m_mute;
	}
};

/**
 * general focus event to provide an focusable* to the Focus system.
 */
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
/**
 * use this to add an element to the focus.
 * is held back in the case of a popup.
 */
class NewFocusElementEvent final : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
/**
 * use this to add an element to the focus.
 * this is alway executed and blocks other elements until the popup is closed.
 */
class NewFocusPopUpElementEvent final : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
/**
 * use this to delete an element to the focus.
 * is held back in the case of a popup.
 */
class DeleteFocusElementEvent final : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
/**
 * use this to delete an element to the focus.
 * this is alway executed and blocks other elements until the popup is closed.
 */
class DeleteFocusPopUpElementEvent final : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
/**
 * use this to select an element to the focus.
 * is held back in the case of a popup.
 */
class SelectFocusElementEvent final : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
/**
 * use this to select an element to the focus.
 * this is alway executed and blocks other elements until the popup is closed.
 */
class SelectFocusPopUpElementEvent final : public FocusEvent {
public:
	using FocusEvent::FocusEvent;
};
/**
 * use this to select any next element to the focus.
 */
class SelectNextFocusElementEvent final: public Event { };
/**
 * use this to add an layer to the focus.
 * this is alway executed and blocks other elements until the popup is closed.
 */
class NewFocusPopUpLayerEvent final :public Event { };
/**
 * use this to add an layer to the focus.
 * is held back in the case of a popup.
 */
class NewFocusLayerEvent final :public Event { };
/**
 * use this to delete an layer of the focus.
 * this is alway executed and blocks other elements until the popup is closed.
 */
class DeleteFocusPopUpLayerEvent final : public Event { };
/**
 * use this to delete an layer of the focus.
 * is held back in the case of a popup.
 */
class DeleteFocusLayerEvent final : public Event { };
/**
 * use this to delete all layer of the focus.
 * this is alway executed.
 */
class ClearFocusEvent final : public Event { };

/**
 * use this to switch the scene at the end of a turn.
 * unloads the old scene and loands a new one
 */
class SwitchSceneEvent final :public Event {
private:
	SceneType m_sceneType;
public:
	SwitchSceneEvent(SceneType sceneType)
		:m_sceneType(sceneType) { }
	[[nodiscard]] SceneType GetSceneType() const {
		return m_sceneType;
	}
};
/**
 * use this to close the last popup generated.
 */
class ClosePopUpEvent final : public Event {
private:
	PopUp* m_popUp;

public:
	ClosePopUpEvent(PopUp* popUp)
		:m_popUp(popUp) {}
	PopUp* GetPop() const {
		return m_popUp;
	}
};
/**
 * genereal popup evenbt to provide title and subtitle
 */
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
/**
 * use this to show a popup message.
 * this will "freeze" the ui until the popup is closed.
 */
class ShowMessagePopUpEvent final : public PopUpEvent {
private:
	std::function<void()> m_callback = []() {};
public:
	ShowMessagePopUpEvent(std::string const& title, std::string const& subTile, std::function<void()> callback = []() {})
		:PopUpEvent(title, subTile), m_callback(callback) { }
	[[nodiscard]] std::function<void()> GetCallback() const {
		return m_callback;
	}
};
/**
 * use this to edit a table cell.
 * this will "freeze" the ui until the popup is closed.
 */
template <typename T>
class ShowCellPopUpEvent final : public PopUpEvent {
private:
	T m_currentValue;
	std::function<void(T)> m_onClick = [](T) {};

public:
	ShowCellPopUpEvent(std::string const& title,
		T currentValue, std::function<void(T)> onClick)
		: PopUpEvent(title, ""), m_currentValue(currentValue),
		m_onClick(onClick) { }

	[[nodiscard]] T GetCurrentValue() const {
		return m_currentValue;
	}
	[[nodiscard]] std::function<void(T)> GetOnClick() const {
		return m_onClick;
	}

};
/**
 * use this to delete a player by id.
 * this will "freeze" the ui until the popup is closed.
 */
class ShowDeletePlayerPopUpEvent final : public PopUpEvent {
	std::function<void(unsigned int)> m_onClick = [](unsigned int) {};

public:
	ShowDeletePlayerPopUpEvent(std::string const& title,
		std::string const& subTitle, std::function<void(unsigned int)> onClick)
		: PopUpEvent(title, subTitle), m_onClick(onClick) { }

	[[nodiscard]] std::function<void(unsigned int)> GetOnClick() const {
		return m_onClick;
	}
};
/**
 * use this to validate a current Situaltion.
 * will call a callback function that returns a bool
 * this will "freeze" the ui until the popup is closed.
 */
class ShowValidatePopUp final : public PopUpEvent {
private:
	std::function<void(bool)> m_callback;

public:
	ShowValidatePopUp(std::string const& title, std::string const& subTile, std::function<void(bool)> callback)
		:PopUpEvent(title, subTile), m_callback(callback) { }

	[[nodiscard]] std::function<void(bool)> GetCallback() const {
		return m_callback;
	}
};
/**
 * use this to set the sound level.
 * this will "freeze" the ui until the popup is closed.
 */
class ShowInitialSoundLevelPopUpEvent final : public PopUpEvent {
public:
	using PopUpEvent::PopUpEvent;
};
