//
// Purpur Tentakel
// 03.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"

template<typename EntryType>
class PrivitiveCellPopUp final : public CellPopUp {
private:
	std::shared_ptr<InputLine<EntryType>> m_inputChange;
	std::function<void(EntryType)> m_onClick = [](EntryType) {};

	void Initialize(AppContext const& appContext,
		Vector2 resolution, EntryType currentValue) {

		auto acceptBtn = InitializeAcceptButton(appContext, resolution);
		acceptBtn->SetOnClick([this]() {
			this->SetValue();
			});

		auto inputChance = std::make_shared<InputLine<EntryType>>(
			3,
			GetElementPosition(m_pos, m_size, 0.5f, 0.55f),
			GetElementSize(m_size, 0.9f, 0.2f),
			Alignment::MID_MID,
			50,
			resolution
			);

		auto event = NewFocusPopUpElementEvent(inputChance.get());
		appContext.eventManager.InvokeEvent(event);

		auto event2 = SelectFocusPopUpElementEvent(inputChance.get());
		appContext.eventManager.InvokeEvent(event2);
		inputChance->SetValue(currentValue);
		inputChance->SetPlaceholderText("Edit Entry");

		m_elements.push_back(inputChance);
		m_inputChange = inputChance;

	}
	void SetValue() override {
		m_onClick(m_inputChange->GetValue());
		SetShouldClose();
	}

public:
	PrivitiveCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture,
		EntryType currentValue, std::function<void(EntryType)> onClick)
		: CellPopUp(pos, size, alignment, resolution, title, infoTexture),
		m_onClick(onClick) {

		Initialize(AppContext::GetInstance(), resolution, currentValue);
	}
};