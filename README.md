# Leonardo DeskPad

Leonardo DeskPad turns an Arduino Leonardo into a four-button USB productivity macro pad with a physical arm switch, software debounce and separate short/long-press actions.

Unlike many HID automation examples, this project is intentionally visible and user-controlled. It does not auto-type on connection, download content or hide its behavior.

## Default actions

| Button | Short press | Long press |
|---|---|---|
| 1 | Copy | Select all |
| 2 | Paste | Undo |
| 3 | Reopen closed tab | New private/incognito window |
| 4 | Focus address bar | Task Manager on Windows |

All actions are configured in `include/MacroConfig.hpp`.

## Hardware

- Arduino Leonardo or compatible ATmega32U4 board
- Four momentary push buttons
- One maintained switch for arming
- Breadboard or enclosure
- USB cable

See [`docs/wiring.md`](docs/wiring.md) for connections.

## Build with PlatformIO

```bash
platformio run
platformio run --target upload
```

Or open the project with the PlatformIO extension in VS Code.

## Safety behavior

- Keyboard output only starts when D7 is connected to GND
- Three LED flashes occur during startup
- The firmware never sends a macro automatically at boot
- `Keyboard.releaseAll()` runs when the arm switch is disabled
- Debounce logic prevents duplicate presses

## Test the button state machine on a computer

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude tests/test_button_state.cpp -o button-tests
./button-tests
```

## Ideas for expansion

- Rotary encoder for volume
- OLED showing the current profile
- Multiple profiles stored in EEPROM
- 3D-printable enclosure
- MQTT status through a second network-capable microcontroller

## License

MIT
