//
// Purpur Tentakel
// 31.10.2022
//

#include "NewGameParameter.h"
#include "AppContext.h"
#include "Text.h"
#include "Title.h"

void NewGameParameterScene::Initialize(Vector2 resolution) {
	AppContext& appContext = AppContext::GetInstance();

	// title
	m_elements.push_back(std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		false,
		resolution,
		appContext
		));

	// parameters
	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.5f, 0.5f),
		GetElementSize(0.8f, 0.1f),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		0.05f,
		"Parameter",
		resolution
		));

}
