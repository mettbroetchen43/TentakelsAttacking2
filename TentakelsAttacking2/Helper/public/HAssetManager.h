//
// Purpur Tentakel
// 31.08.2022
//

#pragma once

#include "HAssetType.hpp"
#include <raylib.h>
#include <array>
#include <unordered_map>
#include <string>
#include <vector>

/**
 * contains all assets and manage them
 */
class AssetManager final {
private:
	using FileArray = std::array<std::string, 11>; ///< the datatype for the files
	FileArray m_files = { ///< contains all asset file strings
		"Assets/btn_f_default.png",
		"Assets/grey.png",
		"Assets/grey_50.png",
		"Assets/exclamation_mark.png",
		"Assets/question_mark.png",
		"Assets/check.png",
		"Assets/logo.png",
		"Assets/arrow_up",
		"Assets/arrow_right",
		"Assets/arrow_down",
		"Assets/arrow_left",
	};
	std::unordered_map<AssetType, Texture2D> m_assets; ///< contains all assets
	std::vector<std::string> m_title; ///< contains the tile
	Font m_font; ///< contains the font

	/**
	 * loads the title.
	 */
	void LoadTitle();
	/**
	 * loads the font.
	 */
	void LoadFont();
	/**
	 * loads all files.
	 * ity important, that the file strings an the enum in in the same order
	 */
	void LoadFiles();

public:
	/**
	 * loads all needed files.
	 */
	AssetManager();
	/**
	 * unloads all needed files.
	 */
	~AssetManager();

	/**
	 * returns a texture* acordung to the AssetType.
	 */
	[[nodiscard]] Texture* GetTexture(AssetType assetType);
	/**
	 * returns a texture* acordung to the AssetType const.
	 */
	[[nodiscard]] Texture const* GetTexture(AssetType assetType) const;
	/**
	 * returns the title pointer.
	 */
	std::vector<std::string>* GetTitle();
	/**
	 * returns a font*.
	 */
	[[nodiscard]] Font const* GetFont() const;
};
