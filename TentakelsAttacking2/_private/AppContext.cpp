//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.h"

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
}

AppContext& AppContext::GetInstance() {
	static AppContext appContext;
	return appContext;
}
