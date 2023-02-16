//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
# include "Scene.h"
# include "Table.h"
# include "Galaxy.h"

/**
 * no doc here.
 * this contains the test scene that is only unsed to diplay new featurs temporary.
 */
class TestScene : public Scene , public EventListener {
private:
	std::shared_ptr<Galaxy> m_galaxy;
	void Initialize(AppContext& appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext const& appContext) override;

	void TestLambda(unsigned int value);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;

	void OnEvent(Event const& event) override;
};

