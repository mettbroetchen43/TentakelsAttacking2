//
// Purpur Tentakel
// 03.10.2022
//

#pragma once
#include "PopUp.h"
#include "ClassicButton.h"

class CellPopUp : public PopUp {
protected:
	bool m_shouldClose = false;
	bool m_firstEnter = false;

	virtual void Initialize(AppContext const& appContext, Vector2 resolution);
	[[nodiscard]] std::shared_ptr<ClassicButton> InitializeAcceptButton(
		AppContext const& appContext, Vector2 resolution);

	void SetShouldClose();
	virtual void SetValue() = 0;

	void CheckEnter();
	void Close(AppContext const& appContext);
public:
	CellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture);

	virtual void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
};