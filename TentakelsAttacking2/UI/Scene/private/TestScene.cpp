//
// Purpur Tentakel
// 05.09.2022
//

#include "TestScene.h"
#include "Slider.h"
#include "AppContext.h"
#include "UIManager.h"
#include "InputLine.h"
#include "Events.h"
#include <iostream>
#include <functional>

void TestScene::Test() {
	std::cout << "ENTER!\n";
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
	auto firstFocus = GetFocusableByFocusID(m_firstFocusID);
	if (firstFocus) {
		auto event = SelectFocusElementEvent(firstFocus);
		appContext.eventManager.InvokeEvent(event);
	}
}


TestScene::TestScene(Vector2 pos, Vector2 size, Alignment alignment, UIManager const& uiManager)
	: BaseMainScene(pos, size, alignment) {
	InitializeSzene(uiManager);
}

void TestScene::InitializeSzene(UIManager const& uiManager) {
	AppContext& appContext = AppContext::GetInstance();

	BaseMainScene::InitializeSzene(uiManager);
	// focus ID > 3!

	auto ptr4 = std::make_shared<InputLine<double>>(
		7,
		GetElementPosition(0.15f, 0.7f),
		GetElementSize(0.2f, 0.05f),
		Alignment::TOP_MID,
		10,
		appContext.assetManager.GetTexture(AssetType::GREY),
		uiManager.GetResolution()
		);
	ptr4->SetPlaceholderText("Double Input List");
	m_elements.push_back(ptr4);

	auto ptr3 = std::make_shared<InputLine<int>>(
		6,
		GetElementPosition(0.15f, 0.6f),
		GetElementSize(0.2f, 0.05f),
		Alignment::TOP_MID,
		10,
		appContext.assetManager.GetTexture(AssetType::GREY),
		uiManager.GetResolution()
		);
	ptr3->SetPlaceholderText("Integer Input List");
	m_elements.push_back(ptr3);

	auto ptr = std::make_shared<InputLine<std::string>>(
		4,
		GetElementPosition(0.15f, 0.4f),
		GetElementSize(0.2f, 0.05f),
		Alignment::TOP_MID,
		40,
		appContext.assetManager.GetTexture(AssetType::GREY),
		uiManager.GetResolution()
		);
	ptr->SetPlaceholderText("into for");
	ptr->SetOnEnter(std::bind(&TestScene::Test,*this));
	m_elements.push_back(ptr);
	m_firstFocusID = ptr->GetFocusID();

	ptr = std::make_shared<InputLine<std::string>>(
		5,
		GetElementPosition(0.15f, 0.5f),
		GetElementSize(0.2f, 0.05f),
		Alignment::TOP_MID,
		40,
		appContext.assetManager.GetTexture(AssetType::GREY),
		uiManager.GetResolution()
		);
	ptr->SetPlaceholderText("copy to");
	m_elements.push_back(ptr);

	auto ptr2 = std::make_shared<Slider>(
		GetElementPosition(0.05f, 0.1f),
		GetElementSize(0.025f, 0.75f),
		Alignment::TOP_MID,
		false,
		appContext.assetManager.GetTexture(AssetType::GREY),
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		6.0f,
		uiManager.GetResolution()
		);
	m_elements.push_back(ptr2);

	ptr2 = std::make_shared<Slider>(
		GetElementPosition(0.05f, 0.9f),
		GetElementSize(0.9f, 0.025f),
		Alignment::TOP_MID,
		true,
		appContext.assetManager.GetTexture(AssetType::GREY),
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		6.0f,
		uiManager.GetResolution()
		);
	m_elements.push_back(ptr2);
}

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (!m_active) { return; }

	InputLine<std::string>* ForCopy = nullptr;
	InputLine<std::string>* ForSave = nullptr;

	for (auto e : m_elements) {
		if (auto element = dynamic_cast<InputLine<std::string>*>(e.get())) {
			if (element->GetFocusID() == 4) {
				ForCopy = element;
			}
			if (element->GetFocusID() == 5) {
				ForSave = element;
			}
		}
	}
	if (ForCopy and ForCopy->HasValueChanced()) {
		ForSave->SetValue(ForCopy->GetValue());
	}


	Scene::CheckAndUpdate(mousePosition, appContext);
}


