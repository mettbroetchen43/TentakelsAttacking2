//
// Purpur Tentakel
// 05.06.2023
//

#include "Scene.h"
#include "EventListener.hpp"
#pragma once

class SendUpdateEvaluation;

class UpdateEvaluationScene final : public Scene, public EventListener {
private:
	void Initialize(SendUpdateEvaluation const* event) const;


public:
	UpdateEvaluationScene(Vector2 resolution);
	~UpdateEvaluationScene();

	void OnEvent(Event const& event) override;
};
