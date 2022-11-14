//
// Purpur Tentakel
// 14.11.2022
//

#include "InitialSoundLevelPopUp.h"

void InitialSoundLevelPopUp::Initialize(Vector2 resolution) {}

InitialSoundLevelPopUp::InitialSoundLevelPopUp(Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution, std::string const& title,
	std::string& subTitle)
	:PopUp(pos, size, alignment, resolution, title, subTitle, AssetType::QUESTION_MARK) {

	Initialize(resolution);
}
