//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
#include "Scene.h"
#include "HUIAlias.hpp"
#include "CountingNumber.h"
#include "HRandom.h"
#include <array>

/**
 * no doc here.
 * this contains the test scene that is only unused to display new features temporary.
 */
class TestScene : public Scene {
private:
	CountingNumber_ty m_first;
	CountingNumber_ty m_second;

	Random& m_random{ Random::GetInstance() };
	std::array<float, 7> m_times{1.0f, 2.5f, 5.0f, 8.3f, 7.9f, 10.0f, 0.5f};
	std::array<int, 7> m_numbers{-1000, -265, -35, 0, 10, 345, 1065};

	void Initialize(AppContext_ty appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext_ty_c appContext) override;

	void TestLambda(CountingNumber::Type type, int current, float time);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	void Render(AppContext_ty_c appContext) override;
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
};
