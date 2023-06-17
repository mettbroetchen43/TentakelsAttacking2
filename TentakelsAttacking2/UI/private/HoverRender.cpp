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

Vector2 HoverRender::GetStartRenderingOffset() const {
	Vector2 offset{ 0.0f, 0.0f };
	for (auto const& e : m_elements) {
		auto const singleOffset{ e->GetRenderOffset() };
		if (offset.x < singleOffset.x) { offset.x = singleOffset.x; }
		if (offset.y < singleOffset.y) { offset.y = singleOffset.y; }
	}

	return offset;
}

void HoverRender::Render() {
	if (m_elements.size() == 0) { return; }

	AppContext_ty appContext = AppContext::GetInstance();
	if (m_elements.size() == 1) {
		m_elements.at(0)->Render(appContext);
		m_elements.clear();
		return;
	}

	auto renderingOffset{ GetStartRenderingOffset() };
	auto const increase{ [&](float offset) {
		renderingOffset.y -= offset + m_renderGap;
	} };

	for (auto const& hover : m_elements) {
		auto const newOffset = hover->RenderOffset(appContext, renderingOffset);
		increase(newOffset);
	}
	m_elements.clear();
}

void HoverRender::OnEvent(Event const& event) {
	if (auto const* HoverEvent = dynamic_cast<RenderHoverEvent const*>(&event)) {
		m_elements.push_back(HoverEvent->GetHover());
		return;
	}
}
