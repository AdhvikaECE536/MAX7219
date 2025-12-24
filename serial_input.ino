#include <MD_Parola.h> // Adds text effects like scrolling
#include <MD_MAX72xx.h> //Controls MAX7219 IC
#include <SPI.h> // enables hardware level communication (DIN, CLK, CS) // chip select

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // FC16_HW → tells library which LED matrix module type using
#define MAX_DEVICES 4 // MAX_DEVICES 4 → you have 4 LED matrix blocks chained

#define DATA_PIN 23
#define CLK_PIN  18
#define CS_PIN   5 // if chip select is wrong, the display wont respond at all

MD_Parola display(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

String incomingMessage = ""; // incomingMessage → stores what you type
bool newMessage = false; // newMessage → tells Arduino "a full message has arrived" // prevents from half-written message from displaying

void setup() {
  Serial.begin(115200); // high baud rate → fast data transfer (ESP32 standard)

  display.begin(); // start display
  display.setIntensity(8); // brightness (0-15)
  display.displayClear(); // clear screen

  display.displayText(
    "READY", // text
    PA_CENTER, // alignment
    100, // speed ; if speed smaller, text scrolls faster
    1000, // pause
    PA_SCROLL_LEFT, // entry animation
    PA_SCROLL_LEFT // exit animation
  );
}

void loop() {
  // Keep animation running
  if (display.displayAnimate()) {
    if (newMessage) {
      display.displayClear();
      display.displayText(
        incomingMessage.c_str(),
        PA_CENTER,
        100,
        1000,
        PA_SCROLL_LEFT,
        PA_SCROLL_LEFT
      );
      newMessage = false;
    }
  }

  // Read Serial safely
  while (Serial.available()) {
    char c = Serial.read();

    // IGNORE newline characters
    if (c == '\n' || c == '\r') {
      if (incomingMessage.length() > 0) {
        newMessage = true;
      }
    } else {
      incomingMessage += c;
    }
  }
}
