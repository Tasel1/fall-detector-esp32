# Data Model: NVS and BLE Schema

## NVS Storage (Persistent Settings)

| Key | Type | Description |
|-----|------|-------------|
| `contacts` | Blob (Serialized JSON/Binary) | Prioritized list of phone numbers (up to 5) |
| `tts_msg` | String (Max 128 chars) | The message to play during emergency calls |
| `sensitivity` | Float | Fall detection threshold (default: 2.5g) |
| `timer_val` | Integer | Cancellation timer duration in seconds (default: 60) |
| `wifi_ssid` | String | Optional WiFi SSID |
| `wifi_pass` | String | Optional WiFi Password |

## BLE Services and Characteristics

### Device Configuration Service (`UUID: 0xFD01`)

| Characteristic | UUID | Properties | Description |
|----------------|------|------------|-------------|
| **Contact List** | `0xFD11` | Read/Write | Serialized contact list |
| **TTS Message** | `0xFD12` | Read/Write | Pre-defined voice alert message |
| **Settings** | `0xFD13` | Read/Write | Sensitivity and timer values |
| **Command** | `0xFD14` | Write | Execute actions (e.g., Reset, Start Test Alert) |

### Device Status Service (`UUID: 0xFD02`)

| Characteristic | UUID | Properties | Description |
|----------------|------|------------|-------------|
| **Battery Level** | `0x2A19` (SIG Standard) | Read/Notify | Current battery percentage |
| **GSM Status** | `0xFD21` | Read/Notify | Signal strength and network registration |
| **GPS Fix** | `0xFD22` | Read/Notify | Latitude, Longitude, and Lock status |
| **Last Alert** | `0xFD23` | Read | Timestamp and cause of last alert |
