# Quickstart: Enhanced Features Testing

## Testing Faint Detection
1.  Place the device on a flat, stable surface.
2.  Wait for 5 minutes (`FAINT_TIMEOUT`).
3.  Verify the buzzer starts a low-frequency tone that ramps up in pitch and volume over 15 seconds.
4.  Press the SOS button briefly within the 15-second window to cancel.

## Testing Immediate SOS
1.  In any mode (Monitoring or Pre-alert), press and hold the SOS button.
2.  Maintain the press for 10 seconds (`SOS_LONG_PRESS`).
3.  Verify the device immediately enters `SOS_ALERT` state, skipping the Pre-alert phase.

## Testing PWM Ramping
1.  Trigger a fall (drop on cushion).
2.  Listen to the piezo buzzer during the 15-second Pre-alert.
3.  Confirm the audio increases in intensity (frequency and volume) every ~1.5 seconds.
