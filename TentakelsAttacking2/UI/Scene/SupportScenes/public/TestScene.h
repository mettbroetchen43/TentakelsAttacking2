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
	std::shared_ptr<DropDown> m_dropDown;

	void Initialize(Vector2 resolution, AppContext& appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext const& appContext) override;

	void TestLambda(float value);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
};

