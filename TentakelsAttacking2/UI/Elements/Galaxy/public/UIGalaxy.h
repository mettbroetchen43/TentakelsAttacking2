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
	bool m_isScrollingByMouse = false;
	bool m_isShowGalaxy = false;
	float m_scaleFactor = 1.0f;
	Vector2 m_lastMousePosition = { 0.0f,0.0f };
	Vector2 m_resolution;
	Rectangle m_colider;
	Rectangle m_absoluteSize;
	Galaxy const* m_currentGalaxy = nullptr;
	std::vector<std::shared_ptr<UIPlanet>> m_uiPlanets;
	std::function<void(float, Vector2)> m_onZoom = [](float, Vector2) {};
	std::function<void(float, bool)> m_onSlide = [](float, bool) {};
	std::function<void(unsigned int)> m_onPlanetClick = [](unsigned int) {};

	void Initialize(Galaxy const* const galaxy);
	[[nodiscard]] Vector2 GetAbsolutePosition(Vector2 pos, AppContext const& appContext) const;
	[[nodiscard]] Vector2 GetRelativePosition(Vector2 pos, AppContext const& appContext) const;

	[[nodiscard]] bool IsPlanetInCollider(std::shared_ptr<UIPlanet> planet) const;
	void UpdatePlanetPosition();
	void SelectPlanet(UIPlanet* planet);

	void CheckPosition();
	void PrepForOnSlide();
	void MoveByKey(Direction direction, float speed);
	void MoveByMouse(Vector2 mousePosition);

	[[nodiscard]] Vector2 GetCurrentScaleReference() const;

public:
	UIGalaxy(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution, bool isShowGalaxy = false);
	~UIGalaxy();

	void SetIsScaling(bool isScaling);
	[[nodiscard]] bool IsScaling() const;

	[[nodiscard]] float GetScaleFactor() const;
	void Zoom(bool zoomIn, int factor = 2);
	void Slide(float position, bool isHorizontal);

	void SetOnZoom(std::function<void(float, Vector2)> onZoom);
	void SetOnSlide(std::function<void(float, bool)> onSlide);
	void SetOnPlanetClick(std::function<void(unsigned int)> onPlanetClick);

	void UpdateColider(Vector2 resolution) override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	void SetEnabled(bool isEnabled);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	void OnEvent(Event const& event) override;
};