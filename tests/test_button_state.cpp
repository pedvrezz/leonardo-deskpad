#include "ButtonState.hpp"

#include <cassert>
#include <iostream>

int main() {
    ButtonState shortPress(30, 700);
    assert(shortPress.update(false, 0) == ButtonEvent::None);
    assert(shortPress.update(true, 10) == ButtonEvent::None);
    assert(shortPress.update(false, 20) == ButtonEvent::None);  // contact bounce
    assert(shortPress.update(true, 25) == ButtonEvent::None);
    assert(shortPress.update(true, 55) == ButtonEvent::None);   // debounced down
    assert(shortPress.isPressed());
    assert(shortPress.update(false, 100) == ButtonEvent::None);
    assert(shortPress.update(false, 130) == ButtonEvent::ShortPressed);
    assert(!shortPress.isPressed());

    ButtonState longPress(30, 700);
    assert(longPress.update(true, 0) == ButtonEvent::None);
    assert(longPress.update(true, 30) == ButtonEvent::None);
    assert(longPress.update(true, 729) == ButtonEvent::None);
    assert(longPress.update(true, 730) == ButtonEvent::LongPressed);
    assert(longPress.update(true, 900) == ButtonEvent::None);   // long press only once
    assert(longPress.update(false, 910) == ButtonEvent::None);
    assert(longPress.update(false, 940) == ButtonEvent::None);  // no short action after long action

    // Validate millis() rollover behavior.
    ButtonState rollover(10, 100);
    const uint32_t nearMax = 0xFFFFFFF8U;
    assert(rollover.update(true, nearMax) == ButtonEvent::None);
    assert(rollover.update(true, 3U) == ButtonEvent::None);     // debounced down across rollover
    assert(rollover.isPressed());

    std::cout << "All ButtonState tests passed\n";
    return 0;
}
