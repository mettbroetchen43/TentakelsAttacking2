//
// Purpur Tentakel
// 29.09.22
//

#pragma once
#include "UIElement.h"
#include "Focusable.h"
#include <string>

class Cell : public UIElement, public Focusable {
private:
	Rectangle m_colider;

protected:
	Vector2 m_textPosition;
	float m_textSize;

	[[nodiscard]] bool ShouldEdit(Vector2 const& mousePosition) const;

public:
	Cell(Vector2 pos, Vector2 size, Alignment alignment,
		unsigned int ID, Vector2 resolution);
	virtual ~Cell() = default;

	[[nodiscard]] virtual Cell* AsEmpty() { return nullptr; }
	[[nodiscard]] virtual Cell* AsColor() { return nullptr; }
	[[nodiscard]] virtual Cell* AsString() { return nullptr; }
	[[nodiscard]] virtual Cell* AsInt() { return nullptr; }
	[[nodiscard]] virtual Cell* AsFloat() { return nullptr; }
	[[nodiscard]] virtual Cell* AsDouble() { return nullptr; }

	[[nodiscard]] virtual void SetColor([[maybe_unused]] Color value) { return; };
	[[nodiscard]] virtual void SetString([[maybe_unused]] std::string value) { return; };
	[[nodiscard]] virtual void SetInt([[maybe_unused]] int value) { return; };
	[[nodiscard]] virtual void SetFloat([[maybe_unused]] float value) { return; };
	[[nodiscard]] virtual void SetDouble([[maybe_unused]] double value) { return; };

	[[nodiscard]] virtual Color GetColor() const { throw "This is not a color"; }
	[[nodiscard]] virtual std::string GetString() const { throw "This is not a string"; }
	[[nodiscard]] virtual int GetInt() const { throw "This is not a int"; }
	[[nodiscard]] virtual float GetFloat() const { throw "This is not a float"; }
	[[nodiscard]] virtual double GetDouble() const { throw "This is not a double"; }

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext)  = 0;
	virtual void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
	
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;
};