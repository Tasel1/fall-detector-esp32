# Feature Specification: Smart Watch with Fall Detection

**Feature Branch**: `001-fall-detection-watch`  
**Created**: 2026-03-25  
**Status**: Draft  
**Input**: User description: "Разработать устройство – умные часы, которые отслеживают внезапное падение и вызывают экстренные службы. Детекция падения по акселерометру MPU6050, при падении – 60-секундный таймер, если кнопка не нажата – отправка SMS через GSM. Также ручной вызов долгим нажатием кнопки. Экран OLED для отображения статуса. Опционально GPS для координат. Энергосбережение."

## Clarifications

### Session 2026-03-25
- Q: How many emergency contacts should the system support? → A: Sequential list, starting with emergency services.
- Q: Should the system also support voice calls for personal contacts? → A: SMS Only for personal contacts.

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Automatic Fall Detection (Priority: P1)

As a wearer, I want the device to automatically detect when I have fallen and start a countdown, so that help can be summoned if I am unable to do so myself.

**Why this priority**: This is the core life-saving feature of the device.

**Independent Test**: Can be tested by simulating a fall (dropping the device onto a soft surface) and observing if the countdown starts.

**Acceptance Scenarios**:

1. **Given** the device is in monitoring mode, **When** a fall is detected by the accelerometer, **Then** the OLED display shows a warning and a 60-second countdown begins.
2. **Given** a countdown is active, **When** the countdown reaches zero, **Then** the device sends an emergency SMS via the GSM module.

---

### User Story 2 - Manual Cancellation (Priority: P1)

As a wearer, I want to be able to cancel an emergency alert if the fall was minor or a false alarm, so that I don't unnecessarily bother emergency services.

**Why this priority**: Essential to prevent false alarms from overwhelming contacts or services.

**Independent Test**: Trigger a fall detection and press the physical button before the 60-second timer expires.

**Acceptance Scenarios**:

1. **Given** an emergency countdown is active, **When** the wearer presses the button once, **Then** the countdown is stopped, and the device returns to normal monitoring mode.

---

### User Story 3 - Manual Emergency Call (Priority: P2)

As a wearer, I want to be able to manually trigger an emergency alert at any time, even if a fall wasn't detected, so that I can call for help in other emergencies.

**Why this priority**: High value for user safety in non-fall related emergencies (e.g., heart attack, feeling threatened).

**Independent Test**: Long-press the button and verify if the emergency SMS is sent.

**Acceptance Scenarios**:

1. **Given** the device is on, **When** the wearer performs a long-press on the button, **Then** an emergency SMS is sent immediately (bypassing the countdown).

---

### User Story 4 - Location Awareness (Priority: P3)

As a wearer, I want my emergency alerts to include my GPS coordinates, so that rescuers can find me quickly.

**Why this priority**: Significantly improves the effectiveness of the rescue operation.

**Independent Test**: Trigger an alert and verify if the sent SMS contains a Google Maps link or coordinates.

**Acceptance Scenarios**:

1. **Given** GPS is enabled and has a signal, **When** an emergency SMS is sent, **Then** a clickable Google Maps link containing the current latitude and longitude is included in the message text.

---

- **FR-015**: System MUST alert the wearer via OLED and buzzer when battery level drops below 10%.
- **FR-016**: System MUST disable optional WiFi and GPS monitoring when in critical low-battery state (<10%) to preserve power for core fall detection and GSM alerts.
- **FR-007**: System MUST include GPS coordinates in the SMS as a clickable Google Maps link if a valid GPS signal is available.

### Edge Cases

- **No GSM Signal**: How does the system handle failed SMS delivery? (Should retry or display status).
- **No GPS Lock**: How does the system handle alerts when coordinates are unavailable? (Should send alert without coordinates).
- **Low Battery**: System MUST alert wearer and enter power-save mode (disabling non-essential modules).

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: System MUST monitor accelerometer data continuously to identify fall patterns.
- **FR-002**: System MUST display a clear visual countdown on the OLED screen when a fall is detected.
- **FR-003**: System MUST provide both audible (buzzer) and haptic (vibration) feedback during the countdown.
- **FR-004**: System MUST allow immediate cancellation of the countdown via a single button press.
- **FR-005**: System MUST alert a prioritized sequential list of contacts (Emergency Services first, then personal contacts) when the countdown expires.
- **FR-010**: System MUST attempt two (2) consecutive voice calls to emergency services (112) if the call is not answered. Regardless of the 112 call outcome, the system MUST proceed to alert all personal contacts via SMS.
- **FR-011**: System MUST allow configuration of the pre-defined TTS message and emergency contact list.
- **FR-012**: System MUST support Bluetooth Low Energy (BLE) as the primary protocol for connecting to the companion mobile application.
- **FR-014**: System MAY support WiFi as an optional connectivity method for secondary configuration or data sync.
- **FR-013**: System MUST provide a secure mechanism for updating device settings via the mobile application.

### Key Entities *(include if feature involves data)*

- **Emergency Contacts**: A prioritized sequential list containing one primary emergency service (e.g., 112) and up to 3 personal phone numbers.
- **Device Settings**: A collection of configurable parameters (contacts, TTS message, sensitivity, sleep intervals) stored in non-volatile memory.
- **Alert Event**: A record of a detected fall or manual SOS trigger, including time and (if available) coordinates.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: Fall detection algorithm identifies 95% of simulated falls.
- **SC-002**: Emergency SMS is sent within 5 seconds of the countdown reaching zero (given signal availability).
- **SC-003**: Battery life exceeds 24 hours of continuous monitoring on a single charge.
- **SC-004**: Manual SOS trigger responds to long-press within 500ms of the 3-second threshold being met.
- **SC-005**: Device configuration updates via the mobile app are applied within 2 seconds of the "Save" action.

## Assumptions

- **Companion App**: A functional mobile application exists to manage device configuration via WiFi/BLE.
- **Standard Fall Profile**: Falls follow typical acceleration patterns (high impact followed by relative inactivity).
- **Hardware Availability**: ESP32, MPU6050, SSD1306, and SIM800L are correctly wired and functional.
- **Mixed Alert Method**: Emergency services receive a voice call (TTS), while personal contacts receive SMS.
 a voice call, for simplicity and reliability in low-signal areas.
rrectly wired and functional.
- **Mixed Alert Method**: Emergency services receive a voice call (TTS), while personal contacts receive SMS.
 a voice call, for simplicity and reliability in low-signal areas.
