//
// Purpur Tentakel
// 18.06.2023
//

#include "HLaguageManager.h"
#include "AppContext.h"
#include "HPrint.h"

void HLanguageManager::Initialize() {

}

HLanguageManager::HLanguageManager() {
	Initialize();
}

std::string HLanguageManager::Text(std::string key) const {
	if (m_current_language == nullptr) {
		Print("No Current Language loaded", PrintType::ERROR);
		return m_default_text;
	}
	else if (m_current_language.is_null()) {
		Print("current Language is null", PrintType::ERROR);
		return m_default_text;
	}
	else if (not m_current_language.contains(key)) {
		Print("current language does not contain \"" + key + "\"", PrintType::ERROR);
		return m_default_text;
	}
	else {
		return m_current_language[key];
	}
}

std::string HLanguageManager::Text(std::string key, std::vector<std::string> replace) const {
	return std::string();
}

void HLanguageManager::OnEvent(Event const& event) {

}
