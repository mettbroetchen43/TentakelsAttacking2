//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "HSoundManager.h"
#include "EventManager.hpp"
#include "HAssetManager.h"
#include "HPlayerCollection.h"
#include "HColors.h"
#include "UIEvents.hpp"
#include "CConstants.hpp"
#include <string>

struct AppContext {
public:
	SoundManager soundManager;
	AssetManager assetManager;
	EventManager eventManager;
	PlayerCollection playerCollection;
	Colors colors;
	Constants constants;
	

	[[nodiscard]] static AppContext& GetInstance();

	void LoadConfig();
	void SaveConfig();

	void Validate();
	void ValidateSound();
	template<typename type>
	void ValidateMinMax(type& lhs, type& rhs,
		std::string const& lhsMessage, std::string const& rhsMessage) {
		if (lhs >= rhs) {
			rhs = lhs + 1;
			auto event = ShowMessagePopUpEvent("Invalid Config",
				lhsMessage + " >= " + rhsMessage + "\nset " + rhsMessage + " to " + std::to_string(rhs)
			);
			eventManager.InvokeEvent(event);
		}
	}

private:
	AppContext();
};
