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
	std::array<std::string, 2> m_files = {
		"Assets/btn_f_default.png",
		"Assets/grey.png"
	};
	std::unordered_map<AssetType, Texture2D> m_assets;
public:
	AssetManager();
	~AssetManager();

	[[nodiscard]] Texture* GetTexture(AssetType assetType);
};