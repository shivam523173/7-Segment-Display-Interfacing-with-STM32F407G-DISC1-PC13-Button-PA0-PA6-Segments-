# 7-Segment Display Interfacing with STM32F407G-DISC1 (PC13 Button)

This project drives a **common-cathode 1-digit 7-segment** using **PA0–PA6** for segments **a–g** and increments the displayed digit **0→9** on each press of the onboard **user button (PC13, EXTI)**.

## 🎯 Objective
Display 0–9 on the 7-segment and increment on each PC13 button press.

## 🧰 Components
- STM32F407G-DISC1
- 1-digit 7-segment (common cathode)
- 7 × 220–330 Ω resistors
- Wires, breadboard, USB
- STM32CubeIDE

## 🔌 Pin Connections
- Segments: **a→PA0, b→PA1, c→PA2, d→PA3, e→PA4, f→PA5, g→PA6**
- Common Cathode → **GND**
- User Button → **PC13 (onboard)**

> Each segment requires its own current-limiting resistor to 3.3 V GPIO.

## 🛠 CubeIDE Setup
1. New STM32 Project → **STM32F407G-DISC1**
2. Pinout:
   - `PA0–PA6` → **GPIO_Output**
   - `PC13` → **GPIO External Interrupt** (Rising edge)
3. NVIC: enable **EXTI15_10**.
4. Generate code and paste the provided `main.c`.

## 🧠 How It Works
- `segmentNumber[]` holds bit patterns for **0–9** (common-cathode).
- `HAL_GPIO_EXTI_Callback()` sets `button_pressed` on **PC13** interrupt.
- Main loop updates the segments to the current digit.

## ▶️ Build & Run
- Flash via ST-Link from CubeIDE.
- On power-up, the display shows the current value and increments on each press.

## 🧪 Observation Table
| Test Step              | Expected Outcome            |
|------------------------|-----------------------------|
| Power ON               | Display shows `0`           |
| Press PC13 once        | Increments to next digit    |
| After `9` then press   | Wraps around to `0`         |
| No button press        | Digit remains steady        |
| Verify PA0–PA6 wiring  | Proper segments illuminate  |

## ⚠️ Notes
- Use a **common cathode** device for these patterns.
- Debouncing may be added if multiple increments occur on a single press (optional).
- Keep wiring short and resistors correctly rated (220–330 Ω).

## 📄 License
MIT — educational use.
