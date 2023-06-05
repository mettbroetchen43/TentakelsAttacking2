//
// Purpur Tentakel
// 05.06.2023
//

#include "UpdateEvaluation.h"
#include "AppContext.h"
#include "GenerelEvents.hpp"
#include "SceneType.h"
#include "Player.h"
#include "HPrint.h"

void UpdateEvaluationScene::Initialize(SendUpdateEvaluation const* event) const {

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	Print("--------------------| Evaluation |--------------------", PrintType::DEBUG);
	for (auto const& e : event->GetFightResults()) {
		if (not e.IsValid()) { Print("invalid update Evaluation", PrintType::DEBUG);  continue; }

		Print(appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().first->GetID()).name
			+ " | " +
			appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().second->GetID()).name, PrintType::DEBUG);

		for (auto const& r : e.GetRounds()) {
			Print(std::to_string(r.first) + " | " + std::to_string(r.second), PrintType::DEBUG);
		}
		Print("----------------------------------------------", PrintType::DEBUG);
	}

	ShowMessagePopUpEvent sendEvent{
		"Update",
		"Logic is updating\ndisplayed in console",
		[]() {
				SwitchSceneEvent sendEvent{ SceneType::MAIN };
				AppContext::GetInstance().eventManager.InvokeEvent(sendEvent);
			}
	};
	appContext.eventManager.InvokeEvent(sendEvent);
}

UpdateEvaluationScene::UpdateEvaluationScene(Vector2 resolution)
	: Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution) {

	AppContext_ty appContext{ AppContext::GetInstance() };
	appContext.eventManager.AddListener(this);
	appContext.eventManager.InvokeEvent(GetUpdateEvaluation{ });
}
UpdateEvaluationScene::~UpdateEvaluationScene() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void UpdateEvaluationScene::OnEvent(Event const& event) {
	if (auto const* evEvent = dynamic_cast<SendUpdateEvaluation const*> (&event)) {
		Initialize(evEvent);
	}
}
