//
// Purpur Tentakel
// 05.09.2022
//

#include "Scene.h"
#include "Focus.h"
#include "Focusable.h"

void Scene::SetFocusActive(Focus& focus) {
	for (auto& element : m_elements) {
		if (auto focusable = dynamic_cast<Focusable*>(&*element)) {
			if (m_active) {
				focus.AddElement(focusable);
				continue;
			}
			focus.DeleteElement(focusable);
		}
	}
}

Scene::Scene(Vector2 size, Vector2 pos, bool active)
	:UIElement(size, pos), m_active(active) { 
	
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
void Scene::Render() {
	if (!m_active) {
		return;
	}

	for (auto& element : m_elements) {
		element->Render();
	}
}
void Scene::Resize(Vector2 resolution) {
	for (auto& element : m_elements) {
		element->Resize(resolution);
	}
}