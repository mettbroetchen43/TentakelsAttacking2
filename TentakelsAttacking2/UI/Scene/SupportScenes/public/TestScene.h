//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
# include "Scene.h"

/**
 * no doc here.
 * this contains the test scene that is only unused to display new features temporary.
 */
class TestScene : public Scene {
private:
	void Initialize(AppContext& appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext const& appContext) override;

	void TestLambda(unsigned int value);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
};
