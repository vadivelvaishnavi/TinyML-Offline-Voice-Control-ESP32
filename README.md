# Adaptive Noise-Robust Offline Voice-Controlled Microcontroller using TinyML

An ESP32-based TinyML voice recognition system capable of offline keyword spotting with adaptive noise handling and real-time device control.

---

#  Project Overview

This project implements an adaptive noise-robust offline voice-controlled microcontroller system using TinyML and ESP32.

The system captures voice input through an INMP441 I2S microphone, processes the audio using adaptive noise filtering and MFCC feature extraction, and performs keyword spotting directly on the microcontroller using an Edge Impulse TinyML model.

When the predefined keyword **"RED"** is detected, the ESP32 activates output devices such as LEDs or relays.

The entire system works completely offline without cloud dependency, ensuring:
- Low latency
- Privacy
- Energy efficiency
- Real-time edge AI processing

---

#  Features

- Offline voice recognition
- TinyML inference on ESP32
- Adaptive noise filtering
- Voice Activity Detection (VAD)
- MFCC feature extraction
- Real-time keyword spotting
- OLED feedback display
- Low-power embedded AI
- Privacy-preserving edge intelligence

---

#  Hardware Components

| Component | Purpose |
|---|---|
| ESP32 Dev Board | Main controller |
| INMP441 I2S Microphone | Audio capture |
| SSD1306 OLED Display | Display inference results |
| LED / Relay Module | Output actuation |
| Breadboard & Jumper Wires | Connections |
| 5V USB Supply | Power source |

---

#  System Workflow

```text
Microphone Input
       ↓
Adaptive Noise Filtering
       ↓
Voice Activity Detection (VAD)
       ↓
MFCC Feature Extraction
       ↓
TinyML Inference
       ↓
ESP32 Decision Logic
       ↓
LED / Relay Output
```

---

#  Block Diagram

<p align="center">
  <img src="doc/block.png" width="900">
</p>

---

#  Circuit Diagram

<p align="center">
  <img src="hardware/circuit_diagram.png" width="1000">
</p>

---

#  Hardware Prototype

<p align="center">
  <img src="hardware/hardware.png" width="700">
</p>

---

#  ML Model Performance

<p align="center">
  <img src="ml/ml result.png" width="800">
</p>

## Model Metrics

| Metric | Value |
|---|---|
| Accuracy | 96.8% |
| Weighted Precision | 0.97 |
| Weighted Recall | 0.97 |
| Weighted F1 Score | 0.97 |
| ROC AUC | 0.98 |

---

#  Serial Monitor Output

<p align="center">
  <img src="result/output.png" width="500">
</p>

### Sample Output

```text
Peak: 20232
noise: 0.45
red: 0.42
unknown: 0.13

FINAL red=0.42 noise=0.45
LED ON
```

---

#  Repository Structure

```text
.
├── code/
│   ├── README.md
│   └── sketch_apr12b.ino
│
├── doc/
│   ├── README.md
│   ├── block.png
│   ├── voice_controller.pdf
│   └── voice_controller_report.pdf
│
├── hardware/
│   ├── README.md
│   ├── circuit_diagram.png
│   └── hardware.png
│
├── ml/
│   ├── README.md
│   ├── ml result.png
│   └── red_light_inferencing.zip
│
├── result/
│   ├── README.md
│   ├── demo.mp4
│   ├── ml result.png
│   └── output.png
│
├── LICENSE
└── README.md
```

---

#  Software & Tools

- Arduino IDE
- Edge Impulse
- TensorFlow Lite for Microcontrollers
- ESP32 Board Package
- Adafruit SSD1306 Library
- TinyML Inference SDK

---

#  Machine Learning Details

## Framework
- Edge Impulse TinyML

## Feature Extraction
- MFCC (Mel-Frequency Cepstral Coefficients)

## Classes
- noise
- red
- unknown

## Deployment
- ESP32 Microcontroller
- Fully offline inference

---

#  Applications

- Smart Home Automation
- Healthcare Assistive Devices
- Industrial Automation
- Agricultural IoT
- Automotive Voice Interfaces
- Educational Embedded AI Kits
- Wearable Electronics

---


#  Future Improvements

- Multi-keyword recognition
- MQTT/WiFi integration
- Multi-language support
- Ultra-low-power optimization
- Sensor fusion systems
- Smart city deployment

---

#  Demo

Demo video available in:

```text
result/demo.mp4
```
---

#  Acknowledgements

- Edge Impulse
- TensorFlow Lite Micro
- Espressif ESP32
- TinyML Community
  
---


#  Author

Kesihambigai S

---

#  License

This project is licensed under the MIT License.

