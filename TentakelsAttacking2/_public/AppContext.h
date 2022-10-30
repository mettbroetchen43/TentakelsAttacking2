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
	void ValidateMinMax(type& lhs, type& rhs, std::string const& message) {
		if (lhs >= rhs) {
			rhs = lhs + 1;
			auto event = ShowMessagePopUpEvent("Invalid Config",
				message + std::to_string(rhs)
			);
			eventManager.InvokeEvent(event);
		}
	}

private:
	AppContext();
};
