# Tasks: Smart Watch with Fall Detection

**Input**: Design documents from `/specs/001-fall-detection-watch/`
**Prerequisites**: plan.md, spec.md, research.md, data-model.md, contracts/

**Tests**: TDD is MANDATORY per Constitution Principle III. All logic-heavy components must have unit tests.

**Organization**: Tasks are grouped by user story to enable independent implementation and testing.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Parallelizable task
- **[Story]**: User story mapping ([US1], [US2], etc.)
- Paths follow the modular structure defined in plan.md

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and PlatformIO environment setup

- [X] T001 Create project folder structure (`src/modules/{sensors,fall_detector,ui,comms,power}`)
- [X] T002 Initialize `platformio.ini` with ESP32 environment and library dependencies
- [X] T003 Configure Unity test framework in `test/` directory for TDD

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core hardware abstraction and persistent storage

- [X] T004 [P] Implement NVS storage manager for contacts and settings in `src/modules/power/nvs_manager.cpp`
- [X] T005 [P] Implement deep sleep and interrupt wakeup logic in `src/modules/power/power_mgmt.cpp`
- [X] T006 Create global state machine and task scheduler in `src/main.cpp`
- [X] T007 [P] Implement I2C bus initialization for MPU6050 and OLED in `src/modules/sensors/i2c_bus.cpp`

**Checkpoint**: Hardware foundation ready - User Story implementation can begin

---

## Phase 3: User Story 1 - Automatic Fall Detection (Priority: P1) 🎯 MVP

**Goal**: Detect fall via MPU6050, run 60s timer, and send emergency SMS via SIM800L

**Independent Test**: Simulate a fall; verify OLED countdown starts and SIM800L sends SMS after 60s.

### Tests for User Story 1
- [X] T008 [P] [US1] Write unit tests for fall detection algorithm in `tests/unit/test_fall_detector.cpp`
- [X] T009 [P] [US1] Write unit tests for SMS payload formatting in `tests/unit/test_comms.cpp`

### Implementation for User Story 1
- [X] T010 [P] [US1] Implement MPU6050 driver and data sampling in `src/modules/sensors/imu_sensor.cpp`
- [X] T011 [US1] Implement threshold-based fall detection algorithm in `src/modules/fall_detector/fall_detector.cpp`
- [X] T012 [P] [US1] Implement GSM SIM800L initialization and SMS sending in `src/modules/comms/gsm_service.cpp`
- [X] T013 [US1] Implement basic OLED status and countdown display in `src/modules/ui/display_service.cpp`
- [X] T014 [US1] Integrate fall detection event with 60s timer logic in `src/main.cpp`

**Checkpoint**: US1 (MVP) fully functional and testable

---

## Phase 4: User Story 2 - Manual Cancellation (Priority: P1)

**Goal**: Cancel active emergency alert via physical button press

**Independent Test**: Trigger fall; press button during countdown; verify OLED returns to monitoring status.

### Implementation for User Story 2
- [X] T015 [P] [US2] Implement button interrupt handler with debouncing in `src/modules/sensors/button_sensor.cpp`
- [X] T016 [US2] Implement countdown cancellation logic in `src/main.cpp`
- [X] T017 [US2] Update OLED UI to show "Alert Canceled" status in `src/modules/ui/display_service.cpp`

---

## Phase 5: User Story 3 - Manual Emergency Call & Sequential Alerts (Priority: P2)

**Goal**: Long-press button for SOS; sequential alert (112 voice call with TTS, then personal SMS)

**Independent Test**: Long-press button; verify immediate 112 call start followed by personal SMS fallback.

### Implementation for User Story 3
- [X] T017a [P] [US3] Write unit tests for sequential alert manager and TTS payload logic in `tests/unit/test_alert_manager.cpp`
- [X] T018 [US3] Implement long-press (>3s) detection in `src/modules/sensors/button_sensor.cpp`
- [X] T019 [P] [US3] Implement voice call initiation and TTS message playback in `src/modules/comms/gsm_service.cpp`
- [X] T020 [US3] Implement sequential alert manager (Retry 2x for 112, then SMS) in `src/modules/comms/alert_manager.cpp`
- [X] T021 [US3] Implement buzzer and vibration feedback patterns in `src/modules/ui/haptic_service.cpp`

---

## Phase 6: User Story 4 - Location Awareness (Priority: P3)

**Goal**: Include GPS coordinates in SMS and Voice TTS messages

**Independent Test**: Trigger alert; verify SMS contains a valid Google Maps link with current coordinates.

### Implementation for User Story 4
- [X] T021a [P] [US4] Write unit tests for GPS coordinate parsing and Google Maps link generation in `tests/unit/test_comms.cpp`
- [X] T022 [P] [US4] Implement GPS Neo-6M driver and coordinate parsing in `src/modules/sensors/gps_sensor.cpp`
- [X] T023 [US4] Update SMS and TTS payload generators to include coordinates in `src/modules/comms/alert_payloads.cpp`

---

## Phase 7: User Story 5 - BLE Configuration (Priority: P3)

**Goal**: Sync contacts and settings via BLE NimBLE service

**Independent Test**: Connect via BLE scanner; write new phone number; verify NVS update after restart.

### Implementation for User Story 5
- [X] T023a [P] [US5] Write unit tests for binary serialization and NVS persistence in `tests/unit/test_power.cpp`
- [X] T023b [P] [US5] Implement BLE passkey authentication/pairing mechanism in `src/modules/comms/ble_service.cpp` (FR-013)
- [X] T023c [P] [US5] Implement optional WiFi connectivity and data sync handler in `src/modules/comms/wifi_service.cpp` (FR-014)
- [X] T024 [P] [US5] Implement NimBLE service with configuration characteristics in `src/modules/comms/ble_service.cpp`
- [X] T025 [US5] Implement binary serialization/deserialization for BLE data in `src/modules/power/nvs_manager.cpp`

---

## Phase 8: Polish & Cross-Cutting Concerns

**Purpose**: Final optimization and HIL validation

- [X] T026 [P] Implement battery voltage monitoring and low-battery alerts in `src/modules/power/power_mgmt.cpp`
- [X] T027 [P] Perform Hardware-in-the-Loop (HIL) accuracy testing in `tests/hil/test_detection.cpp`
- [X] T028 Optimize main loop timing and energy consumption profiles

---

## Dependencies & Execution Order

### Phase Dependencies
1. **Setup (Phase 1)**: No dependencies.
2. **Foundational (Phase 2)**: Depends on Phase 1 completion.
3. **User Story 1 (Phase 3)**: Depends on Phase 2 (HAL/NVS).
4. **User Stories 2-5**: Can proceed in parallel after Phase 3, though sequential is recommended for the prototype.

### Implementation Strategy
- **MVP**: Complete Phases 1, 2, and 3. This delivers a device that detects falls and sends SMS.
- **Incremental**: Add US2 (Cancellation) immediately after US1 for safety.
- **Final**: Add US3 (Voice/TTS), US4 (GPS), and US5 (BLE) as secondary features.

---

## Parallel Opportunities
- T004, T005, and T007 (HAL modules) can be developed simultaneously.
- T010 (IMU) and T012 (GSM) can be developed in parallel by different team members.
- Unit tests (T008, T009) can be written while sensor drivers are being implemented.
