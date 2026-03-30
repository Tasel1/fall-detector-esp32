# Implementation Plan: Enhanced Alerts and Faint Detection

**Branch**: `002-enhanced-alerts-faint-monitor` | **Date**: 2026-03-25 | **Spec**: [specs/002-enhanced-alerts-faint-monitor/spec.md]
**Input**: Feature specification from `/specs/002-enhanced-alerts-faint-monitor/spec.md`

## Summary
The goal is to enhance the fall detection system with a Pre-alert mode, dynamic audio feedback (PWM-based ramping), and Faint Detection (motionless monitoring). The architecture will be updated to include a dedicated `AlertManager` for haptics/audio and a `MotionMonitor` for inactivity tracking.

## Technical Context

**Language/Version**: C++ (Arduino Framework)
**Primary Dependencies**: PlatformIO, Adafruit MPU6050, Adafruit SSD1306, TinyGSM, TinyGPS++, ESP32 BLE/WiFi
**Storage**: ESP32 NVS (for `config.h` overrides if applicable, or hardcoded constants)
**Testing**: Unity (Native ESP32 framework) - *Note: Remove from lib_deps to avoid conflict*
**Target Platform**: ESP32
**Project Type**: Embedded Firmware
**Performance Goals**: Inactivity detection within 5s of threshold; PWM ramping update frequency > 10Hz
**Constraints**: < 10mA in monitoring mode; 15s pre-alert window; 10s manual SOS threshold
**Scale/Scope**: Modular firmware update

## Constitution Check

| Principle | Gate Status | Implementation Plan |
|-----------|-------------|---------------------|
| I. Safety-First | ✅ PASSED | Faint detection provides a secondary safety net; 10s SOS is a reliable manual override. |
| II. Reliability | ✅ PASSED | `AlertManager` ensures wearer is notified BEFORE escalation; `MotionMonitor` uses variance to avoid false negatives. |
| III. TDD | ✅ PASSED | New modules (`MotionMonitor`, `AlertManager` logic) will have unit tests. |
| IV. Modularity | ✅ PASSED | Dedicated modules for motion and alerts keep logic decoupled. |
| V. Energy Efficiency | ✅ PASSED | Motion monitoring frequency will be optimized to minimize CPU wake time. |

## Project Structure

### Documentation (this feature)

```text
specs/002-enhanced-alerts-faint-monitor/
├── plan.md              # This file
├── research.md          # PWM ramping and variance-based motion detection research
├── data-model.md        # State transitions and config constants
├── quickstart.md        # Testing scenarios for faint detection
├── contracts/           # Updated API for Sensor modules
└── tasks.md             # Implementation tasks
```

### Source Code (repository root)

```text
src/
├── modules/
│   ├── sensors/         
│   │   ├── imu_sensor.cpp/h   # Updated API (3-axis input)
│   ├── fall_detector/   
│   │   ├── fall_detector.cpp/h # New states: PRE_ALERT, FAINT_DETECTED
│   ├── motion_monitor/  
│   │   ├── motion_monitor.cpp/h # Variance-based stillness detection
│   ├── alert_manager/   
│   │   ├── alert_manager.cpp/h  # PWM signal ramping logic
│   ├── ui/              
│   ├── comms/           
│   └── power/           
├── config.h             # Central configuration constants
├── main.cpp             
tests/
├── unit/                
└── hil/                 
```

**Structure Decision**: Modular extension of existing architecture.

## Complexity Tracking

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| None | N/A | N/A |
