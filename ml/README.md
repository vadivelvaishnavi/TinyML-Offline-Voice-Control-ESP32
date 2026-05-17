# Machine Learning Model

This folder contains the TinyML model resources and inference-related files.

## Files

### `ml result.png`
Model validation and performance results.

### `red_light_inferencing.zip`
Exported Edge Impulse Arduino library containing:
- TinyML model
- Edge Impulse SDK
- MFCC extraction pipeline
- Inference engine

## Model Details

### Framework
- Edge Impulse TinyML

### Feature Extraction
- MFCC (Mel-Frequency Cepstral Coefficients)

### Classes
- noise
- red
- unknown

## Performance

- Accuracy: 96.8%
- Weighted F1 Score: 0.97
- ROC AUC: 0.98

## Inference Workflow

Audio Input → Noise Filtering → MFCC Extraction → TinyML Classification → Output Action
