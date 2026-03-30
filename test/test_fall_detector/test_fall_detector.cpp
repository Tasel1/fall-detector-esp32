#include <unity.h>
#include "modules/fall_detector/fall_detector.h"
#include <math.h>

#include <ArduinoFake.h>

using namespace fakeit;

extern "C" void setUp(void) {
    ArduinoFakeReset();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char*))).AlwaysReturn();
}

extern "C" void tearDown(void) {}

// Helper to calculate expected magnitude for comparison
float reference_magnitude(float x, float y, float z) {
    return sqrt(x*x + y*y + z*z);
}

void test_3axis_magnitude() {
    float ax = 10.0f, ay = 20.0f, az = 30.0f;
    float expected = reference_magnitude(ax, ay, az);
    float actual = FallDetector::calculateMagnitude(ax, ay, az);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected, actual);
}

void test_fall_detection_3axis() {
    FallDetector detector;
    detector.setSensitivity(2.5f);
    
    // Test case: Impact on X axis (3.0G > 2.5G)
    // processSensorData(ax, ay, az) where ax is in m/s^2. 
    // 3.0G * 9.81 = 29.43
    TEST_ASSERT_TRUE(detector.processSensorData(29.43f, 0.0f, 0.0f)); 
    
    // Test case: Impact on Y axis
    TEST_ASSERT_TRUE(detector.processSensorData(0.0f, 29.43f, 0.0f));

    // Test case: Impact on Z axis
    TEST_ASSERT_TRUE(detector.processSensorData(0.0f, 0.0f, 29.43f));

    // Test case: Mixed axes totaling > 2.5G
    TEST_ASSERT_TRUE(detector.processSensorData(19.62f, 19.62f, 0.0f));

    // Test case: No impact (1.0G static)
    TEST_ASSERT_FALSE(detector.processSensorData(0.0f, 0.0f, 9.81f));
}

#ifdef ARDUINO
#include <Arduino.h>
void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_3axis_magnitude);
    RUN_TEST(test_fall_detection_3axis);
    UNITY_END();
}
void loop() {}
#else
int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_3axis_magnitude);
    RUN_TEST(test_fall_detection_3axis);
    return UNITY_END();
}
#endif
