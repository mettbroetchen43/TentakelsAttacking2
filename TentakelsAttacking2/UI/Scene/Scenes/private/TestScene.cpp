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
			table->SetValue<IntCell, int>(row, column, row * 5 + column, false);
		}
	}
	table->SetValue<StringCell, std::string>(4, 0, "Abonniert coder2k", false);
	table->SetValue<StringCell, std::string>(4, 1, "Abonniert anyway", false);
	table->SetValue<StringCell, std::string>(4, 2, "Abonniert GyrosGeier", false);
	table->SetValue<StringCell, std::string>(4, 3, "Abonniert Necro", false);
	table->SetValue<StringCell, std::string>(4, 4, "Abonniert HAKUINU", false);
	table->SetValue<FloatCell, float>(1, 1, 7.5f, false);
	table->SetValue<DoubleCell, double>(2, 2, 13.542, false);
	table->SetValue<ColorCell, Color>(3, 4, PURPLE, false);
	table->ResizeCells();
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
