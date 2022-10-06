//
// Purpur Tentakel
// 01.10.2022
//

#include "StringCell.h"
#include "AppContext.h"

void StringCell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
    Cell::CheckAndUpdate(mousePosition, appContext);

    if (ShouldEdit(mousePosition)) {
        auto event = ShowStringCellPopUpEvent(
            "Edit Text",
            this
        );
        appContext.eventManager.InvokeEvent(event);
    }
}

void StringCell::Render(AppContext const& appContext) {
    DrawTextEx(
        *(appContext.assetManager.GetFont()),
        value.c_str(),
        m_textPosition,
        m_textSize,
        0.0f,
        WHITE
    );
    Cell::Render(appContext);
}

void StringCell::Resize(Vector2 resolution, AppContext const& appContext) {
    Cell::Resize(resolution, appContext);
}
