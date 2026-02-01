# Arduino-Marble-Run-Story-Machine

An interactive marble-run machine that uses Arduino, ultrasonic sensors, an RGB LCD, and a buzzer to tell a narrative about unequal household labor — built as a **Critical Making** project at TU Munich.

## Concept

The machine narrates the story of Alex and Robin, a couple living together. Players send each character home from work by inserting marbles into the run. While Alex's journey home is straightforward, Robin's trip gets delayed — prompting players to pull out physical cards that reveal why (household duties, invisible labor, etc.). The machine then asks: *"Whose time got stolen?"* and invites players to try again and think about how to make things more fair.

## How It Works

1. **Round 1** — Insert a marble on the left to send Alex home. Sensor 2 detects the marble and Alex arrives quickly.
2. Robin's turn — Insert a marble on the right. Sensor 1 detects launch, but the marble must travel a longer/interrupted path. The LCD cycles through prompts to pull out story cards while music plays.
3. Sensor 3 detects Robin's arrival (or a 60-second timeout triggers "Robin got lost...").
4. The LCD asks *"Whose time got stolen?"* and prompts switching to Round 2.
5. **Round 2** — Flip the physical switch. The machine encourages players to retry and rethink the distribution.

## Hardware

| Component | Pin(s) | Purpose |
|---|---|---|
| Ultrasonic Sensor 1 | Trig: 3, Echo: 2 | Detects marble (Robin launch) |
| Ultrasonic Sensor 2 | Trig: 5, Echo: 4 | Detects marble (Alex arrival) |
| Ultrasonic Sensor 3 | Trig: 7, Echo: 6 | Detects marble (Robin arrival) |
| Buzzer | 8 | Melodies and sound effects |
| Toggle Switch | 13 | Switches between Round 1 and Round 2 |
| Grove RGB LCD (16×2) | I²C | Story text and prompts |

## Wiring Diagram

```
Arduino Uno
├── D2  ← Echo  (Ultrasonic 1)
├── D3  → Trig  (Ultrasonic 1)
├── D4  ← Echo  (Ultrasonic 2)
├── D5  → Trig  (Ultrasonic 2)
├── D6  ← Echo  (Ultrasonic 3)
├── D7  → Trig  (Ultrasonic 3)
├── D8  → Buzzer
├── D13 ← Toggle Switch (INPUT_PULLUP)
└── I²C → Grove RGB LCD
```

## Software Features

- **Non-blocking melody playback** — Music plays concurrently with LCD text updates and sensor polling during Robin's delayed journey
- **Drop sound effect** — A descending frequency sweep (1500→300 Hz) plays every 2 seconds to simulate marble movement
- **Dual melodies** — A startup fanfare and two game melodies for different narrative moments
- **Timeout handling** — If Robin's marble doesn't arrive within 60 seconds, the story adapts
- **Two-round structure** — Physical switch toggles between the narrative round and the reflection round

## Dependencies

- [Grove RGB LCD Library](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight) (`rgb_lcd.h`)
- Arduino built-in `Wire.h` and `tone()`

## Setup

1. Wire components according to the diagram above
2. Install the Grove RGB LCD library via Arduino Library Manager
3. Open `marble_run.ino` in Arduino IDE
4. Upload to an Arduino Uno
5. Flip the switch to start Round 1

## License

MIT License — see [LICENSE](LICENSE) for details.
