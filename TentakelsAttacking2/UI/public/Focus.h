//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include "LayeredVector.hpp"
#include "EventListener.hpp"
#include <vector>

class Focusable;

/**
 * provides a focus system that can heandle focusable*.
 */
class Focus final : public EventListener {
private:
	Focusable* m_currentFocus = nullptr; ///< contains the current focus
	LayeredVector<Focusable> m_focus; ///< contains all focusable elements in layern
	std::vector<Focusable*> m_lastFocus; ///< stores the corrent focus of the underlaying layers
	bool m_renderFocus = false; ///< contains if the focus gets renderd

	size_t m_PopUpLayerCounter = 0; ///< contains the mount of popups that are in the focus layers
	LayeredVector<Focusable> m_addElementRequest; ///< contains the elements to add if a popup ist currently active
	LayeredVector<Focusable> m_removeElementRequest;  ///< contains the elements to remove if a popup ist currently active
	LayeredVector<Focusable> m_toSelectRequest;  ///< contains the elements to select if a popup ist currently active
	std::vector<bool> m_toAddOrDelete; ///< contains if the layer schould be added or delete if a popup is currently active

	/**
	 * returns if the current layer has any anabled elements.
	 */
	[[nodiscard]] bool HasAnyEnabledElements() const;

	/**
	 * sets all focus elements at the top layer to false.
	 * sets the current focus to nullptr.
	 */
	void UnfocusAllAtTopLayer();
	/**
	 * calculates and returns the focus element with the smales id.
	 */
	[[nodiscard]] Focusable* GetFirstFocus();
	/**
	 * calculates and returns the focus element with the heighest id.
	 */
	[[nodiscard]] Focusable* GetLastFocus();
	/**
	 * calculates and returns the focus element with the next id.
	 */
	[[nodiscard]] Focusable* GetNextFocus();
	/**
	 * calculates and returns the focus element with the previous id.
	 */
	[[nodiscard]] Focusable* GetPreviousFocus();
	/**
	 * sets the initial focus.
	 */
	void SetInitialFocus();
	/**
	 * sets the next focus.
	 */
	void SetNextFocus();
	/**
	 * sets the previos focus.
	 */
	void SetPreviousFocus();
	/**
	 * checks and returns if the provided focus element is existing in the top layer.
	 */
	[[nodiscard]] bool IsExistingFocus(Focusable* focusable);

	/**
	 * sets the provided focus active and the previous focus inactive.
	 */
	void SetSpecificFocus(Focusable* focusable);
	/**
	 * sets the provided focus active and the previous focus inactive if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
	void SetSpecificNormalFocus(Focusable* focusable);
	/**
	 * sets the provided focus active and the previous focus inactive.
	 */
	void SetSpecificPopUpFocus(Focusable* focusable);

	/**
	 * adds a new layer to the focus vector.
	 * sets the current focus to nullptr.
	 * sets the render to false.
	 */
	void AddLayer();
	/**
	 * adds a new layer to the focus vector if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
	void AddNormalLayer();
	/**
	 * adds a new layer to the focus vector.
	 * increment the popup counter.
	 */
	void AddPopUpLayer();
	/**
	 * sets all elements to false.
	 * removed the current layer.
	 * sets a new focus if provided.
	 */
	void DeleteLayer(bool setNewFocus = true);
	/**
	 * deletes the current layer to the focus vector if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
	void DeleteNormalLayer();
	/**
	 * deletes the current layer to the focus vector.
	 * decrement the popup counter.
	 */
	void DeletePopUpLayer();
	/**
	 * clears the complete focus class.
	 * no data are remaining.
	 */
	void Clear();

	/**
	 * adds the provided focus element to the vector.
	 * sets a new active focus if provided. 
	 */
	void AddElement(Focusable* focusable, bool setNewFocus = true);
	/**
	 * adds the provided focus element to the vector if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
	void AddNormalElement(Focusable* focusable);
	/**
	 * adds the provided focus element allways to the vector.
	 */
	void AddPopUpElement(Focusable* focusable);
	/**
	 * deletes the provided focus element from the vector.
	 * sets a new active focus if provided.
	 */
	void DeleteElement(Focusable* focusable, bool setNewFocus = true);
	/**
	 * deletes the provided focus element from the vector if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
	void DeleteNormalElement(Focusable* focusable);
	/**
	 * delets the provided focus element allways from the vector.
	 */
	void DeletePopUpElement(Focusable* focusable);

	/**
	 * executes all requests that are hold back while a popup was active.
	 */
	void SetLayerAfterPopUp();

	/**
	 * check if the provided ID is allready existing in the current layer.
	 * thows an exeption if so.
	 */
	void CheckNewID(unsigned int newID);

public:
	/**
	 * ctor.
	 * adds listener to the event system.
	 */
	Focus();

	/**
	 * receives all the events and calls the memebr functions.
	 */
	void OnEvent(Event const& event) override;

	/**
	 * focus logic.
	 */
	void CheckAndUpdate();
	/**
	 * render the focus.
	 */
	void Render();
};