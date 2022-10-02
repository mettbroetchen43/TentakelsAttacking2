//
// Purpur Tentakel
// 01.10.2022
//

#include "StringCell.h"
#include "AppContext.h"

void StringCell::CheckAndUpdate(Vector2 const& mousePosition,
    [[maybe_unused]] AppContext const& appContext) {
    if (ShouldEdit(mousePosition)) {
        // invoke Event
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
