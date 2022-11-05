//
// Purpur Tentakel
// 05.11.2022
//

#include "CreditTable.h"
#include "Text.h"
#include "Line.h"
#include "AppContext.h"
#include <cassert>

void CreditTableScene::Initialize(Vector2 resolution, std::string const& headline, 
	std::vector<std::string> const& entries, bool doubleColumn) {
	// headline
	auto headlineText = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.0f),
		GetElementSize(0.8f, 0.15f),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		0.15f * m_size.y,
		headline,
		resolution
	);
	m_elements.push_back(headlineText);

	auto headlineLine = std::make_shared<Line>(
		GetElementPosition(0.5f, 0.15f),
		GetElementSize(0.7f, 0.0f),
		Alignment::TOP_MID,
		3.0f,
		resolution
	);
	m_elements.push_back(headlineLine);

	// elements
	float textHeight = 0.07f;

	if (doubleColumn) {
		assert(entries.size() % 2 == 0);
		for (size_t i = 0; i < entries.size(); i += 2) {
			m_elements.push_back(std::make_shared<Text>(
				GetElementPosition(0.49f, 0.2f + textHeight * (i / 2)),
				GetElementSize(0.5f, textHeight),
				Alignment::TOP_RIGHT,
				Alignment::TOP_RIGHT,
				textHeight * m_size.y,
				entries.at(i),
				resolution
			));

			m_elements.push_back(std::make_shared<Text>(
				GetElementPosition(0.51f, 0.2f + textHeight * (i / 2)),
				GetElementSize(0.5f, textHeight),
				Alignment::TOP_LEFT,
				Alignment::TOP_LEFT,
				textHeight * m_size.y,
				entries.at(i + 1),
				resolution
			));
		}
	}
	else {
		for (size_t i = 0; i < entries.size(); ++i) {
			m_elements.push_back(std::make_shared<Text>(
				GetElementPosition(0.5f, 0.23f + textHeight * i),
				GetElementSize(0.5f, textHeight),
				Alignment::MID_MID,
				Alignment::MID_MID,
				textHeight * m_size.y,
				entries.at(i),
				resolution
			));
		}
	}
}

CreditTableScene::CreditTableScene(Vector2 pos, Vector2 size, Alignment alignment,
	std::string const& headline, std::vector<std::string> const& entries,
	bool doubleColumn, Vector2 resolution)
	: Scene(pos, size, alignment) {
	GetAlignedCollider(m_pos, m_size, alignment, resolution);
	Initialize(resolution, headline, entries, doubleColumn);
}
