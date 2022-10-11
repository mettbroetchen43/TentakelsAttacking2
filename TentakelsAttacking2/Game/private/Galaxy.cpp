//
// PurpurTentakel
// 10.08.22
//

#include "Galaxy.h"

Galaxy::Galaxy(double x, double y, size_t planetCount, std::vector<std::shared_ptr<Player>> const& initialPlayer)
	: m_dimensions(x, y), m_planetCount(planetCount) {
	GeneratePlanets(initialPlayer);
	}

void Galaxy::GeneratePlanets(std::vector<std::shared_ptr<Player>> const& initialPlayer) {
	
}

Galaxy::Galaxy()
	: m_dimensions({ 0.0f,0.0f }) { }

void Galaxy::PreUpdate() {
	for (auto& spaceObjectWeak : m_spaceObjects) {
		spaceObjectWeak.lock()->PreUpdate(*this);
	}
}

void Galaxy::Update() {
	for (auto& spaceObjectWeak : m_spaceObjects) {
		spaceObjectWeak.lock()->Update(*this);
	}
}

void Galaxy::PostUpdate() {
	for (auto& spaceObjectWeak : m_spaceObjects) {
		spaceObjectWeak.lock()->PostUpdate(*this);
	}
	std::cout << "TODO delete unvalid group pointer" << '\n';
}
