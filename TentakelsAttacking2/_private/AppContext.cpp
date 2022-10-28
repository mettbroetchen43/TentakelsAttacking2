//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.h"
#include "ConfigIO.h"

AppContext& AppContext::GetInstance() {
	static AppContext appContext;
	return appContext;
}

void AppContext::LoadConfig() {
	::LoadConfig();
}
void AppContext::SaveConfig() {
	::SaveConfig();
}

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
	eventManager.AddListener(&playerCollection);
}
