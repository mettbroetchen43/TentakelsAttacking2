//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "Scene.h"
#include "InputLine.hpp"

class ColorPicker;
class Table;
class Focusable;

class NewGameScene : public Scene {
private:
	InputLine<std::string>* m_inputLine;
	ColorPicker* m_colorPicker;
	Table* m_table;
	std::vector<Focusable*> m_nestedFocus;
	void Initialize(Vector2 resolution, AppContext& appContext);
	void CheckForNestedFocus(Vector2 const& mousePosition,
		AppContext const& appContext) const;

	void UpdateSceneEntries(AppContext const& appContext);

	void AddPlayer();
	void DeletePlayer();


public:
	NewGameScene(Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};
