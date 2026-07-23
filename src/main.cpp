#include <Arduino.h>
#include <Keyboard.h>

#include "ButtonState.hpp"
#include "MacroConfig.hpp"

namespace {

constexpr uint8_t BUTTON_PINS[] = {2, 3, 4, 5};
constexpr uint8_t ARM_SWITCH_PIN = 7;  // connect to GND to enable keyboard output
constexpr uint8_t STATUS_LED_PIN = LED_BUILTIN;
constexpr size_t BUTTON_COUNT = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);
static_assert(BUTTON_COUNT == MACRO_COUNT, "Each button must have a configured macro");

ButtonState buttons[BUTTON_COUNT];
bool keyboardArmed = false;

void sendChord(const KeyChord& chord) {
    for (uint8_t index = 0; index < chord.modifierCount; ++index) {
        Keyboard.press(chord.modifiers[index]);
    }
    Keyboard.press(chord.key);
    delay(35);
    Keyboard.releaseAll();
}

void blink(uint8_t times, uint16_t durationMs) {
    for (uint8_t index = 0; index < times; ++index) {
        digitalWrite(STATUS_LED_PIN, HIGH);
        delay(durationMs);
        digitalWrite(STATUS_LED_PIN, LOW);
        delay(durationMs);
    }
}

void setArmed(bool armed) {
    if (keyboardArmed == armed) return;
    keyboardArmed = armed;
    if (armed) {
        Keyboard.begin();
        blink(2, 80);
    } else {
        Keyboard.releaseAll();
        Keyboard.end();
        digitalWrite(STATUS_LED_PIN, LOW);
    }
}

}  // namespace

void setup() {
    pinMode(STATUS_LED_PIN, OUTPUT);
    pinMode(ARM_SWITCH_PIN, INPUT_PULLUP);
    for (const auto pin : BUTTON_PINS) {
        pinMode(pin, INPUT_PULLUP);
    }

    // A visible startup delay prevents accidental keystrokes while the board resets.
    blink(3, 180);
    setArmed(digitalRead(ARM_SWITCH_PIN) == LOW);
}

void loop() {
    setArmed(digitalRead(ARM_SWITCH_PIN) == LOW);
    const uint32_t now = millis();

    for (size_t index = 0; index < BUTTON_COUNT; ++index) {
        const bool pressed = digitalRead(BUTTON_PINS[index]) == LOW;
        const auto event = buttons[index].update(pressed, now);

        if (!keyboardArmed) continue;
        if (event == ButtonEvent::ShortPressed) {
            sendChord(SHORT_MACROS[index]);
        } else if (event == ButtonEvent::LongPressed) {
            sendChord(LONG_MACROS[index]);
        }
    }

    delay(2);
}
