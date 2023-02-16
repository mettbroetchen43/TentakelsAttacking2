//
// Purpur Tentakel
// 24.10.2022
//

#include "HInput.h"
#include "AppContext.h"
#include <CustomRaylib.h>

bool IsConfirmInputPressed() {
    bool triggered =
        IsKeyPressed(KEY_SPACE)
        or IsKeyPressed(KEY_KP_ENTER)
        or IsKeyPressed(KEY_ENTER)
        && !IsSkipInput()
        && !AppContext::GetInstance().constants.global.acceptInputTriggered;

    if (triggered) { AppContext::GetInstance().constants.global.acceptInputTriggered = true; }

    return triggered;
}
bool IsConfirmInputReleased() {
    bool triggered =
        IsKeyReleased(KEY_SPACE)
        or IsKeyReleased(KEY_KP_ENTER)
        or IsKeyReleased(KEY_ENTER)
        && !IsSkipInput()
        && !AppContext::GetInstance().constants.global.acceptInputTriggered;

    if (triggered) { AppContext::GetInstance().constants.global.acceptInputTriggered = true; }

    return triggered;
}
bool IsConfirmInputDown() {
    return IsKeyDown(KEY_SPACE)
        or IsKeyDown(KEY_KP_ENTER)
        or IsKeyDown(KEY_ENTER)
        && !IsSkipInput();
}
bool IsConfirmInputUp() {
    return IsKeyUp(KEY_KP_ENTER)
        or IsKeyUp(KEY_SPACE)
        or IsKeyUp(KEY_ENTER)
        && !IsSkipInput();
}

bool IsOnlyEnterConfirmInputPressed() {
    bool triggered =
        IsKeyPressed(KEY_KP_ENTER)
        or IsKeyPressed(KEY_ENTER)
        && !IsSkipInput()
        && !AppContext::GetInstance().constants.global.acceptInputTriggered;

    if (triggered) { AppContext::GetInstance().constants.global.acceptInputTriggered = true; }

    return triggered;
}
bool IsOnlyEnterConfirmInputReleased() {
    bool triggered =
        IsKeyReleased(KEY_KP_ENTER)
        or IsKeyReleased(KEY_ENTER)
        && !IsSkipInput()
        && !AppContext::GetInstance().constants.global.acceptInputTriggered;

    if (triggered) { AppContext::GetInstance().constants.global.acceptInputTriggered = true; }

    return triggered;
}
bool IsOnlyEnterConfirmInputDown() {
    return IsKeyDown(KEY_KP_ENTER)
        or IsKeyDown(KEY_ENTER)
        && !IsSkipInput();
}
bool IsOnlyEnterConfirmInputUp() {
    return IsKeyUp(KEY_KP_ENTER)
        or IsKeyUp(KEY_ENTER)
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
