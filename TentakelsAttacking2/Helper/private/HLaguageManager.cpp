//
// Purpur Tentakel
// 18.06.2023
//

#include "HLaguageManager.h"
#include "AppContext.h"
#include "HPrint.h"
#include <filesystem>

void HLanguageManager::InitializeLanguage() {
	ChanceLanguage(AppContext::GetInstance().constants.global.currentLanguageName);
	Print("Language", PrintType::INITIALIZE);
}
void HLanguageManager::InitializeAvailableLanguages() {
	std::string const directory{ "Assets/Languages" };
	m_availableLanguages.clear();
	auto const contains{ [&](std::string name) -> bool {
		for (auto const& f : m_availableLanguages) {
			if (f == name) {
				return true;
			}
		}
		return false;
	} };

	if (not DirectoryExists(directory.c_str())) {
		Print("directory \"" + directory + "\" not found -> no language available", PrintType::ERROR);
		return;
	}
	for (auto const& entry : std::filesystem::directory_iterator(directory)) {
		std::filesystem::path file{ entry.path().filename()};
		if (not file.has_extension()) {
			Print("\"" + file.string() + "\" has no extension", PrintType::ERROR);
			continue;
		}
		if (file.extension() != ".tal") {
			Print("\"" + file.string() + "\" has wrong datatype", PrintType::ERROR);
			continue;
		}
		auto const& fileName{ file.replace_extension()};
		if (contains(fileName.string())) {
			Print("multiple language \"" + fileName.string() + "\"", PrintType::ERROR);
			continue;
		}
		m_availableLanguages.push_back(fileName.string());
	}

}

void HLanguageManager::ChanceLanguage(std::string const& language) {
	AppContext_ty appContext{ AppContext::GetInstance() };
	auto handleUpdateLanguage{ [&]() {
		auto const event{ UpdateLanguageInUIEvent(appContext.constants.global.currentLanguageName) };
		appContext.eventManager.InvokeEvent(event);
	} };

	bool const validLoad{ LoadLanguage(language) };

	if (not validLoad) {
		if (not m_current_language.empty()) {
			Print("not able to load new language -> fallback to old language", PrintType::INFO);
			handleUpdateLanguage();
			return;
		}
		if (language != m_default_language) {
			bool const validDefaultLoad{ LoadLanguage(m_default_language) };
			if (validDefaultLoad) {
				Print("fallback to default language: \"" + m_default_language + "\"", PrintType::INFO);
				handleUpdateLanguage();
				return;
			}
			m_current_language.clear();
			appContext.constants.global.currentLanguageName = "";
			Print("not able to load any language.", PrintType::ERROR);
		}
	}
}
bool HLanguageManager::LoadLanguage(std::string const& language) {
	bool found{ false };
	for (auto const& l : m_availableLanguages) {
		if (l == language) { found = true; break; }
	}
	if (not found) {
		Print("language \"" + language + "\" is not available", PrintType::ERROR);
		return false;
	}

	std::string const directory{ "Assets/Languages" };
	if (not DirectoryExists(directory.c_str())) {
		Print("directory \"" + directory + "\" not existing. unable to load provided language", PrintType::ERROR);
		return false;
	}


	std::ifstream in;
	in.open(directory + "/" + language + ".tal");
	if (not in.is_open()) {
		Print("not able to open language. \"" + language + "\"", PrintType::ERROR);
		return false;
	}

	try {
		in >> m_current_language;
	}
	catch (nlohmann::json::parse_error const& e) {
		std::stringstream ss;
		ss << "not able to parse \"" << language << "\" | Message:" << e.what() << " | byte: " << e.byte << " | ID: " << e.id;
		Print(ss.str(), PrintType::ERROR);
		in.close();
		return false;
	}

	in.close();

	AppContext::GetInstance().constants.global.currentLanguageName = language;

	Print("language loaded: \"" + language + "\"", PrintType::INFO);
	return true;
}

std::string HLanguageManager::RawText(std::string const& key) const {
	if (m_current_language == nullptr) {
		Print("No Current Language loaded", PrintType::ERROR);
		return m_missing_language_text;
	}
	else if (m_current_language.is_null()) {
		Print("current Language is null", PrintType::ERROR);
		return m_missing_language_text;
	}
	else if (not m_current_language.contains(key)) {
		Print("current language does not contain \"" + key + "\"", PrintType::ERROR);
		return m_default_text;
	}
	else {
		return m_current_language[key];
	}
}
std::string HLanguageManager::ReplacePlaceholders(std::string const& text) const {
	return text;
}

HLanguageManager::HLanguageManager() {
	Print("LanguageManager", PrintType::INITIALIZE);
}
void HLanguageManager::Initialize() {
	InitializeAvailableLanguages();
	InitializeLanguage();
}

std::vector<std::string> HLanguageManager::GetAvailableLanguages() const {
	return m_availableLanguages;
}
std::string HLanguageManager::Text(std::string const& key) const {
	return RawText(key);
}

void HLanguageManager::OnEvent(Event const& event) {
	if (auto const* ChaneEvent = dynamic_cast<ChangeLanguageEvent const*>(&event)) {
		ChanceLanguage(ChaneEvent->GetLanguage());
	}
}
