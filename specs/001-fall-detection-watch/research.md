# Research: Fall Detection and Hardware Integration

## Decision: Threshold-based Fall Detection Algorithm
**Rationale**: A simple threshold-based algorithm is most efficient for low-power operation on an ESP32. We will implement a 2.5g impact detection followed by a 2-second post-fall inactivity check (using gyroscope data). This approach minimizes false positives from walking or sudden movements while ensuring high sensitivity.
**Alternatives considered**: Neural Networks/AI (Too power-intensive for battery operation).

## Decision: GSM SIM800L for Alerts
**Rationale**: SIM800L is a cost-effective, widely available GSM module that supports both SMS and Voice. We will use the `TinyGSM` library for its abstraction over AT commands and its proven stability with ESP32.
**Alternatives considered**: SIM7000 (LTE-M/NB-IoT) - Rejected due to higher cost and limited 2G/3G network availability in target regions.

## Decision: BLE (NimBLE-Arduino) for Configuration
**Rationale**: Standard ESP32 BLE stacks consume significant memory. `NimBLE-Arduino` is a lighter, more memory-efficient alternative that will leave more RAM for the fall detection logic and GSM buffers.
**Alternatives considered**: Native BLE stack (Excessive memory usage); WiFi-only config (High power consumption).

## Decision: ESP32 NVS (Non-Volatile Storage)
**Rationale**: Using NVS for storing emergency contact lists and configuration parameters is more reliable and robust than using a file system (SPIFFS/LittleFS) for small data sets.
**Alternatives considered**: SD Card (Added hardware complexity); EEPROM library (Deprecated on ESP32).

## Decision: Deep Sleep and Interrupt-based Wakeup
**Rationale**: To meet the < 24-hour battery goal, the ESP32 must spend most of its time in deep sleep. We will use the MPU6050's "Motion Detection" interrupt to wake the ESP32 only when significant movement is detected.
**Alternatives considered**: Light sleep (Higher power usage); Continuous active monitoring (Too much power).
