//
// Purpur Tentakel
// 24.10.2022
//

#include "HInput.h"
#include <raylib.h>

bool IsConfirmInputPressed() {
    return IsKeyPressed(KEY_ENTER)
        or IsKeyPressed(KEY_KP_ENTER)
        or IsKeyPressed(KEY_SPACE);
}
bool IsConfirmInputReleased() {
    return IsKeyReleased(KEY_ENTER)
        or IsKeyReleased(KEY_KP_ENTER)
        or IsKeyReleased(KEY_SPACE);
}
bool IsConfirmInputDown() {
    return IsKeyDown(KEY_ENTER)
        or IsKeyDown(KEY_KP_ENTER)
        or IsKeyDown(KEY_SPACE);
}
bool IsConfirmInputUp() {
    return IsKeyUp(KEY_ENTER)
        or IsKeyUp(KEY_KP_ENTER)
        or IsKeyUp(KEY_SPACE);
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
