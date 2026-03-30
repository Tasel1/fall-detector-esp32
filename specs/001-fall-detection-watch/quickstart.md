# Quickstart: Fall Detector Watch Development

## Hardware Setup
1.  Connect the ESP32 to the following modules:
    - **MPU6050**: SDA (GPIO 21), SCL (GPIO 22)
    - **SSD1306 OLED**: SDA (GPIO 21), SCL (GPIO 22) - Shared I2C bus
    - **SIM800L**: TX (GPIO 17), RX (GPIO 16) - UART2
    - **Buzzer/Vibrator**: GPIO 13, GPIO 12
    - **SOS Button**: GPIO 4 (Internal Pullup)
2.  Insert a valid micro-SIM card (2G capable) into the SIM800L module.
3.  Ensure the SIM800L has a dedicated 3.7V-4.2V power source (Li-Po battery) capable of 2A peaks.

## Build and Flash
1.  Install [PlatformIO](https://platformio.org/).
2.  Clone the repository and open the project folder.
3.  Select the `esp32dev` environment.
4.  Run `pio run -t upload` to flash the firmware.
5.  Open the Serial Monitor at 115200 baud to view logs.

## Testing
1.  **Unit Tests**: Run `pio test` to execute unit tests on the host or target.
2.  **Manual Test**: 
    - Simulate a fall by dropping the device on a cushion.
    - Observe the OLED countdown and buzzer/vibration alerts.
    - Long-press the button (>3s) to trigger a manual SOS.
    - Cancel a triggered alert by pressing the button once within 60s.
