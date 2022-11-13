//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
# include "Scene.h"
# include "Table.h"

class TestScene : public Scene {
private:
	Rectangle m_coldier;
	Vector2 m_resolution;

	void Initialize(Vector2 resolution, AppContext& appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext const& appContext) override;

	void TestLambda(float value);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
};

