//
// Purpur Tentakel
// 12.09.2022
//

#include "Intro.h"
#include "AppContext.h"
#include "UIManager.h"
#include "ClassicButton.h"
#include "AssetType.h"
#include "SoundType.h"
#include "Events.h"

#define THERTY_FIFE 35.0f
#define BTN_SPEED 2.5f

void Intro::RenderTitle(AppContext const& appContext) {
	for (int i = 0;i < m_title->size();++i) {
		DrawTextEx(
			*(appContext.assetManager.GetFont()),
			m_title->at(i).c_str(),
			Vector2(m_textPosition.x, m_textPosition.y +  m_fontSize * i),
			m_fontSize,
			0.0f,
			WHITE);
	}
}
void Intro::RenderTitleSequens(AppContext const& appContext) {
	size_t localCharCount = 0;
	std::string dummyText;
	for (int i = 0;i < m_title->size();++i) {
		dummyText = m_title->at(i);
		if (localCharCount + dummyText.size() > m_charCount) {
			dummyText = dummyText.substr(0, m_charCount - localCharCount);
		}

		DrawTextEx(
			*(appContext.assetManager.GetFont()),
			dummyText.c_str(),
			Vector2(m_textPosition.x, m_textPosition.y + m_fontSize * i),
			m_fontSize,
			0.0f,
			WHITE);
		localCharCount += dummyText.size();
		if (localCharCount >= m_charCount) {
			break;
		}
	}
	if (dummyText.size() > 0) {
		if (dummyText.at(dummyText.size() - 1) != ' ') {
			auto event = PlayTextSoundEvent();
			appContext.eventManager.InvokeEvent(event);
		}
	}

	++m_charCount;
	if (m_charCount >= m_maxCharCount) {
		TitleFinish(appContext);
	}
}
void Intro::MeasureTitleLength() {
	m_maxCharCount = 0;
	for (auto const& s : *m_title) {
		m_maxCharCount += s.size();
	}
}
void Intro::ResizeText(AppContext const& appContext, Vector2 resolution) {
	m_fontSize = resolution.y / THERTY_FIFE;
	Vector2 textSize = MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		m_title->at(0).c_str(),
		m_fontSize,
		0.0f
	);
	m_textPosition.x = (resolution.x - textSize.x) / 2;
	m_textPosition.y = m_fontSize * 2;
	m_maxBtnPosition = static_cast<size_t>(resolution.y * 0.4f);
}

void Intro::TitleFinish(AppContext const& appContext) {
	m_btn->SetEnabled(true);
	m_titleFinish = true;
	auto event = PlaySoundEvent(SoundType::ACCEPTED); // TODO
	appContext.eventManager.InvokeEvent(event);
}
void Intro::MoveBtn() {
	auto colider = m_btn->GetCollider();
	if (colider.y - BTN_SPEED < m_maxBtnPosition) {
		BtnMoveFinish();
		return;
	}
	colider.y -= BTN_SPEED;
	m_btn->SetCollider(colider);
}
void Intro::BtnMoveFinish(){
	auto colider = m_btn->GetCollider();
	colider.y = static_cast<float>(m_maxBtnPosition);
	m_btn->SetCollider(colider);
	m_btnMovmendFinish = true;
	AppContext& appContext = AppContext::GetInstance();
	auto event = PlaySoundEvent(SoundType::ACCEPTED); // TODO
	appContext.eventManager.InvokeEvent(event);
}

Intro::Intro(Vector2 pos, Vector2 size, UIManager const& uiManager)
	:Scene(pos, size) {
	AppContext& appContext = AppContext::GetInstance();
	m_title = appContext.assetManager.GetTitle();

	ResizeText(appContext, uiManager.GetResolution());

	m_btn = std::make_shared<ClassicButton>(
		1,
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		GetElementPosition(0.35f, 1.1f),
		GetElementSize(0.3f, 0.2f),
		uiManager.GetResolution(),
		"Start Game",
		SoundType::ACCEPTED
		);
	m_btn->SetEnabled(false);
	auto event = SelectFocusElementEvent(m_btn.get());
	appContext.eventManager.InvokeEvent(event);

	MeasureTitleLength();
}

void Intro::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	bool skipTile = 
		IsKeyPressed(KEY_ESCAPE)
		and !m_titleFinish;
	if (skipTile) {
		TitleFinish(appContext);
		return;
	}

	bool skipBtn =
		IsKeyPressed(KEY_ESCAPE)
		and m_titleFinish
		and !m_btnMovmendFinish;
	if (skipBtn) {
		BtnMoveFinish();
		return;
	}

	if (m_titleFinish and !m_btnMovmendFinish) {
		MoveBtn();
	}
	m_btn->CheckAndUpdate(mousePosition, appContext);
}
void Intro::Render(AppContext const& appContext) {
	if (!m_titleFinish) {
		RenderTitleSequens(appContext);
	}
	else {
		RenderTitle(appContext);
	}

	m_btn->Render(appContext);
}
void Intro::Resize(Vector2 resolution) {
	m_btn->Resize(resolution);
	ResizeText(AppContext::GetInstance(), resolution);
}

void Intro::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}
