//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
# include "Scene.h"
# include "Hover.h"
# include "Table.h"

/**
 * no doc here.
 * this contains the test scene that is only unused to display new features temporary.
 */
class TestScene : public Scene {
private:
	std::shared_ptr<Hover> m_hover;
	Rectangle m_toRender{ 255.0,100.0,500.0,300.0 };
	bool m_isHover{ false };

	void Initialize(AppContext& appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext const& appContext) override;

	void TestLambda(unsigned int value);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;

	void RenderRectangle(AppContext const& appContext);
	void CheckHover(Vector2 const& mousePosition, AppContext const& appContext);
};
