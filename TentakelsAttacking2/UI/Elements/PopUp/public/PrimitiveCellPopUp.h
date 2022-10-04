//
// Purpur Tentakel
// 03.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "ClassicButton.h"

class PrimitiveCellPopUp : public CellPopUp {
public:
	bool m_shouldClose = false;
	bool m_firstEnter = false;
	ClassicButton m_acceptBTN, m_cancelBTN;

	virtual void Initialize(AppContext const& appContext);

	void SetShouldClose();
	virtual void SetValue() = 0;

	virtual void CheckEnter() = 0;
	void Close(AppContext const& appContext);

public:
	PrimitiveCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string const& subTitle,
		AssetType infoTexture);

	virtual void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	virtual void Render(AppContext const& appContext) override;
	virtual void Resize(Vector2 resolution, AppContext const& appContext) override;
};

