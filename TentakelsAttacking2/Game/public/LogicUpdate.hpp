//
// Purpur Tentakel
// 07.11.2022
//

#pragma once

/**
 * provides pure virtual functions so that every object that is implementing this
 * can be updated in the same way.
 */
struct LogicUpdate {
	virtual void PreUpdate() = 0;
	virtual void MainUpdate() = 0;
	virtual void PostUpdate() = 0;
};
