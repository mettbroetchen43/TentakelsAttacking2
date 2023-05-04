//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
# include "Scene.h"
# include "Table.h"

enum class TableToggle;

/**
 * no doc here.
 * this contains the test scene that is only unsed to diplay new featurs temporary.
 */
class TestScene : public Scene {
private:
	std::shared_ptr<Table> m_table;
	void Initialize(AppContext& appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext const& appContext) override;

	void TestLambda(unsigned int value);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;

	void ToggleTable(TableToggle headline);
};

