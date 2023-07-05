//
// Purpur Tentakel
// 05.06.2023
//

#include "UpdateEvaluation.h"
#include "AppContext.h"
#include "GenerelEvents.hpp"
#include "SpaceObject.h"
#include "SceneType.h"
#include "Player.h"
#include "HPrint.h"

void UpdateEvaluationScene::Initialize(SendUpdateEvaluation const* event) const {

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	Print("--------------------| Evaluation |--------------------", PrintType::DEBUG);

	/*
	Print("------------------ | Merge Results |------------------", PrintType::DEBUG);
	for (auto const& e : event->GetMergeResults()) {
		Print(appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer()->GetID()).GetName(), PrintType::DEBUG);
		Print(std::to_string(e.GetOrigin()->GetID()) + " -> " + std::to_string(e.GetDestination()->GetID()) + " | " + std::to_string(e.GetCount()), PrintType::DEBUG);
		Print("------------------------------------------------------", PrintType::DEBUG);
	}
	*/

	Print("------------------ | Fight Results |------------------", PrintType::DEBUG);
	for (auto const& e : event->GetFightResults()) {
		if (not e.IsValid()) { Print("invalid update Evaluation", PrintType::DEBUG);  continue; }

		Print(std::to_string(e.GetSpaceObjects().first->GetID()) + " | " + std::to_string(e.GetSpaceObjects().second->GetID()), PrintType::DEBUG);
		Print(appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().first->GetID()).GetName()
			+ " | " +
			appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().second->GetID()).GetName(), PrintType::DEBUG);

		for (auto const& r : e.GetRounds()) {
			Print(std::to_string(r.first) + " | " + std::to_string(r.second), PrintType::DEBUG);
		}
		Print("------------------------------------------------------", PrintType::DEBUG);
	}
	Print("------------------------------------------------------", PrintType::DEBUG);
}
void UpdateEvaluationScene::DisplayMergeResult() {
	AppContext_ty_c appContext{ AppContext::GetInstance() };
	auto const data {m_mergeResults.at(m_currentIndex)};
	auto const playerName{
		appContext.playerCollection.GetPlayerByID(
			data.GetPlayer()->GetID()
		).GetName()
	};
	
	std::string spaceOpjectText;
	     if (data.GetDestination()->IsFleet())       { spaceOpjectText = appContext.languageManager.Text("helper_fleet");        }
	else if (data.GetDestination()->IsPlanet())      { spaceOpjectText = appContext.languageManager.Text("helper_planet");       }
	else if (data.GetDestination()->IsTargetPoint()) { spaceOpjectText = appContext.languageManager.Text("helper_target_point"); }
	else                                             { spaceOpjectText = "Invalid";                                              }

	std::string const subText{
		appContext.languageManager.Text(
			"ui_popup_arriving_fleet_subtitle",
			data.GetCount(),
			playerName,
			spaceOpjectText,
			data.GetDestination()->GetID()
		)
	};

	ShowMessagePopUpEvent const event{
		appContext.languageManager.Text("ui_popup_arriving_fleet_title"),
		subText,
		[this]() {this->HandleNextPopup(); }
	};
	appContext.eventManager.InvokeEvent(event);
}
void UpdateEvaluationScene::DisplayFightResult() {
	// implement fight result popup
}
void UpdateEvaluationScene::HandleNextPopup() {

	auto const setNext{ [&]() {
		m_currentIndex = 0;
		int value = static_cast<int>(m_currentResultType);
		++value;
		m_currentResultType = static_cast<ResultType>(value);
	} };

	switch (m_currentResultType) {
		case ResultType::MERGE:
			if (m_currentIndex >= m_mergeResults.size()) {
				setNext();
				goto fight;
			}
			DisplayMergeResult();
			break;
		case ResultType::FIGHT:
		fight:		
			if (m_currentIndex >= m_fightResults.size()) {
				setNext();
				goto last;
			}
			DisplayFightResult();
			break;
		default:
		case ResultType::LAST:
		last:
			AppContext_ty_c appContext{ AppContext::GetInstance() };
			if (m_popupCount == 0) {
				ShowMessagePopUpEvent const event{
					appContext.languageManager.Text("ui_popup_no_evaluation_title"),
					appContext.languageManager.Text("ui_popup_no_evaluation_subtitle"),
					[this]() {this->HandleNextPopup(); }
				};
				appContext.eventManager.InvokeEvent(event);
				break;
			}
			ShowMessagePopUpEvent const event{
				appContext.languageManager.Text("ui_popup_end_of_evaluation_title"),
				appContext.languageManager.Text("ui_popup_end_of_evaluation_subtitle"),
				[]() {
					SwitchSceneEvent const event{ SceneType::MAIN };
					AppContext::GetInstance().eventManager.InvokeEvent(event);
				}
			};
			appContext.eventManager.InvokeEvent(event);
			break;
	}

	++m_popupCount;
	++m_currentIndex;
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
		m_mergeResults = evEvent->GetMergeResults();
		m_fightResults = evEvent->GetFightResults();
		HandleNextPopup();
		Initialize(evEvent);
	}
}
