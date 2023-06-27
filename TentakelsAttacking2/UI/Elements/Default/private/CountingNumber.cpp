//
// Purpur Tentakel
// 27.06.2023
//

#include "CountingNumber.h"
#include "AppContext.h"
#include "Text.h"

CountingNumber::CountingNumber(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Alignment textAlignment, float textHeight, int startNumber) 
	: UIElement(pos, size, alignment, resolution), m_currentNumber{ startNumber }, m_targetNumber{ startNumber }
{
	m_text = std::make_shared<Text>(
		pos,
		size,
		alignment,
		resolution,
		textAlignment,
		textHeight,
		std::to_string(startNumber)
	);
}

bool CountingNumber::IsCounting() const {
	return m_isCounting;
}
void CountingNumber::SetCallback(callback_ty callback) {
	m_callback = callback;
}
void CountingNumber::CountTo(Type type, int target, float timeIsS) {
	m_countingType = type;
	m_targetNumber = target;
	m_timeInS = timeIsS;
}
int CountingNumber::GetCurrentNumber() const {
	return m_currentNumber;
}
int CountingNumber::GetTargetNumber() const {
	return m_targetNumber;
}

void CountingNumber::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	// HandleCounting();
	m_text->CheckAndUpdate(mousePosition, appContext);
}
void CountingNumber::Render(AppContext_ty_c appContext) {
	m_text->Render(appContext);
}
void CountingNumber::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	UIElement::Resize(resolution, appContext);
	m_text->Resize(resolution, appContext);
}
