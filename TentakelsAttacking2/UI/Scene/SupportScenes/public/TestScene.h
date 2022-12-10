//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
# include "Scene.h"
# include "Table.h"

class DropDown;

/**
 * no doc here.
 * this contains the test scene that is only unsed to diplay new featurs temporary.
 */
class TestScene : public Scene {
private:
	std::vector<std::string> m_entries = {
		"Eintrag 1",
		"Eintrag 2",
		"Eintrag 3",
		"Eintrag 4",
		"Eintrag 5",
		"Eintrag 6",
		"Eintrag 7",
		"Eintrag 8",
		"Eintrag 9",
		"Eintrag 10",
		"Eintrag 11",
		"Eintrag 12",
		"Eintrag 13",
		"Eintrag 14",
		"Eintrag 15",
		"Eintrag 16",
		"Eintrag 17",
		"Eintrag 18",
		"Eintrag 19",
		"Eintrag 20",
		"Eintrag 21",
		"Eintrag 22",
		"Eintrag 23",
		"Eintrag 24",
		"Eintrag 25",
		"Eintrag 26",
		"Eintrag 27",
		"Eintrag 28",
		"Eintrag 29",
		"Eintrag 30",
		"Eintrag 31",
		"Eintrag 32",
		"Eintrag 33",
		"Eintrag 34",
		"Eintrag 35",
		"Eintrag 36",
		"Eintrag 37",
		"Eintrag 38",
		"Eintrag 39",
	};
	std::shared_ptr<DropDown> m_dropDown;

	void Initialize(Vector2 resolution, AppContext& appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext const& appContext) override;

	void TestLambda(unsigned int value);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
};

