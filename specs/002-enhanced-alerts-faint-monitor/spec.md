# Feature Specification: Enhanced Alerts and Faint Detection

**Feature Branch**: `002-enhanced-alerts-faint-monitor`  
**Created**: 2026-03-25  
**Status**: Draft  
**Input**: User description: "Добавить следующие требования: - Звуковая индикация через пьезо-зуммер, с возможностью нарастания громкости/частоты. - Предварительный режим при детекции падения: 15-секундный таймер с нарастающим звуком. Отмена коротким нажатием кнопки. - Функция мониторинга неподвижности (Faint Detection): если отсутствие движения > 5 минут, запускается предварительный режим с нарастающим звуком. Отмена аналогично. - Долгое нажатие (>10 сек) в любом режиме (кроме активного вызова) — немедленный SOS. - Все параметры (пороги, время неподвижности, длительность предупреждения) настраиваются через конфигурационный файл config.h."

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Automatic Faint Detection (Priority: P1)

As a wearer, I want the device to detect if I have been motionless for a long period, so that help can be called even if I didn't fall but am unconscious or unable to move.

**Why this priority**: Critical life-safety extension beyond simple fall detection.

**Independent Test**: Leave the device perfectly still for the configured faint timeout (e.g., 5 minutes) and verify that the pre-alert starts.

**Acceptance Scenarios**:

1. **Given** the device is in monitoring mode, **When** no significant motion is detected for > 5 minutes, **Then** the device enters "Pre-alert" mode.
2. **Given** the device is in "Pre-alert" mode due to inactivity, **When** the 15-second timer expires without cancellation, **Then** the device triggers the emergency alert sequence.

---

### User Story 2 - Pre-alert Cancellation (Priority: P1)

As a wearer, I want to be able to quickly cancel a pre-alert triggered by false fall detection or normal inactivity, so that I don't trigger false emergency calls.

**Why this priority**: Essential for UX to prevent false alarms from escalating to emergency services.

**Independent Test**: Trigger a pre-alert (via fall or inactivity) and press the button once within 15 seconds.

**Acceptance Scenarios**:

1. **Given** the device is in "Pre-alert" mode (buzzer sounding), **When** the wearer performs a short button press, **Then** the alert is canceled, sound stops, and the device returns to normal monitoring.

---

### User Story 3 - Immediate SOS (Priority: P2)

As a wearer, I want to be able to trigger an immediate emergency alert by holding the button for a long time, regardless of the current mode, so that I can call for help in extreme situations.

**Why this priority**: Reliable manual override for emergencies.

**Independent Test**: Hold the button for 10 seconds and verify that the emergency alert sequence starts immediately (bypassing pre-alerts).

**Acceptance Scenarios**:

1. **Given** the device is on (and not in an active emergency call), **When** the wearer holds the button for > 10 seconds, **Then** the device immediately starts the emergency alert sequence.

---

### User Story 4 - Dynamic Audio Feedback (Priority: P3)

As a wearer, I want the alert sounds to get louder or more urgent over time, so that I am more likely to notice the pre-alert before it escalates.

**Why this priority**: Increases the chance of wearer intervention for false alarms.

**Independent Test**: Observe the pre-alert sound for the full 15-second duration.

**Acceptance Scenarios**:

1. **Given** the device is in "Pre-alert" mode, **When** the timer progresses, **Then** the buzzer volume or frequency increases incrementally until the timer expires.

---

### Edge Cases

- **Motion during Pre-alert**: Does moving the watch cancel a faint-detection pre-alert? (Requirement says button press is the cancel action).
- **Multiple Triggers**: If a fall is detected while already in a faint-detection pre-alert, does the timer reset? (Should maintain the earliest trigger or most critical).
- **Button Jam**: What happens if the button is stuck in a pressed state? (Should handle debouncing and state transitions carefully).

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: System MUST monitor accelerometer variance to detect "stillness" or "inactivity".
- **FR-002**: System MUST trigger a Pre-alert mode if inactivity exceeds the configured `FAINT_TIMEOUT`.
- **FR-003**: System MUST trigger a Pre-alert mode immediately upon detecting a fall.
- **FR-004**: Pre-alert mode MUST last for `PRE_ALERT_DURATION` (default 15s) before escalating to a full emergency alert.
- **FR-005**: System MUST use a piezo buzzer to provide audio feedback during Pre-alert.
- **FR-006**: Audio feedback MUST increase in volume via PWM control over the duration of the Pre-alert timer to signal increasing urgency.
- **FR-007**: System MUST cancel any active Pre-alert upon a short button press.
- **FR-008**: System MUST trigger an immediate SOS (bypassing Pre-alert) if the button is held for > 10 seconds.
- **FR-009**: Immediate SOS via long-press MUST be disabled if an emergency voice call is currently active.
- **FR-010**: All timing and sensitivity parameters MUST be defined as configurable constants in a central `config.h` file.

### Key Entities *(include if feature involves data)*

- **Motion State**: Current state of activity (Moving, Still).
- **Alert Timer**: Countdown timer for Pre-alert and SOS escalation.
- **Config Profile**: Set of parameters (Thresholds, Timeouts) loaded from `config.h`.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: Faint detection triggers within +/- 5 seconds of the 5-minute inactivity mark.
- **SC-002**: Pre-alert audio intensity increases in at least 3 distinct steps over the 15-second duration.
- **SC-003**: Short button press cancels Pre-alert within 200ms of release.
- **SC-004**: Long-press SOS triggers within 500ms of the 10-second threshold being met.

## Assumptions

- **Piezo Capability**: The piezo buzzer is capable of distinct frequency changes (tones) or volume changes via PWM.
- **Continuous Power**: The device has sufficient power to run the buzzer at high intensity during pre-alerts.
- **Button Reliability**: The physical button can reliably distinguish between short presses, 3s presses (previous SOS), and 10s presses.
