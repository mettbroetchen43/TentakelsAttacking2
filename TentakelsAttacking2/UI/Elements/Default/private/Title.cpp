//
// Purpur Tentakel
// 19.09.2022
// 

#include "Title.h"
#include "AppContext.h"
#include "HRandom.h"

void Title::RenderTitle(AppContext const& appContext) {
	for (int i = 0;i < m_title->size();++i) {
		DrawTextEx(
			*(appContext.assetManager.GetFont()),
			m_title->at(i).c_str(),
			Vector2(m_textPosition.x, m_textPosition.y + m_fontSize * i),
			m_fontSize,
			0.0f,
			WHITE);
	}
}
void Title::RenderTitleSequens(AppContext const& appContext) {
	size_t localCharCount = 0;
	std::string dummyText;
	int i = 0;
	for (;i < m_title->size();++i) {
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

	Random& random = Random::GetInstance();
	float prefixPosition = m_textPosition.x +
		(dummyText.size() *
			MeasureTextEx(
				*(appContext.assetManager.GetFont()),
				"a",
				m_fontSize,
				0.0f).x);

	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_postFixes.at(random.random(m_postFixes.size())).c_str(),
		Vector2(prefixPosition, m_textPosition.y + m_fontSize * i),
		m_fontSize,
		0.0f,
		WHITE);

	if (dummyText.size() > 0) {
		if (dummyText.at(dummyText.size() - 1) != ' ') {
			auto event = PlaySoundEvent(SoundType::TEXT);
			appContext.eventManager.InvokeEvent(event);
		}
	}

	++m_charCount;
	if (m_charCount >= m_maxCharCount) {
		TitleFinish(appContext);
	}
}
void Title::MeasureTitleLength() {
	m_maxCharCount = 0;
	for (auto const& s : *m_title) {
		m_maxCharCount += s.size();
	}
}
void Title::SetColider(AppContext const& appContext, Vector2 const& resolution) {
	m_fontSize = resolution.y * m_size.y / m_title->size();

	std::string title = "";
	for (auto const& line : *m_title) {
		title += line + '\n';
	}
	title.pop_back();

	Vector2 textSize = MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		title.c_str(),
		m_fontSize,
		0.0f
	);
	float size = textSize.x / resolution.x;

	while (m_size.x < size) {
		--m_fontSize;
		textSize = MeasureTextEx(
			*(appContext.assetManager.GetFont()),
			title.c_str(),
			m_fontSize,
			0.0f
		);
		size = textSize.x / resolution.x;
	}

	m_size.x = size;
}
void Title::ResizeText(AppContext const& appContext, Vector2 resolution) {
	SetColider(appContext, resolution);
	m_textPosition = {
		m_pos.x * resolution.x,
		m_pos.y * resolution.y,
		m_size.x * resolution.x,
		m_size.y * resolution.y
	};
}

void Title::TitleFinish(AppContext const& appContext) {
	m_titleFinish = true;
	auto event = PlaySoundEvent(SoundType::ACCEPTED);
	appContext.eventManager.InvokeEvent(event);
}

Title::Title(Vector2 pos, Vector2 size, Alignment alignment, bool drawTitle,
	Vector2 resolution, AppContext& appContext)
	: UIElement(pos, size, alignment), m_titleFinish(!drawTitle) {

	m_title = appContext.assetManager.GetTitle();
	MeasureTitleLength();
	SetColider(appContext, resolution);

	m_textPosition = GetAlignedCollider(m_pos, m_size, alignment, resolution);

}

void Title::CheckAndUpdate([[maybe_unused]] Vector2 const& mousePosition, AppContext const& appContext) {
	bool skipTitle =
		IsKeyPressed(KEY_ESCAPE)
		and !m_titleFinish;
	if (skipTitle) {
		TitleFinish(appContext);
		return;
	}
}
void Title::Render(AppContext const& appContext) {
	// Update here to make shure the value ist correct
	m_lastFinishedTitle = m_titleFinish;

	if (!m_titleFinish) {
		RenderTitleSequens(appContext);
	}
	else {
		RenderTitle(appContext);
	}
}
void Title::Resize(Vector2 resolution, [[maybe_unused]] AppContext const& appContext) {
	ResizeText(AppContext::GetInstance(), resolution);
}

bool Title::HasFinishedTitle() const {
	return m_titleFinish;
}
bool Title::IsTitleFinished() const {
	return m_lastFinishedTitle != m_titleFinish;
}