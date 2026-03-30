# Tasks: Fix Test Failures

**Input**: Design documents from `/specs/003-fix-test-failures/`
**Prerequisites**: plan.md, spec.md, research.md, data-model.md

**Organization**: Tasks are grouped by logical phase to resolve build blockers first, followed by API alignment and new feature completion.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Parallelizable task
- **[Story]**: User story mapping ([US1], [US2], [US3])
- Paths follow the project structure defined in plan.md

---

## Phase 1: Setup (Build System Fixes)

**Purpose**: Resolve linker conflicts and environment mismatches

- [X] T001 [US1] Remove Unity dependency from `lib_deps` in `platformio.ini` to use built-in version
- [X] T002 [P] [US1] Create missing module directories if they don't exist: `src/modules/{alert_manager,motion_monitor}`
- [X] T003 [P] [US1] Add new constants (`BUZZER_PIN`, `FAINT_TIMEOUT_MS`, `ALERT_DURATION_MS`, etc.) to `src/config.h` (hardcoded `#define`, no NVS at this stage)

---

## Phase 2: Foundational (API Standardization)

**Purpose**: Align core module signatures with test expectations

- [X] T004 [US2] Update `FallDetector` signature to `processSensorData(float ax, float ay, float az)` in `src/modules/fall_detector/fall_detector.h`
- [X] T005 [US2] Implement `FallDetector::calculateMagnitude` helper in `src/modules/fall_detector/fall_detector.cpp`
- [X] T006 [US2] Update `GSMService::formatSMSPayload` to accept `float lat, float lng` in `src/modules/comms/gsm_service.h`
- [X] T007 [US2] Implement Google Maps link generation in `src/modules/comms/gsm_service.cpp`

---

## Phase 3: User Story 1 – Resolve Build and Linker Errors (Priority: P1)

**Goal**: Suite compiles and links without "multiple definition" or "undefined reference" errors

**Independent Test**: Run `pio test` and verify successful compilation of all suites.

- [X] T008 [US1] Fix `test/test_fall_detector/test_fall_detector.cpp` to use 3‑argument `processSensorData`
- [X] T009 [US1] Fix `test/test_comms/test_comms.cpp` to pass float arguments to `formatSMSPayload`
- [X] T010 [P] [US1] Add missing `FallDetector` constructor and implementation stubs to resolve undefined references

---

## Phase 4: User Story 2 – Fix API Mismatches in Tests (Priority: P1)

**Goal**: Test code correctly utilizes updated module interfaces

**Independent Test**: `test_comms` and `test_fall_detector` pass with real logic.

- [X] T011 [US2] Update `test/test_comms/test_comms.cpp` expected strings to match Google Maps format
- [X] T012 [US2] Update `test/test_fall_detector/test_fall_detector.cpp` to include magnitude calculation verification

---

## Phase 5: User Story 3 – Implement Missing Logic for Full Test Pass (Priority: P2)

**Goal**: Write tests (TDD) and then implement remaining logic to make all 7 tests pass

**Independent Test**: `pio test` reports 7/7 succeeded.

### Tests first (TDD) – write failing tests

- [X] T013 [P] [US3] Write/update unit tests for `AlertManager` ramping logic in `test/test_alert_manager/test_alert_manager.cpp`
- [X] T014 [P] [US3] Write/update unit tests for `MotionMonitor` stillness detection in `test/test_motion_monitor/test_motion_monitor.cpp`

### Implementation – make tests pass

- [X] T015 [US3] Implement `AlertManager` class with PWM ramping (frequency 500→2000 Hz over 15 s) in `src/modules/alert_manager/alert_manager.cpp`
- [X] T016 [US3] Implement `MotionMonitor` stillness logic (5‑minute timeout) in `src/modules/motion_monitor/motion_monitor.cpp`

---

## Phase 6: Polish & Integration

**Purpose**: Verify system integrity post-fix

- [X] T017 [US3] Integrate `MotionMonitor` and `AlertManager` into the main loop in `src/main.cpp`
- [X] T018 [P] **Fix remaining test suites**:
  - Update `test/test_ui/test_ui.cpp` to resolve Unity linker errors
  - Update `test/test_power/test_power.cpp` to resolve compilation issues
  - Update `test/test_hil/test_hil.cpp` to resolve compilation issues
- [X] T019 Run final full test suite (`pio test`) and verify exit code 0
- [X] T020 **Verify compilation time < 30 seconds** (SC-003) – measure `pio run` duration
- [X] T021 Update `quickstart.md` with the new test verification procedure

---

## Dependencies & Execution Order

### Phase Dependencies
1. **Setup (Phase 1)**: Must be completed first to allow compilation.
2. **Foundational (Phase 2)**: Prerequisite for resolving test mismatches.
3. **User Story 1 & 2 (Phases 3‑4)**: Can proceed in parallel after Phase 2.
4. **User Story 3 (Phase 5)**: Must follow TDD order – write tests (T013, T014) before implementation (T015, T016).
5. **Polish (Phase 6)**: After all core fixes are in place.

### Parallel Opportunities
- T002, T003 (Setup) can run together.
- T013, T014 (test writing) can be done simultaneously.
- T015, T016 (implementations) can be developed in parallel.
- T018 (test suite fixes) can be done in parallel with T017 and T019.

---

## Implementation Strategy

1. **Blocker Removal** (T001‑T003) – resolve Unity conflict and create module skeletons.
2. **API Alignment** (T004‑T007) – fix signatures and helper functions.
3. **Test Adaptation** (T008‑T012) – update existing tests to match new API.
4. **TDD for New Logic** (T013‑T016) – write tests, then implement missing classes.
5. **Complete Test Coverage** (T017‑T019) – integrate, fix remaining test suites, run full suite.
6. **Quality Assurance** (T020‑T021) – verify compilation time and update documentation.
