<!--
Sync Impact Report:
- Version change: 0.0.0 → 1.0.0
- List of modified principles:
  - Initialized with 5 principles: Safety, Reliability, TDD, Modularity, Energy Efficiency.
- Added sections:
  - Hardware & Environment (ESP32, MPU6050, OLED, GSM)
  - Development Workflow & Quality Gates
- Removed sections: None (initialized from template)
- Templates requiring updates:
  - .specify/templates/plan-template.md (✅ aligned)
  - .specify/templates/spec-template.md (✅ aligned)
  - .specify/templates/tasks-template.md (✅ aligned)
- Follow-up TODOs: None.
-->

# Fall Detector ESP32 Constitution

## Core Principles

### I. Safety-First (NON-NEGOTIABLE)
The primary function is life-saving. Fall detection algorithms MUST prioritize sensitivity (minimizing false negatives) while maintaining reasonable specificity. Emergency alerts via GSM MUST be redundant and verified. Failure to send an alert during a detected fall is a critical system failure.

### II. Reliability & Fault Tolerance
The device operates in unpredictable environments. The system MUST handle hardware sensor glitches (MPU6050 noise), connectivity drops (GSM/GPRS), and power fluctuations gracefully. Watchdog timers MUST be employed to recover from software hangs.

### III. Test-Driven Development (TDD)
Logic-heavy components (fall detection algorithms, state machines) MUST be developed using TDD. Hardware-abstracted unit tests MUST be written before implementation. Red-Green-Refactor cycle is the mandatory workflow for all business logic.

### IV. Modularity & Hardware Abstraction
Code MUST be decoupled from specific hardware pins and registers where possible. Use Driver/Service patterns to abstract the MPU6050, OLED, and GSM module. This ensures testability on non-ESP32 hardware (native tests) and simplifies future component swaps.

### V. Energy Efficiency
As a wearable device, battery life is critical. The system MUST utilize ESP32 deep sleep modes and sensor interrupts. MPU6050 FIFO and motion detection interrupts SHOULD be used to wake the MCU only when necessary. OLED updates MUST be minimized to save power.

## Hardware & Environment

The system is built on the ESP32 platform using the following components:
- **MCU**: ESP32 (WROOM/WROVER)
- **IMU**: MPU6050 (Accelerometer + Gyroscope) via I2C
- **Display**: SSD1306 OLED via I2C
- **Communication**: SIM800L or similar GSM module via UART
- **Input**: Physical SOS/Reset button

All firmware MUST be compatible with the PlatformIO build system as defined in `platformio.ini`.

## Development Workflow & Quality Gates

1. **Specification**: Every feature begins with a `/speckit.specify` call to define user stories and requirements.
2. **Planning**: Technical design and hardware constraints are documented via `/speckit.plan`.
3. **TDD Loop**:
   - Write failing test for the logic (e.g., fall detection math).
   - Implement minimal code to pass.
   - Refactor for modularity.
4. **Validation**: All PRs MUST pass existing unit tests and manual hardware-in-the-loop (HIL) verification for sensor accuracy.

## Governance

This Constitution is the supreme guide for the Fall Detector ESP32 project. All technical decisions and code reviews MUST align with these principles.

- **Amendments**: Changes to principles require a version bump and updated rationale in the Sync Impact Report.
- **Compliance**: Any deviation from principles (e.g., skipping TDD for a quick prototype) MUST be documented as a "Complexity Violation" in the implementation plan.
- **Guidance**: Use `.specify/templates/` for all project artifacts to maintain consistency.

**Version**: 1.0.0 | **Ratified**: 2026-03-25 | **Last Amended**: 2026-03-25
