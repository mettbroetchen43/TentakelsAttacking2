//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorPicker.h"
#include "AppContext.h"
#include "ColorPickerCell.h"
#include "HGeneral.h"
#include "HFocusEvents.h"
#include "HInput.h"
#include <cmath>


void ColorPicker::Initialize(Vector2 resolution) {
	AppContext_ty_c appContext{ AppContext::GetInstance() };

	auto const colors{ appContext.colors.GetColors() };

	double const countX_D{ std::ceil(std::sqrt(colors.size())) };
	m_countX = static_cast<size_t>(countX_D);
	m_countY = static_cast<size_t>(std::ceil(colors.size() / countX_D));

	for (int row = 0; row < m_countY; ++row) {
		for (int column = 0; column < m_countX; ++column) {

			size_t const index{ GetIndexFromRowAndColumn(row, column, m_countX) };
			// start					offset
			float const posX{ (1.0f / (2 * m_countX)) + (1.0f / m_countX * column) };
			float const posY{ (1.0f / (2 * m_countY)) + (1.0f / m_countY * row) };
			float const sizeX{ 0.8f / m_countX };
			float const sizeY{ 0.7f / m_countY };

			Color const color{ colors.size() > index ? colors.at(index) : BLANK };

			m_cells.push_back(std::make_unique<ColorPickerCell>(
				static_cast<unsigned int>(index + 1),
				GetElementPosition(m_pos, m_size, posX, posY),
				GetElementSize(m_size, sizeX, sizeY),
				Alignment::MID_MID,
				resolution,
				color,
				this
				));
		}
	}
}
void ColorPicker::SetUsedColors(AppContext_ty_c appContext) {
	auto const& players = appContext.playerCollection.GetPlayerData();

	for (auto& c : m_cells) {
		bool sameColor{ false };
		for (auto& p : players) {
			if (c->GetColor() == p.color) {
				sameColor = true;
				break;
			}
		}

		c->SetEnabled(!sameColor);
	}
}
void ColorPicker::SetColorFromFocus() {
	if (!m_isNestedFocus) {
		return;
	}

	for (auto const& c : m_cells) {
		if (c->IsFocused()) {
			m_currentColorCell = c.get();
			return;
		}
	}
}
void ColorPicker::CheckForValidColor(AppContext_ty_c appContext) {
	if (m_currentColorCell) {
		if (m_currentColorCell->IsEnabled()) {
			return;
		}
	}
	
	SetColor(appContext.playerCollection.GetPossibleColor());
}

ColorPicker::ColorPicker(unsigned int ID, Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution, bool isPopUp)
	: Focusable{ ID }, UIElement{ pos, size, alignment, resolution }, m_isPopUp{ isPopUp } {

	m_backGround = AppContext::GetInstance().assetManager.GetTexture(AssetType::GREY);
	Initialize(resolution);
}
ColorPicker::~ColorPicker() {
	if (!m_isNestedFocus) {
		return;
	}

	DeleteFocusLayer(m_isPopUp);
}

Color ColorPicker::GetColor() const {
	if (m_currentColorCell) {
		return m_currentColorCell->GetColor();
	}
	return BLANK;
}
bool ColorPicker::HasColorChanced() const {
	return {
		    m_currentColorCell->GetColor()
		!=  m_previousColorCell->GetColor()
	};
}
bool ColorPicker::SetInitialColor(Color color) {
	bool const set{ SetColor(color) };
	m_previousColorCell = m_currentColorCell;
	return set;
}
bool ColorPicker::SetColor(Color color) {
	for (auto& c : m_cells) {
		if (c->GetColor() == color) {
			if (!c->IsEnabled()) {
				m_currentColorCell = nullptr;
				return false;
			}

			m_currentColorCell = c.get();
			if (m_isNestedFocus) {
				SelectFocusElementEvent const event { c.get() };
				AppContext::GetInstance().eventManager.InvokeEvent(event);
			}
			return true;
		}
	}

	return false;
}

void ColorPicker::SetOnEnter(std::function<void()> onEnter) {
	m_onEnter = onEnter;
}

void ColorPicker::SetCellFocuses([[maybe_unused]] AppContext_ty_c appContext) {
	if (m_isNestedFocus) {
		return;
	}

	AddFocusLayer(m_isPopUp);

	for (auto const& c : m_cells) {
		AddFocusElement(c.get(), m_isPopUp);
	}

	if (m_currentColorCell) {
		SelectFocusElement(m_currentColorCell, m_isPopUp);
	}
	else {
		SelectFocusElement(m_cells.at(0).get(), m_isPopUp);
	}

	m_isNestedFocus = true;
}
void ColorPicker::SetEnabled(bool enabled, Color color) {
	for (auto& c : m_cells) {
		if (c->GetColor() == color) {
			c->SetEnabled(enabled);
			return;
		}
	}
}
bool ColorPicker::IsEnabled() const {
	return true;
}

[[nodiscard]] bool ColorPicker::IsPopUp() const {
	return m_isPopUp;
}

void ColorPicker::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (IsBackInputPressed()) {
		if (!m_isNestedFocus) {
			return;
		}
		DeleteFocusLayer(m_isPopUp);
		m_isNestedFocus = false;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if (CheckCollisionPointRec(mousePosition, m_collider)) {
			SelectFocusElement(this, m_isPopUp);
		}
	}

	if (IsFocused() and IsConfirmInputPressed()) {
		if (!m_isNestedFocus) {
			SetCellFocuses(appContext);
		}
		else {
			m_onEnter();
		}
	}

	for (auto const& c : m_cells) {
		c->CheckAndUpdate(mousePosition, appContext);
	}

	SetUsedColors(appContext);
	SetColorFromFocus();
	CheckForValidColor(appContext);
}
void ColorPicker::Render(AppContext_ty_c appContext) {
	// update here to make sure all CheckAndUpdate() is done
	m_previousColorCell = m_currentColorCell;

	DrawTexturePro(
		*m_backGround,
		Rectangle(
			0.0f,
			0.0f,
			static_cast<float>(m_backGround->width),
			static_cast<float>(m_backGround->height)
		),
		m_collider,
		Vector2(0.0f, 0.0f),
		0.0f,
		WHITE
	);

	DrawRectangleLinesEx(
		m_collider,
		3.0f,
		PURPLE
	);


	for (auto const& c : m_cells) {
		c->Render(appContext);
	}

	if (m_currentColorCell) {
		DrawRectangleLinesEx(
			m_currentColorCell->GetCollider(),
			3.0f,
			WHITE
		);
	}
}
void ColorPicker::Resize(Vector2 resolution, AppContext_ty_c appContext) {

	UIElement::Resize(resolution, appContext);

	for (auto const& c : m_cells) {
		c->Resize(resolution, appContext);
	}
}

Rectangle ColorPicker::GetCollider() const {
	return UIElement::GetCollider();
}