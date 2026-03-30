# Research: Enhanced Alerts and Faint Detection

## Decision: PWM-based Audio Ramping
**Rationale**: To increase alert urgency, we will use the ESP32's `ledc` peripheral to control the piezo buzzer. Ramping will involve increasing both the duty cycle (volume) and frequency (pitch) over the 15-second Pre-alert period.
**Technical details**: 
- Peripheral: `ledc` (PWM)
- Resolution: 8-bit (0-255)
- Ramping steps: 10 steps over 15 seconds.

## Decision: Variance-based Stillness Detection (Faint Monitor)
**Rationale**: Detecting a "faint" requires distinguishing between a device left on a table and a device worn by someone perfectly still. We will calculate the variance of the accelerometer magnitude ($|A| = \sqrt{x^2 + y^2 + z^2}$) over a 5-second sliding window.
- **Stillness**: Variance below a threshold `VAR_THRESHOLD`.
- **Faint Trigger**: Stillness maintained for `FAINT_TIMEOUT` (5 minutes).
**Alternatives considered**: Absolute threshold (too sensitive to sensor noise).

## Decision: Unified Configuration (`config.h`)
**Rationale**: To ensure maintainability, all magic numbers (thresholds, timeouts, pin assignments) will be moved to a central `src/config.h`. This allows for rapid tuning during testing.

## Decision: Native Unity Integration
**Rationale**: PlatformIO's Unity library in `lib_deps` often conflicts with the Unity version bundled in the Espressif32 framework. We will remove the explicit dependency and rely on the framework's built-in Unity for unit testing.
