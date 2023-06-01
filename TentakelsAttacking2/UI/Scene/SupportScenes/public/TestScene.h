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
	std::shared_ptr<Arrow> m_arrow;

	void Initialize(AppContext_ty appContext);
	void Initialize(AppContext& appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext_ty_c appContext) override;

	void TestLambda(unsigned int value);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	void Render(AppContext_ty_c appContext) override;
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
};
