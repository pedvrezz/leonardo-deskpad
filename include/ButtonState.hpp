#pragma once

#include <stdint.h>

enum class ButtonEvent : uint8_t {
    None,
    ShortPressed,
    LongPressed
};

class ButtonState {
public:
    ButtonState(uint32_t debounceMs = 30, uint32_t longPressMs = 700)
        : debounceMs_(debounceMs), longPressMs_(longPressMs) {}

    ButtonEvent update(bool rawPressed, uint32_t nowMs) {
        if (rawPressed != lastRawPressed_) {
            lastRawPressed_ = rawPressed;
            rawChangedAt_ = nowMs;
        }

        if (rawPressed != stablePressed_ && elapsed(nowMs, rawChangedAt_) >= debounceMs_) {
            stablePressed_ = rawPressed;
            if (stablePressed_) {
                stableChangedAt_ = nowMs;
                longPressSent_ = false;
                return ButtonEvent::None;
            }

            if (!longPressSent_) {
                return ButtonEvent::ShortPressed;
            }
            return ButtonEvent::None;
        }

        if (stablePressed_ && !longPressSent_ && elapsed(nowMs, stableChangedAt_) >= longPressMs_) {
            longPressSent_ = true;
            return ButtonEvent::LongPressed;
        }

        return ButtonEvent::None;
    }

    bool isPressed() const { return stablePressed_; }

private:
    static uint32_t elapsed(uint32_t now, uint32_t before) {
        return now - before;  // unsigned arithmetic safely handles millis() rollover
    }

    uint32_t debounceMs_;
    uint32_t longPressMs_;
    bool lastRawPressed_{false};
    bool stablePressed_{false};
    bool longPressSent_{false};
    uint32_t rawChangedAt_{0};
    uint32_t stableChangedAt_{0};
};
