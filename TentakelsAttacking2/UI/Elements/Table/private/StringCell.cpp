//
// Purpur Tentakel
// 01.10.2022
//

#include "StringCell.h"
#include "AppContext.h"
#include "HTextProcessing.h"
#include "Table.h"

Vector2 StringCell::GetNeededSize() const {
    Vector2 textSize = MeasureTextEx(
        *(AppContext::GetInstance().assetManager.GetFont()),
        m_value.c_str(),
        m_textSize,
        0.0f
    );

    return CalculateNeededSize(textSize);
}

std::string StringCell::GetValue() const {
    return m_value;
}
void StringCell::SetValue(std::string newValue, bool resize) {
    m_value = newValue;

    if (resize) {
        m_table->ResizeCells();
    }
}

void StringCell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
    Cell::CheckAndUpdate(mousePosition, appContext);

    if (ShouldEdit(mousePosition)) {
        auto event = ShowStringCellPopUpEvent(
            "Edit Text",
            m_value,
            [&](std::string value) {SetValue(value);}
        );
        appContext.eventManager.InvokeEvent(event);
    }
}
void StringCell::Render(AppContext const& appContext) {
    std::string printableValue = GetPritablePlaceholderTextInColider(
        m_value,
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
