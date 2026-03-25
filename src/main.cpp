#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int buttonCancelPin = 18;
const int ledPin = 19;
const int buttonFallSimPin = 23;

bool fallDetected = false;
unsigned long fallTime = 0;
const unsigned long cancelWindow = 60000;
bool callMade = false;
const float accelThreshold = 2.5;

unsigned long pressStart = 0;
bool wasPressed = false;
const unsigned long longPressTime = 10000;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
  pinMode(buttonCancelPin, INPUT_PULLUP);
  pinMode(buttonFallSimPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("System ready");
}

float getTotalAcceleration() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;
  return sqrt(ax_g*ax_g + ay_g*ay_g + az_g*az_g);
}

bool checkFall() {
  return getTotalAcceleration() > accelThreshold;
}

void loop() {
  bool nowPressed = (digitalRead(buttonCancelPin) == LOW);
  if (nowPressed && !wasPressed) pressStart = millis();
  if (!nowPressed && wasPressed) {
    unsigned long pressDuration = millis() - pressStart;
    if (fallDetected && pressDuration < 3000) {
      Serial.println("CALL_CANCELLED_BY_USER");
      fallDetected = false;
      callMade = false;
      digitalWrite(ledPin, LOW);
    } else if (!fallDetected && pressDuration >= longPressTime) {
      Serial.println("MANUAL_EMERGENCY_CALL");
      for (int i=0; i<5; i++) {
        digitalWrite(ledPin, HIGH); delay(200);
        digitalWrite(ledPin, LOW); delay(200);
      }
    }
  }
  wasPressed = nowPressed;

  static bool lastSimState = HIGH;
  bool simNow = (digitalRead(buttonFallSimPin) == LOW);
  if (simNow && !lastSimState && !fallDetected) {
    fallDetected = true;
    fallTime = millis();
    callMade = false;
    digitalWrite(ledPin, HIGH);
    Serial.println("SIMULATED_FALL_DETECTED! Press cancel button within 60 sec");
  }
  lastSimState = simNow;

  if (fallDetected) {
    if (!callMade && (millis() - fallTime >= cancelWindow)) {
      Serial.println("AUTOMATIC_EMERGENCY_CALL");
      callMade = true;
      digitalWrite(ledPin, HIGH);
      static unsigned long resetTime = 0;
      if (resetTime == 0) resetTime = millis() + 30000;
      if (millis() >= resetTime) {
        fallDetected = false;
        callMade = false;
        digitalWrite(ledPin, LOW);
        resetTime = 0;
      }
    }
    return;
  }

  if (checkFall()) {
    fallDetected = true;
    fallTime = millis();
    callMade = false;
    digitalWrite(ledPin, HIGH);
    Serial.println("FALL_DETECTED! Press cancel button within 60 sec");
  }

  delay(50);
}
