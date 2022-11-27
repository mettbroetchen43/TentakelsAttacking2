//
// Purpur Tentakel
// 05.09.2022
//

#include "Scene.h"
#include "Focus.h"
#include "Focusable.h"
#include "AppContext.h"
#include "HFocusEvents.h"

void Scene::SetFocusActive(AppContext const&) {
	if (m_active) {
		for (auto& element : m_elements) {
			if (auto focusable = dynamic_cast<Focusable*>(element.get())) {
				AddFocusElement(focusable);
				continue;
			}
		}
		for (auto& element : m_elementsOutUpdates) {
			if (auto focusable = dynamic_cast<Focusable*>(element.get())) {
				AddFocusElement(focusable);
				continue;
			}
		}
	}
	else {
		for (auto& element : m_elements) {
			if (auto focusable = dynamic_cast<Focusable*>(element.get())) {
				DeleteFocusElement(focusable);
				continue;
			}
		}
		for (auto& element : m_elementsOutUpdates) {
			if (auto focusable = dynamic_cast<Focusable*>(element.get())) {
				DeleteFocusElement(focusable);
				continue;
			}
		}
	}
}

Vector2 Scene::GetElementPosition(float x, float y) {
	return {
		m_pos.x + x * m_size.x,
		m_pos.y + y * m_size.y
	};
}
Vector2 Scene::GetElementSize(float x, float y) {
	return {
		x * m_size.x,
		y * m_size.y
	};
}

Focusable* Scene::GetFocusableByFocusID(unsigned int ID) const {
	for (auto element : m_elements) {
		if (auto focus = dynamic_cast<Focusable*>(element.get())) {
			if (focus->GetFocusID() == ID) {
				return focus;
			}
		}
	}
	for (auto element : m_elementsOutUpdates) {
		if (auto focus = dynamic_cast<Focusable*>(element.get())) {
			if (focus->GetFocusID() == ID) {
				return focus;
			}
		}
	}
	return nullptr;
}

	
Scene::Scene(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution)
	:UIElement(pos, size, alignment, resolution) { }

bool Scene::IsActive() const {
	return m_active;
}
void Scene::SetActive(bool active, AppContext const& appContext) {
	if (active == m_active) {
		return;
	}

	m_active = active;
	SetFocusActive(appContext);
}

void Scene::SetPosition(Vector2 pos) {
	Vector2 dif = {
		m_pos.x - pos.x,
		m_pos.y - pos.y
	};

	for (auto e : m_elements) {
		Vector2 ePos = e->GetPosition();
		ePos = {
			ePos.x - dif.x,
			ePos.y - dif.y
		};
		e->SetPosition(ePos);
	}
	for (auto e : m_elementsOutUpdates) {
		Vector2 ePos = e->GetPosition();
		ePos = {
			ePos.x - dif.x,
			ePos.y - dif.y
		};
		e->SetPosition(ePos);
	}

	UIElement::SetPosition(pos);
}
void Scene::SetSize(Vector2 size) {
	Vector2 dif = {
	m_size.x - size.x,
	m_size.y - size.y
	};

	for (auto e : m_elements) {
		Vector2 eSize = e->GetSize();
		eSize = {
			eSize.x - dif.x,
			eSize.y - dif.y
		};
		e->SetSize(eSize);
	}
	for (auto e : m_elementsOutUpdates) {
		Vector2 eSize = e->GetSize();
		eSize = {
			eSize.x - dif.x,
			eSize.y - dif.y
		};
		e->SetSize(eSize);
	}

	UIElement::SetSize(size);
}

void Scene::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	if (!m_active) {
		return;
	}

	for (auto& element : m_elements) {
		element->CheckAndUpdate(mousePosition, appContext);
	}
}
void Scene::Render(AppContext const& appContext) {
	if (!m_active) {
		return;
	}

	for (auto& element : m_elements) {
		element->Render(appContext);
	}
}
void Scene::Resize(Vector2 resolution, AppContext const& appContext) {

	UIElement::Resize(resolution, appContext);

	for (auto& element : m_elements) {
		element->Resize(resolution, appContext);
	}
}