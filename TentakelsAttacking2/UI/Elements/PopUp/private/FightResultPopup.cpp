//
// Purpur Tentakel
// 06.07.2023
// 

#include "FightResultPopup.h"
#include "AppContext.h"
#include "Text.h"
#include "Player.h"
#include "ClassicButton.h"
#include "SpaceObject.h"
#include "CountingNumber.h"
#include "HTextProcessing.h"

void FightResultPopup::Initialize() {
	// constants
	AppContext_ty_c appContext{ AppContext::GetInstance() };
	float constexpr leftX     { 0.25f };
	float constexpr rightX    { 0.75f };
	float           Y         { 0.35f };
	float const     textSize  { GetElementTextHeight(m_size, 0.07f)};

	// subtitle
	std::string fightText{"invalid"};
	auto const& object{ m_result.GetSpaceObjects().first };
	     if (object->IsPlanet())      { fightText = { "Fight at Planet " + std::to_string(object->GetID()) }; }
	else if (object->IsFleet())       { fightText = { "Fight at " + std::to_string(object->GetPos().x) + " / " + std::to_string(object->GetPos().y) }; }
	else if (object->IsTargetPoint()) { fightText = { "Fight at " + std::to_string(object->GetPos().x) + " / " + std::to_string(object->GetPos().y) }; }
	
	auto const subtitle = std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, 0.6f, Y),
		GetElementSize(m_size, 0.7f, textSize * 1.2f),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		textSize * 1.2f,
		fightText
	);
	m_elements.push_back(subtitle);

	Y += 0.15f;

	// player names
	auto playerName = std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, leftX, Y),
		GetElementSize(m_size, 0.5f,textSize),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		textSize,
		appContext.playerCollection.GetPlayerOrNpcByID(m_result.GetPlayer().first->GetID()).GetName()
	);
	m_elements.push_back(playerName);

	playerName = std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, rightX, Y),
		GetElementSize(m_size, 0.5f, textSize),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		textSize,
		appContext.playerCollection.GetPlayerOrNpcByID(m_result.GetPlayer().second->GetID()).GetName()
	);
	m_elements.push_back(playerName);

	Y += 0.1f;

	// numbers
	auto firstNumber{ m_result.GetRounds().at(0).first };
	m_leftNumber = std::make_shared<CountingNumber>(
		GetElementPosition(m_pos, m_size, leftX, Y),
		GetElementSize(m_size, 0.5f, textSize * 1.5f),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		textSize * 1.5f,
		static_cast<int>(firstNumber)
	);
	m_leftNumber->SetCallback([this](CountingNumber::Type type, int from, int to, double time) {
		this->NextNumber(type, from, to, time); 
		});
	m_elements.push_back(m_leftNumber);

	firstNumber = { m_result.GetRounds().at(0).second };
	m_rightNumber = std::make_shared<CountingNumber>(
		GetElementPosition(m_pos, m_size, rightX, Y),
		GetElementSize(m_size, 0.5f, textSize * 1.5f),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		textSize * 1.5f,
		static_cast<int>(firstNumber)
	);
	m_rightNumber->SetCallback([this](CountingNumber::Type type, int from, int to, double time) {
		this->NextNumber(type, from, to, time);
		});
	m_elements.push_back(m_rightNumber);

	Y += 0.1f;

	// win text
	m_winText = std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, 0.5f, Y),
		GetElementSize(m_size, 0.8f, textSize * 1.5f),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		textSize * 1.5f,
		""
	);
	m_elements.push_back(m_winText);
	
	// button
	m_closeBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(m_pos, m_size, 0.5f, 0.95f),
		GetElementSize(m_size, 0.2f, 0.15f),
		Alignment::BOTTOM_MID,
		m_resolution,
		"skip",
		SoundType::CLICKED_RELEASE_STD
	);
	m_closeBtn->SetOnClick([this]() {this->HandleButton(); });
	m_elements.push_back(m_closeBtn);
}

void FightResultPopup::NextNumber() {
	if (m_finishedCounting) { return; }
	if (m_leftNumber->IsCounting() or m_rightNumber->IsCounting()) { return; }
	if (m_index >= m_result.GetRounds().size()) {
		m_finishedCounting = true;
		SetEnd();
		return;
	}

	float constexpr time{ 1.5f };
	m_leftNumber->CountTo(CountingNumber::ASYMPTOTIC, static_cast<int>(m_result.GetRounds().at(m_index).first), time);
	m_rightNumber->CountTo(CountingNumber::ASYMPTOTIC, static_cast<int>(m_result.GetRounds().at(m_index).second), time);

	++m_index;
}
void FightResultPopup::NextNumber(CountingNumber::Type, int, int, double) {
	NextNumber();
}
void FightResultPopup::SetLastStep() {
	m_index = m_result.GetRounds().size() - 1;
	m_leftNumber ->SetTo(static_cast<int>(m_result.GetRounds().at(m_index).first));
	m_rightNumber->SetTo(static_cast<int>(m_result.GetRounds().at(m_index).second));
	SetEnd();
}
void FightResultPopup::SetEnd() {
	m_closeBtn->SetText("Next");

	std::string dummy;
	if (m_result.GetRounds().at(m_result.GetRounds().size() - 1).first == 0) {
		dummy = AppContext::GetInstance().playerCollection.GetPlayerOrNpcByID(m_result.GetPlayer().second->GetID()).GetName();
		m_leftNumber->SetDefaultColor(RED);
	}
	else {
		dummy = AppContext::GetInstance().playerCollection.GetPlayerOrNpcByID(m_result.GetPlayer().first->GetID()).GetName();
		m_rightNumber->SetDefaultColor(RED);
	}


	m_winText->SetText(dummy + " wins!");
}
void FightResultPopup::HandleButton() {
	if (not m_finishedCounting){
		m_finishedCounting = true;
		SetLastStep();
		return;
	}
	m_shouldClose = true;
	m_callback();
}

FightResultPopup::FightResultPopup(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	HFightResult const result, callback_ty callback)
	: PopUp{ pos, size, alignment, resolution, "Fight", s_emptyString, AssetType::EXCLAMATION_MARK},
	m_result{result}, m_callback{callback} {

	Initialize();
	NextNumber();
}
