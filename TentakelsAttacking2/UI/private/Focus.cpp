//
// Purpur Tentakel
// 04.09.2022
//

#include "Focus.h"
#include "Focusable.h"
#include "Events.h"
#include "AppContext.h"
#include <iostream>
#include <stdexcept>

void Focus::UnfocusAllAtTopLayer() {
	for (auto focus : m_focus) {
		focus->SetFocus(false);
	}

	m_currentFocus = nullptr;
}

Focusable* Focus::GetFirstFocus() {
	Focusable* firstFocus = nullptr;

	for (auto focus : m_focus) {
		if (!firstFocus) {
			firstFocus = focus;
		}
		if (firstFocus->GetFocusID() > focus->GetFocusID()) {
			firstFocus = focus;
		}
	}

	return firstFocus;
}
Focusable* Focus::GetLastFocus() {
	Focusable* lastFocus = nullptr;

	for (auto focus : m_focus) {
		if (!lastFocus) {
			lastFocus = focus;
			continue;
		}
		if (lastFocus->GetFocusID() < focus->GetFocusID()) {
			lastFocus = focus;
		}
	}

	return lastFocus;
}
Focusable* Focus::GetNextFocus() {
	unsigned int currentID = m_currentFocus? m_currentFocus->GetFocusID() : 0;
	Focusable* nextFocus = nullptr;

	for (auto focus : m_focus) {
		if (focus->GetFocusID() > currentID) {
			if (!nextFocus) {
				nextFocus = focus;
				continue;
			}
			if (focus->GetFocusID() < nextFocus->GetFocusID()) {
				nextFocus = focus;
			}
		}
	}

	return nextFocus;
}
Focusable* Focus::GetPreviousFocus() {
	unsigned int currentID = m_currentFocus ? m_currentFocus->GetFocusID() : m_focus.size();
	Focusable* previousFocus = nullptr;

	for (auto focus : m_focus) {
		if (focus->GetFocusID() < currentID) {
			if (!previousFocus) {
				previousFocus = focus;
				continue;
			}
			if (focus->GetFocusID() > previousFocus->GetFocusID()) {
				previousFocus = focus;
			}
		}
	}

	return previousFocus;
}
void Focus::SetInitialFocus() {
	m_currentFocus = GetFirstFocus();
	if (m_currentFocus) {
		m_currentFocus->SetFocus(true);
	}
}
void Focus::SetNextFocus() {
	m_currentFocus->SetFocus(false);

	Focusable* nextFocus = GetNextFocus();
	if (!nextFocus) {
		nextFocus = GetFirstFocus();
	}

	m_currentFocus = nextFocus;
	m_currentFocus->SetFocus(true);
}
void Focus::SetPreviousFocus() {
	m_currentFocus->SetFocus(false);

	Focusable* previousFocus = GetPreviousFocus();
	if (!previousFocus) {
		previousFocus = GetLastFocus();
	}

	m_currentFocus = previousFocus;
	m_currentFocus->SetFocus(true);
}
void Focus::SetSpecificFocus(Focusable* focusable) {
	if (!IsExistingFocus(focusable)) { return; }

	if (m_currentFocus) {
		m_currentFocus->SetFocus(false);
	}
	m_currentFocus = focusable;
	m_currentFocus->SetFocus(true);
}
bool Focus::IsExistingFocus(Focusable* focusable) {
	for (auto focus : m_focus) {
		if (focus == focusable) {
			return true;
		}
	}
	return false;
}

void Focus::CheckNewID(unsigned int newID) {
	for (auto focus : m_focus) {
		if (focus->GetFocusID() == newID) {
			throw std::invalid_argument("ID already exists, ID: " + newID);
		}
	}
}

Focus::Focus() {
	AddLayer();
	AppContext& appContext = AppContext::GetInstance();
	appContext.eventManager.AddListener(this);
}

void Focus::AddLayer() {
	m_focus.AddLayer();
	m_currentFocus = nullptr;
}
void Focus::DeleteLayer() {
	m_focus.RemoveLayer();
	SetInitialFocus();
}

void Focus::AddElement(Focusable* focusable) {
	CheckNewID(focusable->GetFocusID());
	m_focus.AddElement(focusable);

	if (!m_currentFocus) {
		SetInitialFocus();
	}
}
void Focus::DeleteElement(Focusable* focusable) {
	if (m_currentFocus == focusable) {
		m_currentFocus = GetNextFocus();
	}

	m_focus.RemoveElement(focusable);
}

void Focus::OnEvent(Event const& event) {
	if (auto const focusEvent = dynamic_cast<NewFocusEvent const*>(&event)) {
		AddElement(focusEvent->GetFocusable());
	}

	if (auto const focusEvent = dynamic_cast<DeleteFocusEvent const*>(&event)) {
		DeleteElement(focusEvent->GetFocusable());
	}

	if (auto const focusEvent = dynamic_cast<SelectFocusEvent const*>(&event)) {
		SetSpecificFocus(focusEvent->GetFocusable());
	}
}

void Focus::CheckAndUpdate() {
	if (!m_currentFocus) {
		return;
	}

	if (IsKeyPressed(KEY_TAB)) {
		if (IsKeyDown(KEY_LEFT_SHIFT) or IsKeyDown(KEY_RIGHT_SHIFT)) {
			SetPreviousFocus();
			return;
		}

		SetNextFocus();
	}

}
void Focus::Render() {
	if (!m_currentFocus) {
		return;
	}

	Rectangle const& f_colider = m_currentFocus->GetCollider();
	DrawRectangle(
		f_colider.x + 1,
		f_colider.y - 3,
		f_colider.width - 2,
		f_colider.height + 6,
		PURPLE
	);
}
