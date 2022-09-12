//
// Purpur Tentakel
// 05.09.2022
//

#include "Scene.h"
#include "Focus.h"
#include "Focusable.h"

void Scene::SetFocusActive(Focus& focus) {
	for (auto& element : m_elements) {
		if (auto focusable = dynamic_cast<Focusable*>(element.get())) {
			if (m_active) {
				focus.AddElement(focusable);
				continue;
			}
			focus.DeleteElement(focusable);
		}
	}
}

Vector2 Scene::GetElementPosition(float x, float y) {
	return {m_pos.x + x * m_size.x, m_pos.y + y * m_size.y };
}
Vector2 Scene::GetElementSize(float x, float y) {
	return {x * m_size.x, y * m_size.y};
}

Scene::Scene(Vector2 pos, Vector2 size, bool active)
	:UIElement(pos, size), m_active(active) { 
	
}

bool Scene::IsActive() const {
	return m_active;
}
void Scene::SetActive(bool active, Focus& focus) {
	if (active == m_active) {
		return;
	}

	m_active = active;
	SetFocusActive(focus);
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
void Scene::Resize(Vector2 resolution) {
	for (auto& element : m_elements) {
		element->Resize(resolution);
	}
}