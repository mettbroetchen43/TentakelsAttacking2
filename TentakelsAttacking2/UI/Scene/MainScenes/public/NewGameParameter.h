//
// Purpur Tentakel
// 31.10.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"
#include <vector>

class GameEventSettings;
class SliderAndInputLine;

class NewGameParameterScene final : public Scene, public EventListener {
private:
	std::shared_ptr<GameEventSettings> m_eventSettings;
	std::vector<std::shared_ptr<SliderAndInputLine>> m_slider;
	void Initialize(Vector2 resolution);

	void SetValue(int value, int ID) const;
	void SetRandom() const;

	void NextScene() const;

public:
	NewGameParameterScene(Vector2 resolution);
	~NewGameParameterScene() override;

	void OnEvent(Event const& event) override;
};