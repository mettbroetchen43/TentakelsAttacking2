//
// Purpur Tentakel
// 10.09.2022
//

#include "MessagePopUp.h"
#include "AppContext.h"
#include "AssetType.h"
#include "SoundType.h"
#include "memory"

void MessagePopUp::Initialize() {
	AppContext& appContext = AppContext::GetInstance();
	m_btn.SetOnClick(std::bind(&MessagePopUp::Close, *this));
	auto event = NewFocusElementEvent(&m_btn);
	appContext.eventManager.InvokeEvent(event);
}

MessagePopUp::MessagePopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	std::string const& title, std::string const& subTitle, AssetType btnTexture,
	AssetType m_infoTexture)
	: PopUp(pos, size, alignment, resolution, title, subTitle, m_infoTexture),
		m_btn(
			1,
			GetElementPosition(0.65f, 0.7f),
			GetElementSize(0.3f, 0.2f),
			Alignment::BOTTOM_RIGHT,
			resolution,
			"OK",
			AppContext::GetInstance().assetManager.GetTexture(btnTexture),
			SoundType::CLICKED_RELEASE_STD
		) {

	Initialize();
}
	

void MessagePopUp::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	m_btn.CheckAndUpdate(mousePosition, appContext);
}
void MessagePopUp::Render(AppContext const& appContext) {
	PopUp::Render(appContext);

	m_btn.Render(appContext);
}
void MessagePopUp::Resize(Vector2 resolution, AppContext const& appContext) {
	PopUp::Resize(resolution, appContext);
	m_btn.Resize(resolution, appContext);
}
