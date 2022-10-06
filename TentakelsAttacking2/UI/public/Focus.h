//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include "LayeredVector.h"
#include "EventListener.hpp"
#include <vector>

class Focusable;

class Focus : public EventListener {
private:
	Focusable* m_currentFocus = nullptr;
	LayeredVector<Focusable> m_focus;
	std::vector<Focusable*> m_lastFocus;
	bool m_renderFocus = false;

	[[nodiscard]] bool HasAnyEnabledElements() const;

	void UnfocusAllAtTopLayer();
	[[nodiscard]] Focusable* GetFirstFocus();
	[[nodiscard]] Focusable* GetLastFocus();
	[[nodiscard]] Focusable* GetNextFocus();
	[[nodiscard]] Focusable* GetPreviousFocus();
	void SetInitialFocus();
	void SetNextFocus();
	void SetPreviousFocus();
	void SetSpecificFocus(Focusable* focusable);
	[[nodiscard]] bool IsExistingFocus(Focusable* focusable);

	void AddLayer();
	void DeleteLayer();
	void Clear();

	void AddElement(Focusable* focusable);
	void DeleteElement(Focusable* focusable);

	void CheckNewID(unsigned int newID);

public:
	Focus();

	void OnEvent(Event const& event) override;

	void CheckAndUpdate();
	void Render();
};