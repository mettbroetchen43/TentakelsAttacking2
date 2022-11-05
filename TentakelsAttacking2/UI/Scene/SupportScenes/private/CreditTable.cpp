//
// Purpur Tentakel
// 05.11.2022
//

#include "CreditTable.h"
#include "Table.h"
#include "Text.h"
#include "Line.h"

void CreditTableScene::Initialize(Vector2 resolution, int rows, unsigned int focusID, std::string const& headline) {
	// headline
	auto headlineText = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.0f),
		GetElementSize(0.5f, 0.05f),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		0.05f * m_size.y,
		headline,
		resolution
		);
	headlineText->RenderRectangle(true);
	m_elements.push_back(headlineText);

	auto headlineLine = std::make_shared<Line>(
		GetElementPosition(0.5f, 0.05f),
		GetElementSize(0.5f, 0.0f),
		Alignment::TOP_MID,
		3.0f,
		resolution
		);
	m_elements.push_back(headlineLine);
	

	// table
	auto table = std::make_shared<Table>(
		GetElementPosition(0.5f, 0.1f),
		GetElementSize(1.0f, 0.9f),
		Alignment::TOP_MID,
		focusID,
		rows,
		2,
		resolution
		);
	table->SetAllCellsEditable(false);
	table->SetValue<std::string>(0, 0, "test");
	table->SetValue<std::string>(1, 0, "test");
	m_elements.push_back(table);
}

CreditTableScene::CreditTableScene(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
	int rows, std::string const& headline, Vector2 resolution)
	: Scene(pos, size, alignment) {
	GetAlignedCollider(m_pos, m_size, alignment, resolution);
	Initialize(resolution, rows, focusID, headline);
}
