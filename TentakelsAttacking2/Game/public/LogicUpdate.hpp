//
// Purpur Tentakel
// 07.11.2022
//

#pragma once

struct LogicUpdate {
	virtual void PreUpdate() = 0;
	virtual void MainUpdate() = 0;
	virtual void PostUpdate() = 0;
};
