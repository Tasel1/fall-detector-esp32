# Feature Specification: Fix Test Failures

**Feature Branch**: `003-fix-test-failures`  
**Created**: 2026-03-25  
**Status**: Draft  
**Input**: User description: "исправить все ошибки после тестирования командой pio test я записал все ошибки в файл @error.md"

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Resolve Build and Linker Errors (Priority: P1)

As a developer, I want the test suite to compile and link without errors, so that I can verify the functionality of the system.

**Why this priority**: Build failures block all verification and deployment.

**Independent Test**: Run `pio test` and verify that the "multiple definition" and "undefined reference" errors are gone.

**Acceptance Scenarios**:

1. **Given** the current project configuration, **When** I run `pio test`, **Then** the linker should not report multiple definitions of Unity functions.
2. **Given** the source code structure, **When** I run `pio test`, **Then** the linker should find all references to `FallDetector`, `AlertManager`, `MotionMonitor`, and other modules.

---

### User Story 2 - Fix API Mismatches in Tests (Priority: P1)

As a developer, I want the test code to align with the actual implementation APIs, so that tests reflect the real system behavior.

**Why this priority**: Compilation errors in tests prevent them from running.

**Independent Test**: Verify `test_comms.cpp` compiles successfully.

**Acceptance Scenarios**:

1. **Given** the `GSMService::formatSMSPayload` implementation taking floats, **When** the test calls it, **Then** it should use the correct argument types (floats instead of strings).

---

### User Story 3 - Successful Test Execution (Priority: P2)

As a developer, I want all 7 tests to pass, so that I am confident in the system's reliability.

**Why this priority**: Passing tests are the ultimate indicator of success.

**Independent Test**: Run `pio test` and see "7 succeeded".

**Acceptance Scenarios**:

1. **Given** all fixes are applied, **When** I run `pio test`, **Then** all 7 test cases should report "PASSED".

---

### Edge Cases

- **Partial Fixes**: What if Unity conflict is fixed but linker errors remain? (Must continue fixing until all are resolved).
- **Regression**: Fixing tests shouldn't break the main application build.

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: System MUST resolve Unity library conflicts in `platformio.ini` by removing the redundant `Unity` dependency from `lib_deps`.
- **FR-002**: System MUST ensure that modules in `src/modules/` are correctly recognized by the PlatformIO test runner (likely by adjusting `test_build_src` or including headers/sources properly).
- **FR-003**: System MUST update `test_comms.cpp` to match the `GSMService` API (passing floats for coordinates).
- **FR-004**: System MUST ensure all 7 test suites (`test_fall_detector`, `test_comms`, `test_ui`, `test_alert_manager`, `test_power`, `test_hil`, `test_motion_monitor`) run to completion.

### Key Entities *(include if feature involves data)*

- **Test Suite**: A collection of unit tests for a specific module.
- **PlatformIO Config**: The `platformio.ini` file governing the build process.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: `pio test` command returns exit code 0.
- **SC-002**: Summary report shows 7/7 tests succeeded.
- **SC-003**: Compilation time for tests is under 30 seconds.

## Assumptions

- **Existing Logic is Correct**: We assume the logic in `src/` is correct and the failures are primarily due to build system configuration and test code mismatches.
- **Environment**: The xtensa-esp32-elf toolchain is correctly installed.
