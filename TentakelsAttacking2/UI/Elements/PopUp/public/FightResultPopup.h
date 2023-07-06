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
	HFightResult const m_result; ///< contains the result that will be shown
	int m_index{ 1 }; ///< contains the current index within the result
	bool m_finishedCounting{ false }; ///< contains if the popup has finished all counting calls

	using callback_ty = std::function<void()>; ///< type of the callback function
	callback_ty m_callback { []() {} }; ///< gets called when the popup closes
	
	CountingNumber_ty m_leftNumber; ///< contains the left counting number
	CountingNumber_ty m_rightNumber; ///< contains the right counting number
	
	std::string m_fightText{ "" }; ///< contains the subtitle -> hwo is fighting
	Text_ty m_winText; ///< contains the text who won -> gets set when the fight is finished
	
	ClassicButton_ty m_closeBtn;

	void Initialize();
	void NextNumber(CountingNumber::Type, int, int, double);
	void SetLastStep();
	void SetEnd();

	void HandleButton();

public:
	FightResultPopup(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, HFightResult const result, callback_ty callback);
};