# Source Code

This folder contains the Arduino source code for the TinyML-based offline voice-controlled system.

## Files

### `sketch_apr12b.ino`
Main ESP32 firmware implementing:
- Audio capture using INMP441
- Noise filtering
- Voice Activity Detection (VAD)
- MFCC feature extraction
- TinyML inference
- OLED display output
- LED/Relay control

## Platform

- ESP32
- Arduino IDE
- Edge Impulse SDK

## Required Libraries

- Edge Impulse Inference SDK
- Adafruit SSD1306
- Adafruit GFX
- I2S Driver Libraries

## Usage

1. Open `sketch_apr12b.ino` in Arduino IDE
2. Select ESP32 board
3. Install required libraries
4. Upload firmware to ESP32
5. Open Serial Monitor

## Functionality

When the keyword `"RED"` is detected with confidence above threshold:
- LED turns ON
- OLED displays inference results
- Serial monitor prints prediction scores
