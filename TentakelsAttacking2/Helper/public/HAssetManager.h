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

class AssetManager final {
private:
	using FileArray = std::array<std::string, 7>;
	FileArray m_files = {
		"Assets/btn_f_default.png",
		"Assets/grey.png",
		"Assets/grey_50.png",
		"Assets/exclamation_mark.png",
		"Assets/question_mark.png",
		"Assets/check.png",
		"Assets/logo.png",
	};
	std::unordered_map<AssetType, Texture2D> m_assets;
	std::vector<std::string> m_title;
	Font m_font;

	void LoadTitle();
	void LoadFont();
	void LoadFiles();

public:
	AssetManager();
	~AssetManager();

	[[nodiscard]] Texture* GetTexture(AssetType assetType);
	std::vector<std::string>* GetTitle();
	[[nodiscard]] Font const* GetFont() const;
};
