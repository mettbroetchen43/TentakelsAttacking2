//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include "EventListener.h"
#include <vector>

 class  EventManager {
public:
	void AddListener(EventListener* eventListener) {
		m_listeners.push_back(eventListener);
	}
	void InvokeEvent(Event const& event) const {
		for (auto const listener : m_listeners) {
			listener->OnEvent(event);
		}
	}

private:
	std::vector<EventListener*> m_listeners;
};