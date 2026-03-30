# Tasks: Enhanced Alerts and Faint Detection

**Input**: Design documents from `/specs/002-enhanced-alerts-faint-monitor/`
**Prerequisites**: plan.md, spec.md, research.md, data-model.md, contracts/

**Tests**: TDD is MANDATORY per Constitution Principle III. All logic-heavy components (3-axis magnitude, alert ramping, stillness detection) MUST have unit tests.

**Organization**: Tasks are grouped by user story to enable independent implementation and testing.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- All paths are relative to repository root

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and environment stabilization

- [X] T001 Fix Unity library conflict in `platformio.ini` (remove lib_deps Unity, use built-in)
- [X] T002 [P] Create project structure per implementation plan (`src/modules/{motion_monitor,alert_manager}`)
- [X] T003 [P] Configure `src/config.h` with new constants (alert duration, faint timeout, PWM pins)

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core API updates and state machine expansion (TDD focus)

- [X] T004 [P] Write unit tests for 3-axis acceleration magnitude calculation in `test/test_fall_detector/test_fall_detector.cpp`
- [X] T005 Implement 3-axis magnitude calculation in `src/modules/sensors/imu_sensor.cpp` (must pass T004)
- [X] T006 [P] Write unit tests for fall detection using 3-axis data in `test/test_fall_detector/test_fall_detector.cpp`
- [X] T007 Update `bool processSensorData(float ax, float ay, float az)` in `src/modules/fall_detector/fall_detector.cpp` (must pass T006)
- [X] T008 [P] Implement SSD1306 OLED display driver (clear, print) in `src/modules/ui/display_service.cpp`
- [X] T009 [P] Implement button debouncing and long/short press detection in `src/modules/sensors/button_sensor.cpp`
- [X] T010 Create state machine skeleton with new states (IDLE, PRE_ALERT, FAINT_DETECTED, CALL_ACTIVE, MANUAL_SOS) in `src/main.cpp`

**Checkpoint**: Foundation ready – baseline tests passing.

---

## Phase 3: User Story 1 – Automatic Faint Detection (Priority: P1) 🎯 MVP

**Goal**: Detect inactivity > 5 minutes and trigger Pre-alert

**Independent Test**: Leave device perfectly still; verify state transition to `PRE_ALERT` after `FAINT_TIMEOUT`.

### Tests for User Story 1
- [X] T011 [P] [US1] Write unit tests for `isMotionless()` stillness detection in `test/test_motion_monitor/test_motion_monitor.cpp`

### Implementation for User Story 1
- [X] T012 [P] [US1] Create `MotionMonitor` class with sliding window variance in `src/modules/motion_monitor/motion_monitor.h`
- [X] T013 [US1] Implement inactivity timer and `isMotionless()` logic in `src/modules/motion_monitor/motion_monitor.cpp` (must pass T011)
- [X] T014 [US1] Integrate `MotionMonitor::update()` into the main sampling loop in `src/main.cpp`

**Checkpoint**: Faint detection MVP fully functional and testable independently.

---

## Phase 4: User Story 2 – Pre-alert & Dynamic Audio (Priority: P1/P3)

**Goal**: 15s warning phase with ramping piezo volume/pitch

**Independent Test**: Trigger Pre-alert; verify buzzer ramps up in intensity over 15s.

### Tests for User Story 2
- [X] T015 [P] [US2] Write unit tests for PWM ramping algorithm in `test/test_alert_manager/test_alert_manager.cpp`

### Implementation for User Story 2
- [X] T016 [P] [US2] Create `AlertManager` with ESP32 `ledc` initialization in `src/modules/alert_manager/alert_manager.h`
- [X] T017 [US2] Implement frequency and volume ramping steps in `src/modules/alert_manager/alert_manager.cpp` (must pass T015)
- [X] T018 [US2] Integrate `AlertManager` start/stop with `PRE_ALERT` state in `src/main.cpp`

---

## Phase 5: User Story 3 – Cancellation & SOS Override (Priority: P1/P2)

**Goal**: Cancel alerts via button or trigger immediate 10s SOS

**Independent Test**: Trigger Pre-alert; short press to cancel. Hold 10s to trigger immediate SOS.

### Implementation for User Story 3
- [X] T019 [US3] Update button interrupt logic for 10s long-press detection in `src/modules/sensors/button_sensor.cpp`
- [X] T020 [US3] Implement immediate SOS logic in `src/main.cpp` (including FR-009 active call check)
- [X] T021 [US3] Implement cancellation transition from `PRE_ALERT` to `MONITORING` in `src/main.cpp`

---

## Phase 6: User Story 4 – GSM Integration & Coordinates (Priority: P2)

**Goal**: Real SMS sending with Google Maps link

**Independent Test**: Trigger alert; verify SMS contains valid coordinate link.

### Implementation for User Story 4
- [X] T022 [P] [US4] Implement `GSMService::formatSMSPayload` with lat/lng link in `src/modules/comms/gsm_service.cpp`
- [X] T023 [US4] Implement `setSOSLockout()` and `isSOSLocked()` in `src/modules/comms/gsm_service.cpp`
- [X] T024 [US4] Integrate call trigger logic with coordinate link in `src/main.cpp`

---

## Phase 7: User Story 5 – Low Battery & Power Saving (Priority: P3)

**Goal**: Power-save mode when battery < 10%

**Independent Test**: Simulate < 10% battery; verify GPS disabled and warning on OLED.

### Implementation for User Story 5
- [X] T025 [P] [US5] Implement low-battery detection (ADC reading) in `src/modules/power/power_mgmt.cpp`
- [X] T026 [US5] Implement power-save mode logic (disable modules, reduce volume) in `src/main.cpp`

---

## Phase 8: Polish & Cross-Cutting Concerns

**Purpose**: Final optimization and energy profiling

- [X] T027 [P] Verify SC-003: measure cancel latency (<200ms) and log result in `test/test_hil/test_latency.cpp`
- [X] T028 Optimize `MotionMonitor` sampling frequency to minimize power consumption
- [X] T029 Perform HIL validation for all scenarios in `quickstart.md`
- [X] T030 Update documentation and `README.md` with new feature details

---

## Dependencies & Execution Order

### Phase Dependencies
1. **Setup (Phase 1)**: No dependencies.
2. **Foundational (Phase 2)**: Depends on Phase 1 completion.
3. **User Story 1 (Phase 3)**: Depends on Phase 2 (HAL/IMU readiness).
4. **User Stories 2-5**: Depend on Phase 2 (HAL/State machine readiness).

### Implementation Strategy
- **MVP**: Complete Phases 1, 2, and 3. This enables faint detection.
- **Incremental**: Add US2 (Audio) and US3 (Cancellation) for feedback loops.
- **Final**: Add US4 (GSM) and US5 (Power) for operational readiness.

---

## Parallel Opportunities
- Setup tasks (T002, T003) can run together.
- T004 (Tests) and T008 (UI) can proceed simultaneously.
- US4 development can start once AlertManager/State skeleton is ready.
