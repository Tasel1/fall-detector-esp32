#include <unity.h>
#include "modules/alert_manager/alert_manager.h"
#include "config.h"

#include <ArduinoFake.h>

using namespace fakeit;

extern "C" void setUp(void) {
    ArduinoFakeReset();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char*))).AlwaysReturn();
    When(Method(ArduinoFake(), millis)).AlwaysReturn(0);
}

extern "C" void tearDown(void) {}

void test_alert_ramping_logic() {
    // Тест проверяет, что AlertManager инициализируется и принимает параметры
    TEST_ASSERT_TRUE(AlertManager::begin());
    
    // Эмуляция нарастания (проверяем отсутствие крэшей при расчетах)
    AlertManager::startAlert();
    AlertManager::updateAlert(0.0f); // 0%
    AlertManager::updateAlert(0.5f); // 50%
    AlertManager::updateAlert(1.0f); // 100%
    AlertManager::stop();
}

#ifdef ARDUINO
#include <Arduino.h>
void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_alert_ramping_logic);
    UNITY_END();
}
void loop() {}
#else
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_alert_ramping_logic);
    return UNITY_END();
}
#endif
