//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "MainEvent.hpp"

class EventListener {
	friend class EventManager;
private:
	virtual void OnEvent(Event const& event) = 0;
};
