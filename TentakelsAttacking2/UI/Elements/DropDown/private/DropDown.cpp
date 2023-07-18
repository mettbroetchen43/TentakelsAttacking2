//
// Purpur Tentakel
// 01.12.2022
//

#include "DropDown.h"
#include "DropDownElement.h"
#include "HTextProcessing.h"
#include "HInput.h"
#include "HFocusEvents.h"
#include "UIEvents.hpp"
#include "AppContext.h"
#include <algorithm>



void DropDown::Initialize(std::vector<std::string> const& elements, unsigned int startFocusID) {

	float const x{ m_pos.x + m_size.x * 0.01f };
	float       y{ m_pos.y + m_size.y };
	float const width{ m_size.x * 0.98f };
	float const height{ m_size.y * 2 / 3 };

	for (size_t i = 0; i < elements.size(); ++i) {
		auto entry = std::make_shared<DropDownElement>(
			Vector2(x, y),
			Vector2(width, height),
			Alignment::DEFAULT,
			m_resolution,
			startFocusID,
			static_cast<unsigned int>(i + 1),
			elements.at(i),
			[this](Rectangle collider) -> Rectangle {
				return this->GetTemporaryCollider(collider);
			}
		);
		entry->SetOnClick([this](unsigned int ID) {
			this->OnElementClick(ID);
			});
		entry->SetEnabled(false);
		m_dropDownElements.push_back(entry);
		++startFocusID;
		y += height;

		if (i == 0) {
			SetCurrentElement(entry);
		}
	}
}

void DropDown::OnElementClick(unsigned int ID) {
	SetCurrentElementByID(ID);
}

void DropDown::SetCurrentElement(std::shared_ptr<DropDownElement> element) {
	m_currentElement = element;

	SetText();

	m_onSave(element->GetID());
}

void DropDown::SetText() {
	m_currentElementText = m_currentElement->GetText();
	StripString(m_currentElementText);
	m_fontSize = GetElementTextHeight(
		m_size,
		m_resolution.y
	);
	m_currentElementText = GetPrintableTextInCollider(
		m_currentElementText,
		m_fontSize,
		m_collider,
		AppContext::GetInstance()
	);

	m_textPosition = {
		m_collider.x + 5.0f,
		m_collider.y + (m_collider.height - m_fontSize) / 2
	};
}

void DropDown::ToggleFoldedOut() {

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	m_isFoldouts = !m_isFoldouts;

	appContext.eventManager.InvokeEvent(PlaySoundEvent(SoundType::CLICKED_PRESS_STD));

	if (m_isFoldouts) {
		m_arrowTexture = appContext.assetManager.GetTexture(AssetType::ARROW_DOWN);
		AddFocusLayer();
		for (auto const& e : m_dropDownElements) {
			AddFocusElement(e.get());
		}
		CheckAndSetElementsEnabled();
	}
	else {
		m_arrowTexture = appContext.assetManager.GetTexture(AssetType::ARROW_UP);
		DeleteFocusLayer();
	}
}

Rectangle DropDown::GetTemporaryCollider(Rectangle collider) const {

	return GetCollisionRec(m_dropDownCollider, collider);
}

void DropDown::CheckAndSetElementsEnabled() {
	for (auto const& e : m_dropDownElements) {
		bool const overlap{ CheckCollisionRecs(m_dropDownCollider, e->GetCollider()) };
		e->SetEnabled(overlap);
	}
}

void DropDown::ScrollMove(float wheel) {

	if (!m_isScrolling) { return; }

	for (auto const& e : m_dropDownElements) {
		Vector2 pos{ e->GetPosition() };
		pos.y += 0.025f * wheel;
		e->SetPositionUnaligned(pos);
	}
	CheckAndSetElementsEnabled();
	ClampScrolling();
}
void DropDown::ClampScrolling() {

	float offset{ 0.0f };
	auto element{ m_dropDownElements.front() };
	float dropDownValue{ m_dropDownCollider.y };
	float elementValue{ element->GetCollider().y };
	if (dropDownValue < elementValue) {
		offset = dropDownValue - elementValue;
	}

	element = m_dropDownElements.back();
	dropDownValue = m_dropDownCollider.y + m_dropDownCollider.height;
	elementValue = element->GetCollider().y + element->GetCollider().height;
	if (dropDownValue > elementValue) {
		offset = dropDownValue - elementValue;
	}

	if (offset == 0.0f) { return; }

	for (auto const& e : m_dropDownElements) {
		Rectangle col = e->GetCollider();
		col.y += offset;
		e->SetCollider(col);
	}
}
void DropDown::CheckIfScrolling() {
	float sum{ 0 };

	for (auto const& e : m_dropDownElements) {
		sum += e->GetCollider().height;
		if (m_dropDownCollider.height < sum) { m_isScrolling = true; return; }
	}

	m_isScrolling = sum > m_dropDownCollider.height;
}

