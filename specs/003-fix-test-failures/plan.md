# Implementation Plan: Fix Test Failures

**Branch**: `003-fix-test-failures` | **Date**: 2026-03-25 | **Spec**: [specs/003-fix-test-failures/spec.md]
**Input**: Feature specification from `/specs/003-fix-test-failures/spec.md`

## Summary
The goal is to resolve build and execution errors in the test suite by fixing library conflicts, aligning module APIs with test expectations, and completing missing logic in core modules. This includes fixing the Unity library overlap, updating FallDetector and GSMService signatures, and implementing the AlertManager and MotionMonitor classes as specified.

## Technical Context

**Language/Version**: C++ (Arduino Framework)
**Primary Dependencies**: PlatformIO, Adafruit MPU6050, TinyGSM, ESP32 LEDC (for PWM)
**Storage**: NVS (for contact persistence)
**Testing**: Unity (Native ESP32 Framework version)
**Target Platform**: ESP32
**Project Type**: Embedded Firmware Fix
**Performance Goals**: Test suite compilation < 30s; 100% pass rate.
**Constraints**: No external Unity library (use framework built-in); PWM ramping 500-2000Hz.

## Constitution Check

| Principle | Gate Status | Implementation Plan |
|-----------|-------------|---------------------|
| I. Safety-First | ✅ PASSED | Fixing tests ensures the safety logic (Fall/Faint) is actually verifiable. |
| II. Reliability | ✅ PASSED | Resolving linker errors and API mismatches improves system stability. |
| III. TDD | ✅ PASSED | This entire plan is focused on making the TDD cycle functional again. |
| IV. Modularity | ✅ PASSED | Maintaining clear module boundaries (AlertManager, MotionMonitor). |
| V. Energy Efficiency| ✅ PASSED | MotionMonitor logic respects inactivity windows to allow for future sleep optimization. |

## Project Structure

### Documentation (this feature)

```text
specs/003-fix-test-failures/
├── plan.md              # This file
├── research.md          # Linker and API mismatch research
├── data-model.md        # Updated module interfaces
├── quickstart.md        # Test execution guide
└── tasks.md             # Derived from this plan
```

### Source Code (repository root)

```text
src/
├── modules/
│   ├── fall_detector/   # API update: processSensorData(ax, ay, az)
│   ├── comms/           # GSMService: formatSMSPayload(lat, lng)
│   ├── alert_manager/   # NEW: Audio ramping logic
│   └── motion_monitor/  # NEW: Stillness detection
├── main.cpp             # Integration
└── config.h             # Configuration constants
platformio.ini           # Remove redundant Unity lib
```

**Structure Decision**: Single project modular fix.

## Complexity Tracking

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| None | N/A | N/A |
