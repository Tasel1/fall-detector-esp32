# BLE Interface Contract

## Overview
Communication with the companion mobile application uses Bluetooth Low Energy (BLE). The ESP32 acts as a Peripheral, and the mobile application acts as a Central.

## Connection Protocol
1.  **Advertising**: The ESP32 advertises its name (e.g., "FallWatch-XXXX") and the Configuration Service UUID (`0xFD01`).
2.  **Authentication**: Simple passkey pairing (numeric comparison) is required for write operations.
3.  **Data Exchange**: Standard BLE Characteristic Read/Write/Notify operations as defined in `data-model.md`.

## Data Serialization (Binary Format)
To save memory, data is sent in a simple packed binary format.

### Contact List (`0xFD11`)
| Offset | Length | Description |
|--------|--------|-------------|
| 0 | 1 | Number of contacts (N) |
| 1 | 15 | Contact 1: UTF-8 Phone Number (Nul-terminated) |
| ... | ... | Contact N: UTF-8 Phone Number (Nul-terminated) |

### Settings (`0xFD13`)
| Offset | Length | Description |
|--------|--------|-------------|
| 0 | 4 | Sensitivity (Float, Little Endian) |
| 4 | 2 | Timer Value (Uint16, Little Endian) |
| 6 | 1 | Flags (0x01: WiFi Enable, 0x02: GPS Enable) |
