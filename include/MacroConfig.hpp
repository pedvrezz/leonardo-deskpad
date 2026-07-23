#pragma once

#include <Arduino.h>
#include <Keyboard.h>

struct KeyChord {
    uint8_t modifiers[3];
    uint8_t modifierCount;
    uint8_t key;
};

// Edit only this table to customize the four buttons.
// Defaults are useful and non-destructive on Windows/Linux browsers and editors.
constexpr KeyChord SHORT_MACROS[] = {
    {{KEY_LEFT_CTRL, 0, 0}, 1, 'c'},                 // Copy
    {{KEY_LEFT_CTRL, 0, 0}, 1, 'v'},                 // Paste
    {{KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 0}, 2, 't'},    // Reopen closed browser tab
    {{KEY_LEFT_CTRL, 0, 0}, 1, 'l'}                  // Focus browser address bar
};

constexpr KeyChord LONG_MACROS[] = {
    {{KEY_LEFT_CTRL, 0, 0}, 1, 'a'},                 // Select all
    {{KEY_LEFT_CTRL, 0, 0}, 1, 'z'},                 // Undo
    {{KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 0}, 2, 'n'},    // New private/incognito window
    {{KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 0}, 2, KEY_ESC} // Task manager on Windows
};

constexpr size_t MACRO_COUNT = sizeof(SHORT_MACROS) / sizeof(SHORT_MACROS[0]);
