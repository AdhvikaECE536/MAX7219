#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// ================= MAX7219 CONFIG =================
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// ================= WIFI CONFIG ====================
const char* ssid = "123";
const char* password = "123*";

// ================= WEATHER API ====================
String URL = "http://api.openweathermap.org/data/2.5/weather?";
String ApiKey = "d3c893bfa03ab05bce6f5df53c1fde83";

// Location
String lat = "17.23912677317249";
String lon = "78.43579050289536";

void setup() {
  Serial.begin(115200);

  // MAX7219 init
  display.begin();
  display.setIntensity(5);     // 0–15
  display.displayClear();

  display.displayText(
    "CONNECTING WIFI",
    PA_CENTER,
    50,
    2000,
    PA_SCROLL_LEFT,
    PA_SCROLL_LEFT
  );

  // WiFi connect
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    display.displayAnimate();
  }

  display.displayClear();
  display.displayText(
    "WIFI CONNECTED",
    PA_CENTER,
    50,
    2000,
    PA_SCROLL_LEFT,
    PA_SCROLL_LEFT
  );
}

void loop() {

  if (display.displayAnimate()) {

    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient http;
      http.begin(URL + "lat=" + lat + "&lon=" + lon +
                 "&units=metric&appid=" + ApiKey);

      int httpCode = http.GET();

      if (httpCode > 0) {

        String JSON_Data = http.getString();
        Serial.println(JSON_Data);

        DynamicJsonDocument doc(2048);
        deserializeJson(doc, JSON_Data);

        // ===== Extract parameters =====
        const char* description = doc["weather"][0]["description"];
        float temp = doc["main"]["temp"];
        float feelsLike = doc["main"]["feels_like"];
        int humidity = doc["main"]["humidity"];
        int pressure = doc["main"]["pressure"];
        float windSpeed = doc["wind"]["speed"];

        // ===== Message rotation =====
        static uint8_t stage = 0;
        String msg;

        switch (stage) {
          case 0:
            msg = "COND: " + String(description);
            break;

          case 1:
            msg = "TEMP: " + String(temp, 1) + "C  FL: " +
                  String(feelsLike, 1) + "C";
            break;

          case 2:
            msg = "HUM: " + String(humidity) + "%  PRES: " +
                  String(pressure) + "hPa";
            break;

          case 3:
            msg = "WIND: " + String(windSpeed, 1) + " m/s";
            break;
        }

        stage = (stage + 1) % 4;

        display.displayClear();
        display.displayText(
          msg.c_str(),
          PA_LEFT,
          40,
          2500,
          PA_SCROLL_LEFT,
          PA_SCROLL_LEFT
        );

      } else {
        display.displayClear();
        display.displayText(
          "ERROR FETCHING DATA",
          PA_CENTER,
          50,
          3000,
          PA_SCROLL_LEFT,
          PA_SCROLL_LEFT
        );
      }

      http.end();
    }

    delay(1000);   // update every 30 seconds
  }
}

