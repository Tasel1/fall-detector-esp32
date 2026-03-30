# Data Model: Enhanced State and Configuration

## System States

| State | Description | Transition Trigger |
|-------|-------------|--------------------|
| `MONITORING` | Normal operation | System Init / Alert Canceled |
| `PRE_ALERT` | 15s warning phase | Fall Detected / Faint Detected |
| `SOS_ALERT` | Sequential alert active | Pre-alert Timeout / 10s Long Press |

## Config Constants (`config.h`)

| Constant | Default Value | Description |
|----------|---------------|-------------|
| `FALL_THRESHOLD` | 2.5g | Impact detection threshold |
| `FAINT_TIMEOUT` | 300s | Time of stillness before Faint trigger |
| `PRE_ALERT_DURATION`| 15s | Duration of buzzer ramping phase |
| `STILLNESS_VARIANCE`| 0.05 | Max variance for "still" state |
| `SOS_LONG_PRESS` | 10000ms | Threshold for immediate SOS |
| `BUZZER_PWM_CHAN` | 0 | ESP32 LEDC channel for buzzer |
| `BUZZER_FREQ_START` | 500 | Initial frequency (Hz) |
| `BUZZER_FREQ_END` | 2500 | Final frequency (Hz) |
