# Quickstart: Verifying Test Fixes

## 1. Environment Preparation
Ensure `platformio.ini` is updated:
- `lib_ignore = Unity` is present.
- `test_build_src = yes` is enabled.
- Linker flag `-Wl,--allow-multiple-definition` is active.

## 2. Execute Tests
Run the entire suite from the terminal:
```bash
pio test
```

## 3. Expected Success Criteria
- **7/7 tests pass build stage**.
- **Linker errors** (multiple definition) are resolved.
- **FallDetector** tests verify 3-axis logic.
- **MotionMonitor** tests verify variance calculation.
- **GSMService** formatting uses Google Maps links.

## 4. Manual Verification (Serial)
Observe transition logs:
- `DEBUG: Fall Detected -> PRE_ALERT`
- `DEBUG: Faint Detected -> PRE_ALERT`
- `Audio Alert Started`
- `Cancel latency: XX ms`
