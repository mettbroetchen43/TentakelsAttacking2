//
// Purpur Tentakel
// 05.09.2022
//


#pragma once
#include "UIEvents.hpp"
#include "AllPopUp.hpp"
#include "EventListener.hpp"
#include <memory>
#include <string>
#include <vector>

class PopUpManager :public EventListener {
private:
	std::vector<std::unique_ptr<PopUp>> m_popUps;
	AppContext* m_appContext;
	Vector2 m_resolution;

public:
	PopUpManager(Vector2 resolution);
	~PopUpManager() = default;

	[[nodiscard]] bool IsActivePopUp() const;

	void OnEvent(Event const& event) override;

	void NewMessagePopUp(ShowMessagePopUpEvent const* event);
	template<typename popUpType, typename eventType>
	void NewTableCellPopUp(eventType const* event) {
		auto focusEvent = NewFocusLayerEvent();
		m_appContext->eventManager.InvokeEvent(focusEvent);

		m_popUps.push_back(std::make_unique<popUpType>(
			Vector2(0.5f, 0.5f),
			Vector2(0.7f, 0.7f),
			Alignment::MID_MID,
			m_resolution,
			event->GetTitle(),
			AssetType::LOGO,
			event->GetCell()
			)
		);
	}

	void DeleteLastPopUp();

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext);
};