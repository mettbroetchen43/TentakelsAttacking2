//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include <CustomRaylib.h>

/**
 * provides the focusable inplementation for every ui element that should be focusable.
 */
class Focusable {
private:
	unsigned int m_focusID; ///< contains the unique (per layer) id
	bool m_isFocus = false; ///< contains if this focusable is currntly in focus

protected:
	bool m_isNestedFocus = false; ///< contains if there is a nested focus

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	Focusable(unsigned int ID);
	/**
	 * dtor
	 * deletes this in the focus system if its still exists.
	 */
	~Focusable();
	
	/**
	 * returns if this element currently focused.
	 */
	[[nodiscard]] bool IsFocused() const;
	/**
	 * sets if this element is in focus.
	 */
	void SetFocus(bool focus);
	/**
	 * returns if this element has an nested focus.
	 */
	[[nodiscard]] bool IsNestedFocus() const;
	/**
	 * sets if this element has an nested focus.
	 */
	void SetNestedFocus(bool nestedFocus);

	/**
	 * returns if the current elements is enabled.
	 */
	[[nodiscard]] virtual bool IsEnabled() const = 0;

	/**
	 * returns the unique (per layer) id.
	 */
	[[nodiscard]] unsigned int GetFocusID() const;
	/**
	 * returns thr current collider.
	 */
	[[nodiscard]] virtual Rectangle GetCollider() const = 0;
};
