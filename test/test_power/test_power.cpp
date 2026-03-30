#include <unity.h>
#include "modules/power/nvs_manager.h"

#include <ArduinoFake.h>

using namespace fakeit;

extern "C" void setUp(void) {
    ArduinoFakeReset();
}

extern "C" void tearDown(void) {}

void test_serialization_logic() {
    // Test contact list serialization
}

#ifdef ARDUINO
#include <Arduino.h>
void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_serialization_logic);
    UNITY_END();
}
void loop() {}
#else
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_serialization_logic);
    return UNITY_END();
}
#endif
