//
// Purpur Tentakel
// 31.08.2022
//

#include "HAssetManager.h"
#include <iostream>
#include <fstream>


void AssetManager::LoadTitle() {
	std::fstream newFile;
	m_title.clear();
	std::string line;

	newFile.open("Assets/title.txt", std::ios::in);
	if (newFile.is_open()) {
		while (getline(newFile, line)) {
			m_title.push_back(line);
		}
		newFile.close();
	}
}
void AssetManager::LoadFont() {
	m_font = LoadFontEx("Assets/default_font.ttf", 128, 0, 250);
}

void AssetManager::LoadFiles() {
	for (int i = 0; i < m_files.size(); ++i) {
		char const* test = (m_files.at(i)).c_str();
		Texture2D texture = LoadTexture(test);
		m_assets[static_cast<AssetType>(i)] = texture;
	}
}

AssetManager::AssetManager() {
	LoadFiles();
	LoadTitle();
	LoadFont();
}
AssetManager::~AssetManager() {
	for (auto [type, asset] : m_assets) {
		UnloadTexture(asset);
	}
	UnloadFont(m_font);
}

Texture* AssetManager::GetTexture(AssetType assetType) {
	return &m_assets.at(assetType);
}
Texture const* AssetManager::GetTexture(AssetType assetType) const {
	return &m_assets.at(assetType);
}
std::vector<std::string>* AssetManager::GetTitle() {
	return &m_title;
}
Font const* AssetManager::GetFont() const {
	return &m_font;
}
