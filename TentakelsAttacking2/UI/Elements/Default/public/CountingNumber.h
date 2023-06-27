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
	int m_startNumber;
	int m_currentNumber;
	int m_targetNumber;

	double m_timeInS{ 0.0f };
	double m_startCountingTime{ GetTime() };
	float m_countingSpeed{ 0.0f };

	Color m_countingColor{ RED };
	Color m_defaultColor{ WHITE };

	using callback_ty = std::function<void(Type, int, int, double)>;
	callback_ty m_callback{[](Type, int, int, double) ->void {} };

	void HandleCounting();
	void HandleLinearCounting();
	void HandleAsymptoticCounting();
	void SetNewNumber(int number);

public:
	CountingNumber(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		Alignment textAlignment, float textHeight, int startNumber);
	
	/**
	 * sets the color for rendering while counting.
	 */
	void SetCountingColor(Color color);
	/**
	 * sets the color for rendering without counting.
	 */
	void SetDefaultColor(Color color);
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
	void CountTo(Type type, int target, double timeIsS);
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
