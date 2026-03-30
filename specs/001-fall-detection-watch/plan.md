# Implementation Plan: Smart Watch with Fall Detection

**Branch**: `001-fall-detection-watch` | **Date**: 2026-03-25 | **Spec**: [specs/001-fall-detection-watch/spec.md]
**Input**: Feature specification from `/specs/001-fall-detection-watch/spec.md`

## Summary
The goal is to develop an ESP32-based wearable device that detects falls using an MPU6050 accelerometer and triggers emergency alerts. The technical approach involves a modular C++ architecture (Sensors, Fall Detector, UI, Comms, Power) using the Arduino framework. Fall detection utilizes a threshold-based algorithm (2.5g impact + post-fall inactivity check).

## Technical Context

**Language/Version**: C++ (Arduino Framework)
**Primary Dependencies**: PlatformIO, Adafruit MPU6050, Adafruit SSD1306, TinyGSM (SIM800L), TinyGPS++, ESP32 BLE/WiFi
**Storage**: ESP32 NVS (Non-Volatile Storage) for contact lists and settings
**Testing**: Unity (embedded unit tests)
**Target Platform**: ESP32
**Project Type**: Embedded Firmware
**Performance Goals**: Fall detection processing < 50ms; GSM alert initiation < 5s after timer
**Constraints**: Deep sleep power < 5mA; BLE mandatory for config; 60s cancellation window
**Scale/Scope**: Single device firmware with companion app interface

## Constitution Check

| Principle | Gate Status | Implementation Plan |
|-----------|-------------|---------------------|
| I. Safety-First | ✅ PASSED | Algorithm prioritizes sensitivity; sequential alert fallback (112 -> personal). |
| II. Reliability | ✅ PASSED | GSM retry logic; SIM800L status monitoring; watchdog timer implementation. |
| III. TDD | ✅ PASSED | Algorithm logic and state machines will be developed using Unity unit tests. |
| IV. Modularity | ✅ PASSED | Modular design (Sensors, UI, Comms) abstracts hardware from logic. |
| V. Energy Efficiency | ✅ PASSED | Deep sleep usage; interrupt-driven sensor readings; minimized OLED uptime. |

## Project Structure

### Documentation (this feature)

```text
specs/001-fall-detection-watch/
├── plan.md              # This file
├── research.md          # Fall detection and hardware integration research
├── data-model.md        # NVS storage and BLE characteristic schema
├── quickstart.md        # Hardware setup and build instructions
├── contracts/           # BLE protocol and SMS/TTS format specifications
└── tasks.md             # Implementation tasks
```

### Source Code (repository root)

```text
src/
├── modules/
│   ├── sensors/         # MPU6050 and GPS drivers
│   ├── fall_detector/   # Detection algorithm and logic
│   ├── ui/              # OLED display and buzzer/vibration control
│   ├── comms/           # GSM/GPRS, BLE, and WiFi services
│   └── power/           # Sleep management and battery monitoring
├── main.cpp             # Global state and task management
tests/
├── unit/                # Algorithm and logic tests
└── hil/                 # Hardware-in-the-loop validation
```

**Structure Decision**: Single project with modular structure as requested.

## Complexity Tracking

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| None | N/A | N/A |
