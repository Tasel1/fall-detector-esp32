#include <unity.h>
#include "modules/motion_monitor/motion_monitor.h"
#include "config.h"

#include <ArduinoFake.h>

using namespace fakeit;

extern "C" void setUp(void) {
    ArduinoFakeReset();
    When(Method(ArduinoFake(), millis)).AlwaysReturn(0);
}

extern "C" void tearDown(void) {}

void test_stillness_detection() {
    MotionMonitor monitor;
    
    // Заполняем окно "движением" (чередуем 1.0G и 2.0G для создания дисперсии)
    for (int i = 0; i < 5; i++) {
        monitor.update(1.0f); 
        monitor.update(2.0f); 
    }
    // Дисперсия будет около 0.25, что больше порога 0.05
    TEST_ASSERT_FALSE(monitor.isMotionless());
    
    // Заполняем окно "покоем" (стабильные 1.0G)
    for (int i = 0; i < 10; i++) {
        monitor.update(1.0f);
    }
    // Дисперсия 0.0, что меньше порога 0.05
    TEST_ASSERT_TRUE(monitor.isMotionless());
}

#ifdef ARDUINO
#include <Arduino.h>
void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_stillness_detection);
    UNITY_END();
}
void loop() {}
#else
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_stillness_detection);
    return UNITY_END();
}
#endif
