#ifndef CONFIG_H
#define CONFIG_H

// --- Fall Detection ---
#define FALL_THRESHOLD      2.5f    // Magnitude in G
#define STILLNESS_VARIANCE  0.05f   // Max variance for "still" state
#define STILLNESS_THRESHOLD 0.2f    // G-force threshold for "still"

// --- Faint Detection ---
#define FAINT_TIMEOUT_MS    300000 // 5 minutes in ms

// --- Alert Timing ---
#define PRE_ALERT_DURATION_MS 15000 // 15 seconds in ms
#define SOS_LONG_PRESS_MS     5000 // 5 seconds in ms
#define ALERT_DURATION_MS     15000 // 15 seconds

// --- Audio (Buzzer) ---
#define BUZZER_PIN          13
#define BUZZER_PWM_CHAN     0
#define BUZZER_FREQ_START   500     // Hz
#define BUZZER_FREQ_END     2000    // Hz

// --- GSM ---
#define MAX_PERSONAL_CONTACTS 3

#endif // CONFIG_H
