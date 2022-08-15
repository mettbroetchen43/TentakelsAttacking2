//
// Purpur Tentakel
// 08.08.2022
//

// original Random by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)

#include "Button.h"
#include <raylib.h>
#include <iostream>

void test() {
    std::cout << "clicked" << '\n';
}

int main() {
    int width= 800;
    int height = 450;
    InitWindow(width, height, "raylib [core] example - basic window");
    int display = GetCurrentMonitor();
    height = GetMonitorHeight(display);
    width = GetMonitorWidth(display);
    SetWindowSize(width, height);
    //ToggleFullscreen();
    SetTargetFPS(60);

    Button button("Assets/discord.png", 100.0f, 100.0f, test);
    Vector2 mousePosition = GetMousePosition();

    while (!WindowShouldClose()) {
        mousePosition = GetMousePosition();
        button.CheckAndUpdate(mousePosition);

        BeginDrawing();
        ClearBackground(BLACK);
        button.Render();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}