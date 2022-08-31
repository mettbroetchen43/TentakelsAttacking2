//
// Purpur Tentakel
// 31.08.2022
//

#include "AssetManager.h"
#include <iostream>

AssetManager::AssetManager() {
	InitWindow(100, 100, "Title TODO");
	for (int i = 0; i < m_files.size(); ++i) {
		char const* test = (m_files.at(i)).c_str();
		Texture2D texture = LoadTexture(test);
		m_assets[static_cast<AssetType>(i)] = texture;
	}
}
AssetManager::~AssetManager() {
	for (auto [type, asset] : m_assets) {
		UnloadTexture(asset);
	}
}

Texture* AssetManager::GetTexture(AssetType assetType) {
	return &m_assets.at(assetType);
}
