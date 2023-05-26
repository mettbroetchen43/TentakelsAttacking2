//
// Purpur Tentakel
// 10.09.2022
//

#include "MessagePopUp.h"
#include "AppContext.h"
#include "HGeneral.h"
#include <memory>

void MessagePopUp::Initialize(Vector2 resolution) {
	AppContext_ty_c appContext{ AppContext::GetInstance() };

	auto btn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(m_pos, m_size,0.5f, 0.8f),
		GetElementSize(m_size,0.3f, 0.2f),
		Alignment::MID_MID,
		resolution,
		"OK",
		SoundType::CLICKED_RELEASE_STD
		);

	btn->SetOnClick([this]() {
		this->m_callback();
		AppContext::GetInstance().eventManager.InvokeEvent(ClosePopUpEvent(this));
		});
	NewFocusPopUpElementEvent event{ btn.get() };
	appContext.eventManager.InvokeEvent(event);

	m_elements.push_back(btn);
}

MessagePopUp::MessagePopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	std::string const& title, std::string& subTitle, AssetType infoTexture, std::function<void()> callback)
	: PopUp{ pos, size, alignment, resolution, title, subTitle, infoTexture }, m_callback{ callback } {

	Initialize(resolution);
}

void MessagePopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext_ty_c appContext) {

	if (!m_firstEnter) {
		PopUp::CheckAndUpdate(mousePosition, appContext);
	}

	LateUpdate();
}
