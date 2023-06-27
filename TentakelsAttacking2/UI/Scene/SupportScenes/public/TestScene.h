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
	std::array<double, 7> m_times{3.5, 2.5, 5.0, 8.3, 7.9, 10.0, 12.0 };
	std::array<int, 7> m_numbers{-1000, -265, -35, 0, 10, 345, 1065};

	void Initialize(AppContext_ty appContext);

public:
	TestScene(Vector2 resolution);
	void SetActive(bool active, AppContext_ty_c appContext) override;

	void TestLambda(CountingNumber::Type type, int start, int current, double time);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	void Render(AppContext_ty_c appContext) override;
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
};
