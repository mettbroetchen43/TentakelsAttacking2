//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "UIManager.h"

void TestScene::Initialize(Vector2 resolution,
	[[maybe_unused]] AppContext& appContext) {
	auto table = std::make_shared<Table>(
		GetElementPosition(0.1f, 0.1f),
		GetElementSize(0.8f, 0.8f),
		Alignment::TOP_LEFT,
		1,
		10,
		5,
		resolution
		);
	for (int row = 0; row < 10; ++row) {
		for (int column = 0; column < 5; ++column) {
			table->SetValue<IntCell, int>(row, column, row * 5 + column);
		}
	}
	table->SetValue<StringCell, std::string>(4, 2, "Aboniert GyrosGeier");
	table->SetValue<FloatCell, float>(1, 1, 7.5f);
	table->SetValue<DoubleCell, double>(2, 2, 13.542);
	table->SetValue<ColorCell, Color>(3, 4, PURPLE);
	m_elements.push_back(table);
}

TestScene::TestScene(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution)
	: Scene(pos, size, alignment) {
	Initialize(resolution, AppContext::GetInstance());
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}
