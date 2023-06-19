//
// Purpur Tentakel
// 18.06.2023
//

#pragma once
#include "EventListener.hpp"
#include <nlohmann/json.hpp>

class HLanguageManager final : public EventListener {
private:
	nlohmann::json m_current_language; ///< contains all text in a specific language
	std::string m_current_language_name{ "english" }; ///< contains the current language name <- gets overwritten by config
	static inline std::vector<std::string> m_availableLanguages; ///< contains all available languages
	static inline std::string const m_default_text{ "no language loaded" }; ///< contains the default string. this gets returnd when lo language is loaded

	void InitializeLanguage();
	void InitializeAvailableLanguages();

	void ChanceLanguage(std::string const& language);
	std::pair<bool, nlohmann::json> LoadLanguage(std::string const& language);

public:
	HLanguageManager();

	void Initialize();

	[[nodiscard]] std::string Text(std::string key) const;
	[[nodiscard]] std::string Text(std::string key, std::vector<std::string> replace) const;

	void OnEvent(Event const& event) override;
};
