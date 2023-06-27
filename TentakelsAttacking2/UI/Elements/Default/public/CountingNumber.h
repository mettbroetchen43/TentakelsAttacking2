//
// Purpur Tentakel
// 27.06.2023
//

#pragma once
#include "UIElement.hpp"
#include "HUIAlias.hpp"

class CountingNumber : public UIElement {
public:
	enum Type {
		LINEAR,
		ASYMPTOTIC,
	};

private:
	Text_ty m_text;

	bool m_isCounting{ false };
	Type m_countingType{ LINEAR };
	int m_currentNumber;
	int m_targetNumber;
	float m_timeInS{ 0.0f };

	using callback_ty = std::function<void(Type, int, float)>;
	callback_ty m_callback{[](Type, int, float) ->void {} };

	void HandleCounting();
	void HandleLinearCounting();
	void HandleAsymptoticCounting();
	void SetNewNumber(int number);

public:
	CountingNumber(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		Alignment textAlignment, float textHeight, int startNumber);

	/**
	 * returns if the number is currently counting.
	 */
	[[nodiscard]] bool IsCounting() const;
	/**
	 * sets the callback function that gets called when the counting process is finished.
	 */
	void SetCallback(callback_ty callback);
	/**
	 * counts in a certain type to a other number in a provided time in s.
	 */
	void CountTo(Type type, int target, float timeIsS);
	/**
	 * returns the current number.
	 * differs from target number while counting.
	 */
	[[nodiscard]] int GetCurrentNumber() const;
	/**
	 * return the target number.
	 * differs from current number while counting.
	 */
	[[nodiscard]] int GetTargetNumber() const;


	/**
	 * 
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 *
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * 
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appCntext) override;
};
