//
// Purpur Tentakel
// 08.08.2022
//

// original Random by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)

#include "Button.h"
#include <raylib.h>
#include <vector>
#include <iostream>

void test() {
    std::cout << "clicked" << '\n';
    exit(0);
}

int main() {
    Vector2 resolution = { 800.0f, 450.0f };
    InitWindow(resolution.x, resolution.y, "raylib [core] example - basic window");
    if (false) {
        int display = GetCurrentMonitor();
        resolution.x = GetMonitorWidth(display);
        resolution.y = GetMonitorHeight(display);
        SetWindowSize(resolution.x, resolution.y);
    }
    //ToggleFullscreen();
    SetTargetFPS(60);

    std::vector<Button> buttons;
    buttons.reserve(2);
    buttons.emplace_back("Assets/btn_f_default.png", Vector2(0.6f, 0.2f), Vector2(0.2f, 0.13f), resolution, "Super Testtext, viel besser Text", test);
    buttons.emplace_back("Assets/btn_f_default.png", Vector2(0.4f, 0.4f), Vector2(0.3f, 0.2f), resolution, "Quit", test);
    buttons.at(0).SetEnabled(false);
    std::cout << "btn 0: " << buttons.at(0).IsEnabled() << '\n';
    std::cout << "btn 1: " << buttons.at(1).IsEnabled() << '\n';

    Vector2 mousePosition = GetMousePosition();

    while (!WindowShouldClose()) {
        mousePosition = GetMousePosition();
        for (auto& button : buttons) {
            button.CheckAndUpdate(mousePosition);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        for (auto& button : buttons) {
            button.Render();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}