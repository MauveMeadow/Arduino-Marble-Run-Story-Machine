It integrates the technical details from your Arduino code (pin definitions, libraries, and logic) with the conceptual framework provided in the "Chains2Change" report.

### **Response Summary & Source Basis**

The following README includes a summary of the **Critical Making** project "Chains2Change". It outlines the concept of **Trip Chaining**, where women's travel patterns are often fragmented by care obligations compared to men's linear journeys. The device uses a marble run to visualize this inequality, featuring two characters: **Alex** (linear path) and **Robin** (interrupted path). The code logic provided controls the ultrasonic sensors, LCD storytelling, and audio feedback for the two rounds of interaction: "Unequal Distribution" and "Making It Fair".


### **README.md**

# Chains2Change: Translating Gendered Trip Chaining into Tangible Experience

**Chains2Change** is an interactive Critical Making artifact designed to visualize and challenge the invisible inequalities of **Trip Chaining** in urban mobility. 

Using a vertical marble run powered by Arduino, this project physically demonstrates the difference between linear "commuter" travel and the fragmented, care-laden journeys often undertaken by women.

## 📖 Context & Concept

Research shows that mobility is not gender-neutral. While men often follow linear routes (Home → Work → Home), women are statistically more likely to engage in **Trip Chaining**—linking multiple stops for care work (e.g., school drop-offs, grocery shopping) within a single journey.

This artifact materializes that data into a storytelling machine with two characters:
* **Alex:** Follows a smooth, direct path (representing the linear commute).
* **Robin:** Follows a path blocked by physical "Task Cards" (representing care obligations like "Pick up kids" or "Buy groceries").

The device invites users to experience the frustration of delay and interruption, and then actively redistribute the "burden" to see how shared responsibility changes the flow of the "day."

## ⚙️ How It Works

The system runs on an **Arduino Uno** and uses ultrasonic sensors to track the marbles' progress, triggering audio cues and narrative text on an LCD screen.

### The Interaction Loop
1.  **Round 1 (The Status Quo):** * **Alex** is released. The marble travels uninterrupted. Music is playful and continuous.
    * **Robin** is released. The marble is stopped by obstacles (Task Cards). The user must physically remove cards to let Robin proceed. The music is fragmented, and the screen displays delays.
2.  **Round 2 (Making it Fair):**
    * The user flips a toggle switch.
    * The system prompts the user to redistribute the obstacles (Task Cards) between both paths to balance the travel time.

## 🛠️ Hardware & Wiring

### Components
* **Microcontroller:** Arduino Uno R3
* **Display:** 16x2 RGB LCD (Grove - LCD RGB Backlight)
* **Sensors:** 3x HC-SR04 Ultrasonic Sensors
* **Audio:** Passive Piezo Buzzer
* **Input:** Toggle Switch

### Pin Configuration
Based on `Marble_Run.ino`:

| Component | Pin / Port | Function |
| :--- | :--- | :--- |
| **Ultrasonic Sensor 1** | Trig: `3`, Echo: `2` | Detects **Robin** leaving work (Start) |
| **Ultrasonic Sensor 2** | Trig: `5`, Echo: `4` | Detects **Alex** leaving work (Start) |
| **Ultrasonic Sensor 3** | Trig: `7`, Echo: `6` | Detects **Robin** arriving home (End) |
| **Buzzer** | `8` | Audio feedback & Melodies |
| **Switch** | `13` | Toggles between Round 1 and Round 2 |
| **RGB LCD** | `I2C` (SDA/SCL) | Narrative display |

## 💻 Software & Dependencies

The code is written in C++ for the Arduino IDE.

### Required Libraries
* **`Wire.h`**: Standard Arduino library for I2C communication.
* **`rgb_lcd.h`**: Library for the Grove RGB LCD. You may need to install the [Grove - LCD RGB Backlight](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight) library via the Arduino Library Manager.

### Installation
1.  Connect components according to the pinout above.
2.  Install the `Grove - LCD RGB Backlight` library.
3.  Upload `Marble_Run.ino` to your Arduino Uno.
4.  Power the Arduino (via USB or external power).
5.  Ensure the "Start" sensors are placed at the top of the run and the "End" sensor is at the bottom of Robin's track.

## 👥 Authors & Acknowledgments

**Project Team:**
* Mays Al Sheikh
* Hala Kassab
* Matthias Ellerböck

*This project was developed as part of a seminar on Critical Making, aiming to bridge the gap between abstract mobility data and tangible human experience.*

```
