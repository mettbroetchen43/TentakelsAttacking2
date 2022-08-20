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
}

int main() {
    int width = 800;
    int height = 450;
    InitWindow(width, height, "raylib [core] example - basic window");
    int display = GetCurrentMonitor();
    height = GetMonitorHeight(display);
    width = GetMonitorWidth(display);
    SetWindowSize(width, height);
    ToggleFullscreen();
    SetTargetFPS(60);

    std::vector<Button> buttons;
    buttons.reserve(2);
    buttons.emplace_back("Assets/btn_f_default.png", 100.0f, 100.0f, "Super Testtext", test);
    buttons.emplace_back("Assets/btn_f_default.png", 100.0f, 300.0f, "Super Testtext 2", test);

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