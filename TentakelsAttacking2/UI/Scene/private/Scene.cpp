//
// Purpur Tentakel
// 05.09.2022
//

#include "Scene.h"
#include "Focus.h"
#include "Focusable.h"
#include "AppContext.h"

void Scene::SetFocusActive(AppContext const& appContext) {
	if (m_active) {
		for (auto& element : m_elements) {
			if (auto focusable = dynamic_cast<Focusable*>(element.get())) {
				auto event = NewFocusElementEvent(focusable);
				appContext.eventManager.InvokeEvent(event);
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
	return nullptr;
}

Scene::Scene(Vector2 pos, Vector2 size, Alignment alignment)
	:UIElement(pos, size, alignment), m_firstFocusID(0) { }

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

void Scene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
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
	for (auto& element : m_elements) {
		element->Resize(resolution, appContext);
	}
}