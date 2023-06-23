//
// Purpur Tentakel
// 03.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"

/**
 * provides a popup that can represent all primitive types and update the table.
 */
template<typename T>
class PrivativeCellPopUp final : public CellPopUp {
private:
	std::shared_ptr<InputLine<T>> m_inputChange; ///< contains the input line for the current type
	std::function<void(T)> m_onClick{ [](T) {} }; ///< contains the lambda that sets the edited value

	/**
	 * initializes all ui elements.
	 */
	void Initialize(AppContext_ty_c appContext,
		Vector2 resolution, T currentValue) {

		auto acceptBtn = InitializeAcceptButton(appContext, resolution);
		acceptBtn->SetOnClick([this]() {
			this->SetValue();
			});

		auto inputChance = std::make_shared<InputLine<T>>(
			3,
			GetElementPosition(m_pos, m_size, 0.5f, 0.55f),
			GetElementSize(m_size, 0.9f, 0.2f),
			Alignment::MID_MID,
			resolution,
			50
			);

		NewFocusPopUpElementEvent event{ inputChance.get() };
		appContext.eventManager.InvokeEvent(event);

		SelectFocusPopUpElementEvent event2{ inputChance.get() };
		appContext.eventManager.InvokeEvent(event2);
		inputChance->SetValue(currentValue);
		inputChance->SetPlaceholderText(appContext.languageManager.Text("ui_primitive_cell_popup_input_line_placeholder_text");

		m_elements.push_back(inputChance);
		m_inputChange = inputChance;

	}
	/**
	 * gets the value from the input line and calls on click.
	 * sets should close afterword's.
	 */
	void SetValue() override {
		m_onClick(m_inputChange->GetValue());
		SetShouldClose();
	}

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	PrivativeCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture,
		T currentValue, std::function<void(T)> onClick)
		: CellPopUp{ pos, size, alignment, resolution, title, infoTexture },
		m_onClick{ onClick } {

		Initialize(AppContext::GetInstance(), resolution, currentValue);
	}
};
