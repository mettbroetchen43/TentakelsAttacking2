//
// Purpur Tentakel
// 27.06.2023
//

#include "CountingNumber.h"
#include "AppContext.h"
#include "Text.h"

void CountingNumber::HandleCounting() {
	if (m_currentNumber != m_targetNumber and not m_isCounting) {
		m_isCounting = true;
		m_startCountingTime = GetTime();
		m_text->SetColor(m_countingColor);
	}
	if (not m_isCounting) { return; }

	switch (m_countingType) {
		default:
		case LINEAR:
			HandleLinearCounting();
			break;
		case ASYMPTOTIC:
			HandleAsymptoticCounting();
			break;
	}

	if ((m_targetNumber - m_startNumber) >= 0) {
		if (m_targetNumber < m_currentNumber) { m_currentNumber = m_targetNumber; }
	}
	else {
		if (m_targetNumber > m_currentNumber) { m_currentNumber = m_targetNumber; }
	}

	if (m_currentNumber == m_targetNumber and m_isCounting) {
		m_isCounting = false;
		m_callback(m_countingType, m_startNumber, m_currentNumber, m_timeInS);
		m_text->SetColor(m_defaultColor);
	}
}
void CountingNumber::HandleLinearCounting() {
	double const percent{ (GetTime() - m_startCountingTime) / m_timeInS };
	int nextNumber = { m_startNumber + static_cast<int>((m_targetNumber - m_startNumber) * percent) };

	SetNewNumber(nextNumber);
}
void CountingNumber::HandleAsymptoticCounting() {
	double const percent{ std::sqrt((GetTime() - m_startCountingTime) / m_timeInS) };
	int nextNumber = { m_startNumber + static_cast<int>((m_targetNumber - m_startNumber) * percent) };

	SetNewNumber(nextNumber);
}
void CountingNumber::SetNewNumber(int number) {
	m_currentNumber = number;
	m_text->SetText(std::to_string(m_currentNumber));
}

CountingNumber::CountingNumber(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Alignment textAlignment, float textHeight, int startNumber) 
	: UIElement(pos, size, alignment, resolution),
	m_startNumber{ startNumber }, m_currentNumber { startNumber }, m_targetNumber{ startNumber }
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

void CountingNumber::SetCountingColor(Color color) {
	m_countingColor = color;
}
void CountingNumber::SetDefaultColor(Color color) {
	m_defaultColor = color;
}

bool CountingNumber::IsCounting() const {
	return m_isCounting;
}
void CountingNumber::SetCallback(callback_ty callback) {
	m_callback = callback;
}
void CountingNumber::CountTo(Type type, int target, double timeIsS) {
	if (target == m_currentNumber) { return; }
	m_countingType = type;
	m_targetNumber = target;
	m_timeInS = timeIsS;
	m_startNumber = m_currentNumber;
}
int CountingNumber::GetCurrentNumber() const {
	return m_currentNumber;
}
int CountingNumber::GetTargetNumber() const {
	return m_targetNumber;
}

void CountingNumber::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	HandleCounting();
	m_text->CheckAndUpdate(mousePosition, appContext);
}
void CountingNumber::Render(AppContext_ty_c appContext) {
	m_text->Render(appContext);
}
void CountingNumber::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	UIElement::Resize(resolution, appContext);
	m_text->Resize(resolution, appContext);
}
