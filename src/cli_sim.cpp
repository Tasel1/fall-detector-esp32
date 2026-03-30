#ifdef SIMULATOR
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>
#include <stdint.h>
#include <math.h>

// Эмуляция базовых типов Arduino
typedef std::string String;

// Макаем Arduino-функции в стандартный C++
unsigned long _sim_millis = 0;
extern "C" unsigned long millis() { return _sim_millis; }
void delay(int ms) { _sim_millis += ms; }

struct MockSerial {
    void print(const char* s) { std::cout << s; }
    void print(float f) { std::cout << f; }
    void print(int i) { std::cout << i; }
    void println(const char* s = "") { std::cout << s << std::endl; }
    void println(int i) { std::cout << i << std::endl; }
};
MockSerial Serial;

// Подключаем ваши модули
#include "modules/fall_detector/fall_detector.h"
#include "modules/motion_monitor/motion_monitor.h"
#include "modules/fall_detector/timer.h"

// Состояния
enum class SystemState { MONITORING, PRE_ALERT, SOS_ACTIVE };
SystemState state = SystemState::MONITORING;

FallDetector detector;
MotionMonitor motion;
FallTimer preAlertTimer;

void print_header() {
    std::cout << "\033[2J\033[1;1H"; // Очистка экрана
    std::cout << "==========================================" << std::endl;
    std::cout << "   FALL DETECTOR - INTERACTIVE CLI SIM    " << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << " TIME: " << std::fixed << std::setprecision(1) << (float)_sim_millis/1000.0f << "s | ";
    std::cout << " STATE: " << (state == SystemState::MONITORING ? "MONITORING" : 
                               state == SystemState::PRE_ALERT ? "!!! PRE-ALERT !!!" : "SOS ACTIVE") << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

int main() {
    std::string cmd;
    detector.setSensitivity(2.5f);

    while (true) {
        print_header();
        
        if (state == SystemState::PRE_ALERT) {
            if (preAlertTimer.isExpired()) {
                state = SystemState::SOS_ACTIVE;
                std::cout << "[OLED] >> SENDING SOS TO CONTACTS..." << std::endl;
            } else {
                std::cout << "[OLED] >> FALL DETECTED! CANCEL IN: " << preAlertTimer.remaining()/1000 << "s" << std::endl;
                std::cout << "[BUZZER] >> Ramping: " << 500 + (1500 * (1.0f - (float)preAlertTimer.remaining()/15000.0f)) << " Hz" << std::endl;
            }
        } else if (state == SystemState::MONITORING) {
            std::cout << "[OLED] >> Status: OK. Monitoring..." << std::endl;
        }

        std::cout << "------------------------------------------" << std::endl;
        std::cout << "COMMANDS: [fall] [still] [move] [btn] [sos] [tick] [exit]" << std::endl;
        std::cout << ">> ";
        std::cin >> cmd;

        if (cmd == "exit") break;
        
        if (cmd == "fall") {
            // 30 m/s^2 имитирует удар > 3G
            if (detector.processSensorData(30.0f, 0, 0)) {
                state = SystemState::PRE_ALERT;
                preAlertTimer.start(15000);
            }
        } else if (cmd == "still") {
            _sim_millis += 300001; // Прыгаем на 5 минут вперед
            state = SystemState::PRE_ALERT;
            preAlertTimer.start(15000);
        } else if (cmd == "move") {
            motion.update(1.5f); 
            std::cout << ">> Movement detected." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } else if (cmd == "btn") {
            if (state == SystemState::PRE_ALERT) {
                state = SystemState::MONITORING;
                std::cout << ">> SOS Canceled by user." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        } else if (cmd == "tick") {
            _sim_millis += 1000;
        } else if (cmd == "sos") {
            state = SystemState::SOS_ACTIVE;
            std::cout << ">> IMMEDIATE SOS TRIGGERED!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    return 0;
}
#endif
