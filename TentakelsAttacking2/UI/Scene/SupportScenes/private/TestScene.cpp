//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "ClassicButton.h"
#include "SceneType.h"
#include "AppContext.h"
#include <iostream>

enum class TableToggle {
	HEADLINE,
	FIRST_COLUMN,
	SCROLLABLE
};

void TestScene::Initialize(	[[maybe_unused]] AppContext& appContext) {

	m_table = std::make_shared<Table2>(
		Vector2(0.5f, 0.5f), // pos
		Vector2(0.5f, 0.5f), // size
		Alignment::MID_MID,
		m_resolution,
		1, // focus ID
		15, // row count
		6, // column count
		Vector2(0.15f, 0.08f),// min cell size
		0.025f // scroll speed
	);
	m_elements.push_back(m_table);

	m_table->SetRowEditable(2, false);
	m_table->SetColumnEditable(1, false);

	m_table->SetScrollable(true);
	//m_table->SetFixedHeadline(true);
	//m_table->SetFixedFirstColumn(true);


	// to get Back No testing
	auto backBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.05f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"Back",
		SoundType::CLICKED_PRESS_STD
	);
	backBtn->SetOnClick([]() {
		auto event = SwitchSceneEvent(SceneType::MAIN_MENU);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(backBtn);

	auto toggleHeadlineButton = std::make_shared<ClassicButton>(
		1001,
		GetElementPosition(0.25f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"toggle headline",
		SoundType::CLICKED_PRESS_STD
	);
	toggleHeadlineButton->SetOnClick([this, type = TableToggle::HEADLINE]() {
		this->ToggleTable(type);
		});
	m_elements.push_back(toggleHeadlineButton);

	auto toggleFirstRowButton = std::make_shared<ClassicButton>(
		1002,
		GetElementPosition(0.45f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"toggle first row",
		SoundType::CLICKED_PRESS_STD
	);
	toggleFirstRowButton->SetOnClick([this, type = TableToggle::FIRST_COLUMN]() {
		this->ToggleTable(type);
		});
	m_elements.push_back(toggleFirstRowButton);

	auto toggleScrollable = std::make_shared<ClassicButton>(
		1003,
		GetElementPosition(0.65f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"toggle scrollable",
		SoundType::CLICKED_PRESS_STD
	);
	toggleScrollable->SetOnClick([this, type = TableToggle::SCROLLABLE]() {
		this->ToggleTable(type);
		});
	m_elements.push_back(toggleScrollable);
}



TestScene::TestScene(Vector2 resolution)
	: Scene(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Alignment::DEFAULT, resolution) {

	AppContext& appContext = AppContext::GetInstance();
	Initialize(appContext);
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda([[maybe_unused]] unsigned int value) {
}

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}

void TestScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);
}

void TestScene::ToggleTable(TableToggle type) {
	switch (type) {
		case TableToggle::HEADLINE:
			m_table->SetFixedHeadline(!m_table->IsFixedHeadline());
			break;
		case TableToggle::FIRST_COLUMN:
			m_table->SetFixedFirstColumn(!m_table->IsFixedFirstColumn());
			break;
		case TableToggle::SCROLLABLE:
			m_table->SetScrollable(!m_table->IsScollable());
			break;
	}
}
