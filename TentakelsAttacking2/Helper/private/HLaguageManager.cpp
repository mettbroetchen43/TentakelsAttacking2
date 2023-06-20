//
// Purpur Tentakel
// 18.06.2023
//

#include "HLaguageManager.h"
#include "AppContext.h"
#include "HPrint.h"
#include <filesystem>
#include <iostream>

void HLanguageManager::Initialize() {
	InitializeLanguage();
	InitializeAvailableLanguages();
}
void HLanguageManager::InitializeLanguage() {
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

HLanguageManager::HLanguageManager() {
	Print("LanguageManager", PrintType::INITIALIZE);
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
