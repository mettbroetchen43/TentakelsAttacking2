//
// Purpur Tentakel
// 24.10.2022
//

#include "HInput.h"
#include <raylib.h>

bool IsConfirmInputPressed() {
    return (IsKeyPressed(KEY_ENTER)
        or IsKeyPressed(KEY_KP_ENTER)
        or IsKeyPressed(KEY_SPACE))
        && !IsSkipInput();
}
bool IsConfirmInputReleased() {
    return (IsKeyReleased(KEY_ENTER)
        or IsKeyReleased(KEY_KP_ENTER)
        or IsKeyReleased(KEY_SPACE))
        && !IsSkipInput();
}
bool IsConfirmInputDown() {
    return (IsKeyDown(KEY_ENTER)
        or IsKeyDown(KEY_KP_ENTER)
        or IsKeyDown(KEY_SPACE))
        && !IsSkipInput();
}
bool IsConfirmInputUp() {
    return (IsKeyUp(KEY_ENTER)
        or IsKeyUp(KEY_KP_ENTER)
        or IsKeyUp(KEY_SPACE))
        && !IsSkipInput();
}

bool IsBackInputPressed() {
    return IsKeyPressed(KEY_ESCAPE);
}
bool IsBackInputReleased() {
    return IsKeyReleased(KEY_ESCAPE);
}
bool IsBackInputDown() {
    return IsKeyDown(KEY_ESCAPE);
}
bool IsBackInputUp() {
    return IsKeyUp(KEY_ESCAPE);
}

bool IsToggleFullscreenInput() {
    return IsKeyPressed(KEY_F11)
        || (IsKeyDown(KEY_LEFT_ALT)
            && (IsKeyPressed(KEY_ENTER)));
}

bool IsSkipInput() {
    return IsKeyDown(KEY_LEFT_ALT);
}

bool IsQuitInput() {
    return IsKeyDown(KEY_LEFT_ALT)
        and IsKeyDown(KEY_F4);
}
