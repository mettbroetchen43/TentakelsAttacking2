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

class PopUpManager final : public EventListener {
private:
	std::vector<std::unique_ptr<PopUp>> m_popUps;
	std::vector<PopUp*> m_toDelete;
	AppContext* m_appContext;
	Vector2 m_resolution;

public:
	PopUpManager(Vector2 resolution);
	~PopUpManager() = default;

	[[nodiscard]] bool IsActivePopUp() const;

	void OnEvent(Event const& event) override;

	void NewMessagePopUp(ShowMessagePopUpEvent const* event);
	void NewDeletePlayerPopUp(ShowDeletePlayerPopUpEvent const* event);
	void NewValidatePopUp(ShowValidatePopUp const* event);
	void NewColorCellPopUp(ShowCellPopUpEvent<Color> const* event);
	void NewInitialSoundLevelPopUp(ShowInitialSoundLevelPopUpEvent const* event);
	template<typename T, typename eventType>
	void NewTableCellPopUp(eventType const* event) {
		auto focusEvent = NewFocusPopUpLayerEvent();
		m_appContext->eventManager.InvokeEvent(focusEvent);

		m_popUps.push_back(std::make_unique<PrivitiveCellPopUp<T>>(
			Vector2(0.5f, 0.5f),
			Vector2(0.7f, 0.7f),
			Alignment::MID_MID,
			m_resolution,
			event->GetTitle(),
			AssetType::LOGO,
			event->GetCurrentValue(),
			event->GetOnClick()
			)
		);
	}

	void DeleteLastPopUp(PopUp* toDelete);
	void CheckForDeleteRemainingPopUps();

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext);
};