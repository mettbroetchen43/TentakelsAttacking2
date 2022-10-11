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

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
	eventManager.AddListener(&playerCollection);
}
