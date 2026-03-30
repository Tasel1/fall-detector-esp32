#include <unity.h>
#include "modules/comms/gsm_service.h"

#include <ArduinoFake.h>

using namespace fakeit;

extern "C" void setUp(void) {
    ArduinoFakeReset();
    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char*))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char*))).AlwaysReturn();
}

extern "C" void tearDown(void) {}

void test_sms_payload_generation() {
    GSMService gsm;
    String payload = gsm.formatSMSPayload(55.75f, 37.61f);
    
    TEST_ASSERT_TRUE(payload.indexOf("EMERGENCY") >= 0);
    TEST_ASSERT_TRUE(payload.indexOf("55.75") >= 0);
}

void test_gps_link_generation() {
    GSMService gsm;
    String payload = gsm.formatSMSPayload(55.75f, 37.61f);
    TEST_ASSERT_TRUE(payload.indexOf("maps.google.com") >= 0);
}

#ifdef ARDUINO
#include <Arduino.h>
void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_sms_payload_generation);
    RUN_TEST(test_gps_link_generation);
    UNITY_END();
}
void loop() {}
#else
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_sms_payload_generation);
    RUN_TEST(test_gps_link_generation);
    return UNITY_END();
}
#endif
