//
// Purpur Tentakel
// 15.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"
#include <functional>

class DeletePlayerPopUp final : public CellPopUp {
private:
	std::shared_ptr<InputLine<int>> m_inputLine;
	std::function<void(unsigned int)> m_onClick;

	void Initialize(AppContext const& appContext,
		Vector2 resolution) override;
	void SetValue() override;

public:
	DeletePlayerPopUp(Vector2 pos, Vector2 size, Alignment alignemnt,
		Vector2 resolution, std::string const& title, AssetType inpuTexture,
		std::function<void(unsigned int)> onClick);
};
