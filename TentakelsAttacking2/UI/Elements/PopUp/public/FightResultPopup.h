//
// PurpurTentakel
// 06.07.23
//

#pragma once
#include "PopUp.h"
#include "HFightResult.h"
#include "CountingNumber.h"

class FightResultPopup : public PopUp {
private:
	HFightResult const m_result;
	int m_index{ 1 };
	using callback_ty = std::function<void()>;
	callback_ty m_callback { []() {} };
	CountingNumber_ty m_leftNumber;
	CountingNumber_ty m_rightNumber;
	std::string m_fightText{ "" };
	Text_ty m_winText;
	ClassicButton_ty m_closeBtn;
	bool m_finishedCounting{ false };

	void Initialize();
	void NextNumber(CountingNumber::Type type, int from, int to, double time);
	void SetLastStep();

	void HandleButton();

public:
	FightResultPopup(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, HFightResult const result, callback_ty callback);
	~FightResultPopup();


	void OnEvent(Event const& event) override; 
};