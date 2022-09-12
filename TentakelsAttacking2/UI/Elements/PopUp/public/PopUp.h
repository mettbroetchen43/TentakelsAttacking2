//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include "UIElement.h"


class PopUp : public UIElement {
protected:
	std::string m_title, m_subTitle;
	Texture2D *m_fullBackground, *m_popUpBackground, *m_infoTexture;
	Rectangle m_backgroundColider, m_colider;

	void Close();
	virtual void Initialize() = 0;

	Vector2 GetElementPosition(float x, float y);
	Vector2 GetElementSize(float x, float y);

	Rectangle GetColiderWithMaxValues(Texture2D* texture, float maxWidth, float maxHeight) const;

public:
	PopUp(Vector2 pos, Vector2 size, Vector2 resolution, 
		std::string const& title, std::string const& subTitle,
		Texture2D *fullBackground, Texture2D *popUpBackground, Texture2D *m_infoTexture);
	PopUp(PopUp const&) = default;
	PopUp(PopUp&&) = default;
	PopUp& operator= (PopUp const&) = default;
	PopUp& operator= (PopUp&&) = default;

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) = 0;
	virtual void Render(AppContext const& appContext) = 0;
	void Resize(Vector2 resolution);
};
