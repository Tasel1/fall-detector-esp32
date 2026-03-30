#include "display_service.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#ifdef ARDUINO
Adafruit_SSD1306 DisplayService::display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

bool DisplayService::begin() {
#ifdef ARDUINO
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        return false;
    }
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.display();
#endif
    return true;
}

void DisplayService::showStatus(const char* status, int battery) {
#ifdef ARDUINO
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Status: ");
    display.println(status);
    display.print("Battery: ");
    display.print(battery);
    display.println("%");
    display.display();
#endif
}

void DisplayService::showCountdown(int seconds) {
#ifdef ARDUINO
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(30, 10);
    display.println("FALL!!");
    display.setTextSize(3);
    display.setCursor(50, 30);
    display.print(seconds);
    display.display();
#endif
}

void DisplayService::clear() {
#ifdef ARDUINO
    display.clearDisplay();
    display.display();
#endif
}
