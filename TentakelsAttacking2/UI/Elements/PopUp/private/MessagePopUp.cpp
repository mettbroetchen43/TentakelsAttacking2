//
// Purpur Tentakel
// 10.09.2022
//

#include "MessagePopUp.h"
#include "AppContext.h"
#include "AssetType.h"
#include "SoundType.h"

void MessagePopUp::Initialize() {
	m_btn.SetOnClick(std::bind(&MessagePopUp::Close, *this));
}

MessagePopUp::MessagePopUp(Vector2 pos, Vector2 size, Vector2 resolution,
	std::string const& title, std::string const& subTitle, Texture2D* btnTexture,
	Texture2D* fullBackground, Texture2D* popUpBackground, Texture2D* m_infoTexture)
	: PopUp(pos, size, resolution, title, subTitle, fullBackground, popUpBackground, m_infoTexture),
	m_btn(1,
		btnTexture,
		GetElementPosition(0.65f, 0.7f),
		GetElementSize(0.3f, 0.2f),
		resolution,
		"OK",
		SoundType::CLICKED_RELEASE_STD) {
	Initialize();
}

void MessagePopUp::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	m_btn.CheckAndUpdate(mousePosition, appContext);
}
void MessagePopUp::Render(AppContext const& appContext) {
	Rectangle textureRec = { 0.0f,0.0f,
		static_cast<float>(m_fullBackground->width), static_cast<float>(m_fullBackground->height) };
	DrawTexturePro(*m_fullBackground, textureRec, m_backgroundColider, { 0.0f, 0.0f }, 0, WHITE);

	textureRec = { 0.0f, 0.0f, static_cast<float>(m_popUpBackground->width),static_cast<float>(m_popUpBackground->height) };
	DrawTexturePro(*m_popUpBackground, textureRec, m_colider, { 0.0f, 0.0f }, 0, WHITE);
	DrawRectangleLines(
		static_cast<int>(m_colider.x),
		static_cast<int>(m_colider.y),
		static_cast<int>(m_colider.width),
		static_cast<int>(m_colider.height), PURPLE);

	textureRec = { 0.0f, 0.0f,
		static_cast<float>(m_infoTexture->width),static_cast<float>(m_infoTexture->height) };
	Rectangle colider = GetColiderWithMaxValues(m_infoTexture, m_colider.width * 0.3f,
		m_colider.height * 0.3f);
	colider.x = m_colider.x + m_colider.width * 0.075f;
	colider.y = m_colider.y + m_colider.height * 0.025f;
	DrawTexturePro(*m_infoTexture, textureRec, colider, { 0.0f, 0.0f }, 0.0f, WHITE);

	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_title.c_str(),
		Vector2(m_colider.x + m_colider.width * 0.3f, m_colider.y + m_colider.height * 0.1f),
		m_colider.height * 0.2f,
		0,
		WHITE);
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_subTitle.c_str(),
		Vector2(m_colider.x + m_colider.width * 0.05f, m_colider.y + m_colider.height * 0.40f),
		m_colider.height * 0.1f,
		0,
		WHITE);

	m_btn.Render(appContext);
}
void MessagePopUp::Resize(Vector2 resolution) {
	PopUp::Resize(resolution);
	m_btn.Resize(resolution);
}
