//
// Purpur Tentakel
// 06.09.2022
//

#pragma once
#include "UIElement.h"
#include "Focusable.h"
#include <raylib.h>
#include <string>

class InputLine : public UIElement, public Focusable {
protected:
	unsigned int m_charLimit;
	Rectangle m_collider;
	std::string m_input;
	Texture* m_texture;
	double m_backspacePressTime = 0.0;

	bool AddChar(int key);
	void RemoveChar();
	[[nodiscard]] bool IsAnyKeyPressed();
	[[nodiscard]] virtual bool IsValidKey(int key) = 0;
	[[nodiscard]] std::string GetPritableInput(std::string const& enter, std::string const& Prefix, int fontSize,
		int cursorOffset) const;
public:
	InputLine(unsigned int focusID, Texture2D* texture, Vector2 pos, Vector2 size, unsigned int charLimit,
		Vector2 resolution);
	InputLine(InputLine const&) = default;
	InputLine(InputLine&&) = default;
	InputLine& operator= (InputLine const&) = default;
	InputLine& operator= (InputLine&&) = default;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render() override;
	void Resize(Vector2 resolution) override;

	[[nodiscard]] Rectangle GetCollider() const override;
};

