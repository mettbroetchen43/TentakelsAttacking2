//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "Scene.h"
#include "InputLine.hpp"
#include "AbstractTableCell.h"
#include "EventListener.hpp"

class ColorPicker;
class Table;
class Focusable;
class ClassicButton;

class NewGamePlayerScene final : public Scene, public EventListener {
private:
	InputLine<std::string>* m_inputLine;
	ColorPicker* m_colorPicker;
	Table* m_table;
	std::shared_ptr<ClassicButton> m_nextBTN;
	std::vector<Focusable*> m_nestedFocus;
	void Initialize(Vector2 resolution, AppContext& appContext);
	void CheckForNestedFocus(Vector2 const& mousePosition,
		AppContext const& appContext) const;

	void UpdateSceneEntries(AppContext const& appContext);

	void AddPlayer();
	void UpdatePlayer(unsigned int ID, std::string const& name,
		Color color, AppContext const& appContext);
	void UpdatePlayerName(AbstractTableCell const* cell,
		std::string oldValue, std::string newValue);
	void UpdatePlayerColor(AbstractTableCell const* cell,
		Color oldValue, Color newValue);
	void CreateDeletePlayer();
	void DeletePlayer(unsigned int ID);
	void CheckPlayerCount() const;
	void NextScene(bool valid);
	void Reset();

	void SetNextButton(AppContext const& appContext);

public:
	NewGamePlayerScene(Vector2 resolution);
	~NewGamePlayerScene();

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	void OnEvent(Event const& event) override;
};
