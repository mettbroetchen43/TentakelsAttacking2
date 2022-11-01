//
// Purpur Tentakel
// 01.11.2022
//

#include "Settings.h"

void SettingsScene::Initialize(Vector2 resolution) {
}

SettingsScene::SettingsScene(Vector2 resolution)
	:Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT) {
	Initialize(resolution);
}
