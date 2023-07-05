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
	enum class ResultType {
		MERGE,
		FIGHT,
		LAST,
	};

private:
	std::vector<HMergeResult> m_mergeResults;
	std::vector<HFightResult> m_fightResults;
	ResultType m_currentResultType{ ResultType::MERGE };
	int m_currentIndex{ 0 };
	int m_popupCount{ 0 };

	void Initialize(SendUpdateEvaluation const* event) const;

	void DisplayMergeResult();
	void DisplayFightResult();
	void HandleNextPopup();

public:
	UpdateEvaluationScene(Vector2 resolution);
	~UpdateEvaluationScene();

	void OnEvent(Event const& event) override;
};
