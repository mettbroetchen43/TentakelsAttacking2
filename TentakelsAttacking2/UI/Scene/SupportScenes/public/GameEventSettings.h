//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"
#include "GenerelEvents.hpp"

class CheckBox;
enum class GameEventTypes;

class GameEventSettings : public Scene, public EventListener {
private:
	std::vector<std::shared_ptr<CheckBox>> m_checkBoxes;
	void Initialize(Vector2 resoluton, unsigned int focusID);

	void SetChecked(unsigned int ID, bool isCecked);

	void UpdateElements(UpdateCheckGameEventsUI const* event);

public:
	GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution);
	~GameEventSettings();

	void OnEvent(Event const& event);
};
