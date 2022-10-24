//
// Purpur Tentakel
// 24.10.2022
//

#include "HInput.h"
#include <raylib.h>

bool IsConfirmInput() {
    return IsKeyPressed(KEY_ENTER)
        or IsKeyPressed(KEY_KP_ENTER)
        or IsKeyPressed(KEY_SPACE);
}
bool IsBackInput() {
    return IsKeyPressed(KEY_ESCAPE);
}
bool IsQuitInput() {
    return IsKeyDown(KEY_LEFT_ALT)
        and IsKeyDown(KEY_F4);
}
