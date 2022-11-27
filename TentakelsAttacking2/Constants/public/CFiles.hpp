//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <string>

/**
 * contains the file constants.
 */
struct CFiles final {
private:
	static inline const std::string m_configFile = "config.tac"; ///< config file name
public:
	static inline const std::string savesDir = "saves"; ///< saves dir name

	/**
	 * return the complete path of the colfig file.
	 */
	[[nodiscard]] inline std::string configFile() const {
		return savesDir + "/" + m_configFile;
	}
};
