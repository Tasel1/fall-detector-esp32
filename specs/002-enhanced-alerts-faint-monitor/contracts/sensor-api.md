# Sensor API Contract Update

## Fall Detector Module
The `FallDetector` class must handle 3-axis accelerometer data to accurately calculate magnitude and variance.

### Updated Method
`bool processSensorData(float accelX, float accelY, float accelZ);`

**Parameters:**
- `accelX`: Acceleration on X axis (m/s^2)
- `accelY`: Acceleration on Y axis (m/s^2)
- `accelZ`: Acceleration on Z axis (m/s^2)

**Return:**
- `true` if a fall event is triggered, `false` otherwise.

## Motion Monitor Module
The `MotionMonitor` class tracks stillness over time.

### Method
`bool isMotionless(float accelX, float accelY, float accelZ);`

**Returns:**
- `true` if variance is below threshold for more than `FAINT_TIMEOUT`.
