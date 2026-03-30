# Research: Linker and API Mismatch Analysis

## Decision: Native Unity Integration
**Rationale**: The "multiple definition" errors in `error.md` stem from `lib_deps = Unity` in `platformio.ini` conflicting with the Unity library already included in the `framework-arduinoespressif32`. Removing the explicit dependency resolves the symbol duplication.
**Alternatives considered**: Using `lib_ignore = Unity` (Less clean than removing the unnecessary dependency).

## Decision: 3-Axis Fall Detection API
**Rationale**: `error.md` shows undefined references to `FallDetector::FallDetector()` and mismatches in `processSensorData`. We will standardize the API to `processSensorData(float ax, float ay, float az)` to ensure all axes are considered in the magnitude calculation, improving sensitivity.
**Technical details**: magnitude = `sqrt(ax*ax + ay*ay + az*az)`.

## Decision: GPS Coordinate SMS Payload
**Rationale**: Tests currently try to pass strings to `formatSMSPayload`, but the implementation (per `error.md`) expects floats. We will update the tests to pass `55.75f, 37.61f` and update the service to return a Google Maps formatted string.

## Decision: PWM-based Alert Ramping
**Rationale**: To meet the 500-2000Hz ramping requirement, we will use the ESP32 `ledc` peripheral.
- Start: 500Hz
- End: 2000Hz
- Duration: 15s
- Trigger: `updateAlert(ratio)` called from main loop.
