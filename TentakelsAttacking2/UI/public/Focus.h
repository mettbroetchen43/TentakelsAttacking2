//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include "LayeredVector.h"
#include "EventListener.h"

class Focusable;

class Focus : public EventListener {
private:
	Focusable* m_currentFocus = nullptr;
	LayeredVector<Focusable> m_focus;

	void UnfocusAllAtTopLayer();
	[[nodiscard]] Focusable* GetFirstFocus();
	[[nodiscard]] Focusable* GetLastFocus();
	[[nodiscard]] Focusable* GetNextFocus();
	[[nodiscard]] Focusable* GetPreviousFocus();
	void SetInitialFocus();
	void SetNextFocus();
	void SetPreviousFocus();

	void AddElement(Focusable* focusable);
	void DeleteElement(Focusable* focusable);

	void CheckNewID(unsigned int newID);

public:
	Focus();

	void AddLayer();
	void DeleteLayer();

	void OnEvent(Event const& event) override;

	void CheckAndUpdate();
	void Render();
};