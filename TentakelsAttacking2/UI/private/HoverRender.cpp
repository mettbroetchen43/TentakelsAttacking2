//
// Purpur Tentakel
// 14.05.2023
//

#include "HoverRender.h"
#include "Hover.h"
#include "UIEvents.hpp"
#include "AppContext.h"

HoverRender::HoverRender() {
	AppContext::GetInstance().eventManager.AddListener(this);
}

HoverRender::~HoverRender() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void HoverRender::Render() {
	if (m_elements.size() == 0) { return; }

	AppContext_ty appContext = AppContext::GetInstance();
	for (auto const& hover : m_elements) {
		hover->Render(appContext);
	}
	m_elements.clear();
}

void HoverRender::OnEvent(Event const& event) {
	if (auto const* HoverEvent = dynamic_cast<RenderHoverEvent const*>(&event)) {
		m_elements.push_back(HoverEvent->GetHover());
		return;
	}
}
