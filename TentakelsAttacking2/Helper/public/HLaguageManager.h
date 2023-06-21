//
// Purpur Tentakel
// 18.06.2023
//

#pragma once
#include "HPrint.h"
#include "EventListener.hpp"
#include <nlohmann/json.hpp>

class HLanguageManager final : public EventListener {
private:
	nlohmann::json m_current_language; ///< contains all text in a specific language
	static inline std::vector<std::string> m_availableLanguages; ///< contains all available languages
	static inline std::string const m_default_text{ "no language loaded" }; ///< contains the default string. this gets returnd when lo language is loaded
	static inline std::string const m_default_language{ "english" }; ///< contains the default language -> gets loaded when the provided language is not able to be loaded

	void InitializeLanguage();
	void InitializeAvailableLanguages();

	void ChanceLanguage(std::string const& language);
	[[nodiscard]] bool LoadLanguage(std::string const& language);

	[[nodiscard]] std::string RawText(std::string const& key) const;

	[[nodiscard]] std::string ReplacePlaceholders(std::string const& text) const;
	template<typename... Args>
	[[nodiscard]] std::string ReplacePlaceholders(std::string_view text, Args const&... args) const;

public:
	HLanguageManager();

	void Initialize();

	[[nodiscard]] std::vector<std::string> GetAvailableLanguages() const;

	[[nodiscard]] std::string Text(std::string const& key) const;
	template<typename... Args>
	[[nodiscard]] std::string Text(std::string const& key, Args const&... args) const;

	void OnEvent(Event const& event) override;
};

template<typename ...Args>
inline std::string HLanguageManager::ReplacePlaceholders(std::string_view text, Args const & ...args) const {
	try {
		return std::vformat(text, std::make_format_args(args...));
	}
	catch (std::format_error const&) {
		std::string t{ text.substr() };
		Print("wrong format. appears mostly when arguments not matching: " + t, PrintType::ERROR);
		assert(false and "wrong format");
		return m_default_text;
	}
	catch (std::bad_alloc const&) {
		std::string t{ text.substr() };
		Print("bad alloc: " + t, PrintType::ERROR);
		assert(false and "bad alloc");
		return m_default_text;
	}
}

template<typename ...Args>
inline std::string HLanguageManager::Text(std::string const& key, Args const & ...args) const {
	std::string text{ RawText(key) };
	return ReplacePlaceholders(text, args...);
}
 