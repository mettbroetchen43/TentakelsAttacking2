//
// Purpur Tentakel
// 15.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"

class DeletePlayerPopUp : public CellPopUp {
private:
	std::shared_ptr<InputLine<int>> m_inputLine;

	void Initialize(AppContext const& appContext,
		Vector2 resolution) override;
	void SetValue() override;

public:
	using CellPopUp::CellPopUp;
};
