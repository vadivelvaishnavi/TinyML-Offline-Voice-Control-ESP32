# Project Results

This folder contains project outputs, inference screenshots, and demo results.

## Files

### `demo.mp4`
Project demonstration video showing:
- Voice command recognition
- LED activation
- OLED display feedback
- Real-time inference

### `ml result.png`
TinyML model performance metrics and confusion matrix.

### `output.png`
Serial monitor output showing:
- Prediction scores
- Noise levels
- Keyword detection
- LED activation status

## Observed Results

- Offline keyword spotting achieved successfully
- Noise robustness improved using adaptive thresholds
- Real-time response under 200 ms
- Reliable operation on ESP32
- Accurate detection of keyword `"RED"`

## Output Example

```text
Peak: 20232
noise: 0.45
red: 0.42
unknown: 0.13

FINAL red=0.42 noise=0.45
LED ON
```
