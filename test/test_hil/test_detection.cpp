#include <unity.h>
#include "modules/sensors/imu_sensor.h"
#include "modules/fall_detector/fall_detector.h"

#include <ArduinoFake.h>

using namespace fakeit;

extern "C" void setUp(void) {
    ArduinoFakeReset();
}

extern "C" void tearDown(void) {}

void test_physical_fall_sim() {
    // В HIL тестах мы просто проверяем, что вызов API работает
    FallDetector detector;
    // Эмуляция данных
    bool result = detector.processSensorData(0.0f, 0.0f, 9.81f);
    TEST_ASSERT_FALSE(result); // При 1G падения быть не должно
}

#ifdef ARDUINO
#include <Arduino.h>
void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_physical_fall_sim);
    UNITY_END();
}
void loop() {}
#else
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_physical_fall_sim);
    return UNITY_END();
}
#endif
