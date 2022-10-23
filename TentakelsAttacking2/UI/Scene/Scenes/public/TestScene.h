//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
# include "Scene.h"
# include "Table.h"

class TestScene : public Scene {
private:
	void Initialize(Vector2 resolution, AppContext& appContext);

	void Checked(unsigned int ID, bool isChecked);

protected:

public:
	TestScene(Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution);
	void SetActive(bool active, AppContext const& appContext) override;

};
