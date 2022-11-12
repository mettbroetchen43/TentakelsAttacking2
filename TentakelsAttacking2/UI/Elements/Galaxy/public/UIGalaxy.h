//
// Purpur Tentakel
// 12.11.2022
//

#pragma once
#include "UIElement.hpp"
#include "EventListener.hpp"
#include "Focusable.h"
#include <functional>
#include <memory>
#include <vector>

class Galaxy;
class UIPlanet;

class UIGalaxy final : public UIElement, public EventListener, public Focusable {
private:
	enum class Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};
	bool m_isEnabled = true;
	bool m_isScaling = true;
	float m_scaleFacor = 1.0f;
	Vector2 m_lastMousePosition = { 0.0f,0.0f };
	Vector2 m_resolution;
	Rectangle m_colider;
	Rectangle m_absoluteSize;
	std::vector<std::shared_ptr<UIPlanet>> m_uiPlanets;
	std::function<void(float)> m_onZoom = [](float) {};
	std::function<void(float, bool)> m_onSlide = [](float, bool) {};

	void Initialize(Galaxy const* const galaxy);
	[[nodiscard]] Vector2 GetAbsolutePosition(Vector2 pos, AppContext const& appContext) const;
	[[nodiscard]] Vector2 GetRelativePosition(Vector2 pos, AppContext const& appContext) const;

	[[nodiscard]] bool IsPlanetInColider(std::shared_ptr<UIPlanet> planet) const;
	void UpdatePlanetPosition();
	void SelectPlanet(UIPlanet* planet);

	void CheckPosition();
	void PrepForOnSlide();
	void MoveByKey(Direction direction, float speed);
	void MoveByMouse(Vector2 mousePosition);

public:
	UIGalaxy(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution);
	~UIGalaxy();

	void SetIsScaling(bool isScaling);
	[[nodiscard]] bool IsScaling() const;

	[[nodiscard]] float GetScaleFactor() const;
	void Zoom(bool zoomIn, int factor = 1);
	void Slide(float position, bool isHorizontal);

	void SetOnZoom(std::function<void(float)> onZoom);
	void SetOnSlide(std::function<void(float, bool)> onSlide);

	void UpdateColider(Vector2 resolution) override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	void SetEnabled(bool isEnabled);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	void OnEvent(Event const& event) override;
};