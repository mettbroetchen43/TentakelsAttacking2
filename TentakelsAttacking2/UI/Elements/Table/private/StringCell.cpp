//
// Purpur Tentakel
// 01.10.2022
//

#include "StringCell.h"
#include "AppContext.h"
#include "HTextProcessing.h"

Vector2 const& StringCell::GetNeededSize() const {
    Vector2 neededSize = MeasureTextEx(
        *(AppContext::GetInstance().assetManager.GetFont()),
        value.c_str(),
        m_textSize,
        0.0f
    );

    return {
        (m_colider.x / neededSize.x) * m_size.x,
        (m_colider.y / neededSize.y) * m_size.y
    };
}

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
    std::string printableValue = GetPritablePlaceholderTextInColider(
        value,
        m_textSize,
        m_colider,
        appContext
    );
    DrawTextEx(
        *(appContext.assetManager.GetFont()),
        printableValue.c_str(),
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
