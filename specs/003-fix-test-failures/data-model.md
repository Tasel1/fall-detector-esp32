# Data Model: Module Interface Updates

## FallDetector (Extended API)
- `bool processSensorData(float ax, float ay, float az)`: Logic-heavy entry point.
- `float calculateMagnitude(float ax, float ay, float az)`: Static helper.

## GSMService (Fixed API)
- `String formatSMSPayload(float lat, float lng)`: Returns Google Maps link.

## AlertManager (NEW)
- `void begin()`: Init PWM channel.
- `void startAlert()`: Activate sound.
- `void updateAlert(float remainingRatio)`: Calculate frequency (500 + 1500 * (1 - ratio)).
- `void stop()`: Turn off PWM.

## MotionMonitor (NEW)
- `void update(float accMagnitude)`: Record current reading.
- `bool isMotionless()`: True if magnitude < THRESHOLD for > 5 mins.

## Configuration (src/config.h additions)
| Key | Value | Description |
|-----|-------|-------------|
| `BUZZER_PIN` | 13 | PWM Pin |
| `FAINT_TIMEOUT_MS` | 300000 | 5 minutes |
| `ALERT_DURATION_MS` | 15000 | 15 seconds |
| `STILLNESS_THRESHOLD` | 0.2f | G-force threshold for "still" |
