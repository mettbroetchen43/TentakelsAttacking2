//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.h"

AppContext& AppContext::GetInstance() {
	static AppContext appContext;
	return appContext;
}

std::string const& AppContext::Version() const {
	return m_version;
}
std::string const& AppContext::CopyRight() const {
	return m_copyRight;
}

bool AppContext::IsMaximizedStartingWindow() const {
	return m_starting_maximized_window;
}

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
	eventManager.AddListener(&playerCollection);
}
