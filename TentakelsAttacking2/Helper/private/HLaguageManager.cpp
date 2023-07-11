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
	Print(PrintType::INITIALIZE, "Language");
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
		Print(
			PrintType::ERROR,
			"directory \"{}\" not found -> no language available",
			directory
		);
		return;
	}
	for (auto const& entry : std::filesystem::directory_iterator(directory)) {
		std::filesystem::path file{ entry.path().filename()};
		if (not file.has_extension()) {
			Print(
				PrintType::ERROR,
				"language file \"{}\" has no extension",
				file.string()
			);
			continue;
		}
		if (file.extension() != ".tal") {
			Print(
				PrintType::ERROR,
				"file \"{}\" has wrong datatype",
				file.string()
			);
			continue;
		}
		auto const& fileName{ file.replace_extension()};
		if (contains(fileName.string())) {
			Print(
				PrintType::ERROR,
				"language \"{}\" loaded multiple times",
				fileName.string()
			);
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
			Print(PrintType::INFO, "not able to load new language -> fallback to old language");
			handleUpdateLanguage();
			return;
		}
		if (language != m_default_language) {
			bool const validDefaultLoad{ LoadLanguage(m_default_language) };
			if (validDefaultLoad) {
				Print(
					PrintType::ERROR,
					"fallback to default language: \"{}\"",
					m_default_language
				);
				handleUpdateLanguage();
				return;
			}
			m_current_language.clear();
			appContext.constants.global.currentLanguageName = "";
			Print(PrintType::ERROR, "not able to load any language.");
		}
	}
}
bool HLanguageManager::LoadLanguage(std::string const& language) {
	bool found{ false };
	for (auto const& l : m_availableLanguages) {
		if (l == language) { found = true; break; }
	}
	if (not found) {
		Print(
			PrintType::ERROR,
			"language \"{}\" is not available",
			language
		);
		return false;
	}

	std::string const directory{ "Assets/Languages" };
	if (not DirectoryExists(directory.c_str())) {
		Print(
			PrintType::ERROR,
			"directory \"{}\" not existing. unable to load provided language",
			directory
		);
		return false;
	}


	std::ifstream in;
	in.open(directory + "/" + language + ".tal");
	if (not in.is_open()) {
		Print(
			PrintType::ERROR,
			"not able tp open language: \"{}\"",
			language
		);
		return false;
	}

	try {
		in >> m_current_language;
	}
	catch (nlohmann::json::parse_error const& e) {
		Print(
			PrintType::ERROR,
			"not able tp parse \"{}\" -> message: {} -> byte: {} -> id: {}",
			language,
			e.what(),
			e.byte,
			e.id
		);
		in.close();
		return false;
	}

	in.close();

	AppContext::GetInstance().constants.global.currentLanguageName = language;

	Print(
		PrintType::ERROR,
		"language loaded: \"{}\"",
		language
	);
	return true;
}

std::string HLanguageManager::RawText(std::string const& key) const {
	if (m_current_language == nullptr) {
		Print(PrintType::ERROR, "No Current Language loaded");
		return m_missing_language_text;
	}
	else if (m_current_language.is_null()) {
		Print(PrintType::ERROR, "current Language is null");
		return m_missing_language_text;
	}
	else if (not m_current_language.contains(key)) {
		Print(
			PrintType::ERROR,
			"current language does not contain \"{}\"",
			key
		);
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
	Print(PrintType::INITIALIZE, "LanguageManager");
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
