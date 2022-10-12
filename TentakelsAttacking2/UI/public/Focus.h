//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include "LayeredVector.hpp"
#include "EventListener.hpp"
#include <vector>

class Focusable;

class Focus : public EventListener {
private:
	Focusable* m_currentFocus = nullptr;
	LayeredVector<Focusable> m_focus;
	std::vector<Focusable*> m_lastFocus;
	bool m_renderFocus = false;

	size_t m_PopUpLayerCounter = 0;
	LayeredVector<Focusable> m_layerRequest;
	LayeredVector<Focusable> m_toSelectRequest;
	std::vector<bool> m_toAddOrDelete;

	[[nodiscard]] bool HasAnyEnabledElements() const;

	void UnfocusAllAtTopLayer();
	[[nodiscard]] Focusable* GetFirstFocus();
	[[nodiscard]] Focusable* GetLastFocus();
	[[nodiscard]] Focusable* GetNextFocus();
	[[nodiscard]] Focusable* GetPreviousFocus();
	void SetInitialFocus();
	void SetNextFocus();
	void SetPreviousFocus();
	[[nodiscard]] bool IsExistingFocus(Focusable* focusable);

	void SetSpecificFocus(Focusable* focusable);
	void SetSpecificNormalFocus(Focusable* focusable);
	void SetSpecificPopUpFocus(Focusable* focusable);

	void AddLayer();
	void AddNormalLayer();
	void AddPopUpLayer();
	void DeleteLayer();
	void DeleteNormalLayer();
	void DeletePopUpLayer();
	void Clear();

	void AddElement(Focusable* focusable);
	void AddNormalElement(Focusable* focusable);
	void AddPopUpElement(Focusable* focusable);
	void DeleteElement(Focusable* focusable);
	void DeleteNormalElement(Focusable* focusable);
	void DeletePopUpElement(Focusable* focusable);

	void SetLayerAfterPopUp();

	void CheckNewID(unsigned int newID);

public:
	Focus();

	void OnEvent(Event const& event) override;

	void CheckAndUpdate();
	void Render();
};