#include <unity.h>
#include "modules/sensors/button_sensor.h"

#include <ArduinoFake.h>

using namespace fakeit;

extern "C" void setUp(void) {
    ArduinoFakeReset();
}

extern "C" void tearDown(void) {}

void test_button_press_logic() {
    // Mocking or testing internal logic if possible
    // For now, placeholder for debouncing logic tests
}

#ifdef ARDUINO
#include <Arduino.h>
void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_button_press_logic);
    UNITY_END();
}
void loop() {}
#else
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_button_press_logic);
    return UNITY_END();
}
#endif
