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
	template<typename type>
	void ValidateMinMax(type& lhs, type& rhs,
		std::string const& lhsMessage, std::string const& rhsMessage) {

		if (lhs < rhs) { return; }

		rhs = lhs + 1;
		auto event = ShowMessagePopUpEvent("Invalid Config",
			lhsMessage + " >= " + rhsMessage + "\nset " + rhsMessage + " to " + std::to_string(rhs)
		);
		eventManager.InvokeEvent(event);
	}
	template<typename type>
	void ValidateLowerThan(type& value, type max,
		std::string const& valueMessage) {

		if (value <= max) { return; }

		value = max;
		auto event = ShowMessagePopUpEvent("Invalid Config",
			valueMessage + " > " + std::to_string(max) +
				"\nset " + valueMessage + " to " + std::to_string(value)
		);
		eventManager.InvokeEvent(event);
	}
	template<typename type>
	void ValidateGreaterThan(type& value, type min,
		std::string const& valueMessage) {

		if (value >= min) { return; }

		value = min;
		auto event = ShowMessagePopUpEvent("Invalid Config",
			valueMessage + " < " + std::to_string(min) +
				"\nset " + valueMessage + " to " + std::to_string(value)
		);
		eventManager.InvokeEvent(event);
	}

private:
	AppContext();
};