void DropDown::UpdateCollider() {

	UIElement::UpdateCollider();
	SetText();

	m_arrowCollider = {
		m_collider.x + m_collider.width,
		m_collider.y,
		m_collider.height,
		m_collider.height
	};

	m_dropDownCollider = {
		m_collider.x,
		m_collider.y + m_collider.height,
		m_collider.width,
		m_resolution.y * m_dropDownHeight
	};
}

DropDown::DropDown(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, float dropDownHeight,
	unsigned int focusID, unsigned int startElementFocusID, std::vector<std::string> const& elements)
	: UIElement{ pos, size, alignment, resolution }, Focusable{ focusID }, m_dropDownHeight{ dropDownHeight } {



	m_arrowTexture = AppContext::GetInstance().assetManager.GetTexture(AssetType::ARROW_UP);
	m_arrowTextureRec = {
		0.0f,
		0.0f,
		static_cast<float>(m_arrowTexture->width),
		static_cast<float>(m_arrowTexture->height)
	};
	m_arrowCollider = {
		m_collider.x + m_collider.width - m_collider.height,
		m_collider.y,
		m_collider.height,
		m_collider.height
	};

	m_dropDownCollider = {
	m_collider.x,
	m_collider.y + m_collider.height,
	m_collider.width - m_arrowCollider.width,
	m_resolution.y * m_dropDownHeight
	};

	m_collider.width -= m_arrowCollider.width;
	UpdateColliderReverse();

	Initialize(elements, startElementFocusID);
}

std::shared_ptr<DropDownElement> DropDown::GetCurrentElement() const {

	return m_currentElement;
}

bool DropDown::SetCurrentElementByID(unsigned int ID) {

	for (auto const& e : m_dropDownElements) {
		if (e->GetID() == ID) {
			SetCurrentElement(e);
			if (m_isFoldouts) {
				ToggleFoldedOut();
			}
			return true;
		}
	}
	return false;
}
bool DropDown::SetCurrentElementByString(std::string const& element) {

	for (auto const& e : m_dropDownElements) {
		if (e->GetText() == element) {
			SetCurrentElement(e);
			return true;
		}
	}
	return false;
}

void DropDown::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	bool const hover{
		   CheckCollisionPointRec(mousePosition, m_collider)
		or CheckCollisionPointRec(mousePosition, m_arrowCollider) 
	};

	bool first{ false };
	if (hover) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			ToggleFoldedOut();
			first = true;
		}
	}
	if (IsFocused()) {
		if (IsConfirmInputPressed() && !IsNestedFocus() && !m_isFoldouts) {
			ToggleFoldedOut();
			first = true;
		}
		if (IsBackInputPressed() && m_isFoldouts) {
			ToggleFoldedOut();
			first = true;
		}
	}

	if (m_isFoldouts) {
		float const wheel{ GetMouseWheelMove() };
		if (wheel != 0.0f) {
			CheckIfScrolling();
			ScrollMove(wheel);
		}
	}

	if (m_isFoldouts && !first) {
		for (auto const& e : m_dropDownElements) {
			e->CheckAndUpdate(mousePosition, appContext);
		}
	}
}
void DropDown::Render(AppContext_ty_c appContext) {
	DrawRectangleLinesEx(
		m_collider,
		2.0f,
		WHITE
	);

	if (m_currentElement) {
		DrawTextPro(
			*(appContext.assetManager.GetFont()),
			m_currentElementText.c_str(),
			m_textPosition,
			{ 0.0f,0.0f },
			0.0f,
			m_fontSize,
			0.0f,
			WHITE
		);
	}

	DrawRectangleLinesEx(
		m_arrowCollider,
		2.0f,
		WHITE
	);

	float const offset{ m_collider.height * 0.1f };
	DrawTexturePro(
		*m_arrowTexture,
		m_arrowTextureRec,
		{
			m_arrowCollider.x + offset,
			m_arrowCollider.y + offset,
			m_arrowCollider.width - 2.0f * offset,
			m_arrowCollider.height - 2.0f * offset,
		},
		{ 0.0f,0.0f },
		0.0f,
		WHITE
	);

	if (m_isFoldouts) {

		BeginScissorMode(
			static_cast<int>(m_dropDownCollider.x),
			static_cast<int>(m_dropDownCollider.y),
			static_cast<int>(m_dropDownCollider.width),
			static_cast<int>(m_dropDownCollider.height + 2.0f)
		);

		for (auto const& e : m_dropDownElements) {
			e->Render(appContext);
		}

		EndScissorMode();
	}
}
void DropDown::Resize(Vector2 resolution, AppContext_ty_c appContext) {

	UIElement::Resize(resolution, appContext);


	for (auto const& element : m_dropDownElements) {
		element->Resize(resolution, appContext);
	}
}

bool DropDown::IsEnabled() const {
	return m_isEnabled;
}
void DropDown::SetEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
}

bool DropDown::IsFoldedOut() const {
	return m_isFoldouts;
}

Rectangle DropDown::GetCollider() const {
	return m_collider;
}

void DropDown::SetOnSave(std::function<void(unsigned int)> onSave) {
	m_onSave = onSave;
}
