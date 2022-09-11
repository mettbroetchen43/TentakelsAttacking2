//
// Purpur Tentakel
// 31.08.2022
//

#pragma once

#include "AssetType.h"
#include <raylib.h>
#include <array>
#include <unordered_map>
#include <string>

class AssetManager {
private:
	std::array<std::string, 5> m_files = {
		"Assets/btn_f_default.png",
		"Assets/grey.png",
		"Assets/grey_50.png",
		"Assets/exclamation_mark.png",
		"Assets/question_mark.png",
	};
	std::unordered_map<AssetType, Texture2D> m_assets;
public:
	AssetManager();
	~AssetManager();

	[[nodiscard]] Texture* GetTexture(AssetType assetType);
};
