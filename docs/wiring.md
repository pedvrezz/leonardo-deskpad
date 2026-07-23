# Wiring

The firmware uses the Leonardo's internal pull-up resistors, so no external resistors are required.

| Component | Leonardo pin | Other side |
|---|---:|---|
| Button 1 | D2 | GND |
| Button 2 | D3 | GND |
| Button 3 | D4 | GND |
| Button 4 | D5 | GND |
| Arm switch | D7 | GND |
| Status LED | Built-in LED | Already connected |

A button is considered pressed when it connects its digital pin to ground. The arm switch must be closed before the board sends any keyboard input.

## Breadboard view

```text
GND ─────┬────[ Button 1 ]──── D2
         ├────[ Button 2 ]──── D3
         ├────[ Button 3 ]──── D4
         ├────[ Button 4 ]──── D5
         └────[ ARM SWITCH ]── D7
```

The arm switch is intentionally separate from the macro buttons. It provides a physical safety control while uploading firmware, moving cables or troubleshooting a computer.
