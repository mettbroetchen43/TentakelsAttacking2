//
// Purpur Tentakel
// 04.11.2022
//

#include "Credits.h"

void CreditsScene::Initialize(Vector2 resolution) {

}

CreditsScene::CreditsScene(Vector2 resolution)
	:Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT), m_resolution(resolution) {
	Initialize(resolution);
}
