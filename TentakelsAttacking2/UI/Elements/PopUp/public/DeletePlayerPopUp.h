//
// Purpur Tentakel
// 15.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"
#include <functional>

/**
 * provides a popup to choose witch player should be deleted.
 */
class DeletePlayerPopUp final : public CellPopUp {
private:
	std::shared_ptr<InputLine<int>> m_inputLine; ///< contains an inputline for user input
	std::function<void(unsigned int)> m_onClick; ///< contauns a lambda that gets called when the player cets deleted

	/**
	 * initialises all ui elements.
	 */
	void Initialize(AppContext const& appContext,
		Vector2 resolution) override;
	/**
	 * gets the id from the inputline and calles onClick.
	 * sets should close afterwords.
	 */
	void SetValue() override;

public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	DeletePlayerPopUp(Vector2 pos, Vector2 size, Alignment alignemnt,
		Vector2 resolution, std::string const& title, AssetType inpuTexture,
		std::function<void(unsigned int)> onClick);
};
