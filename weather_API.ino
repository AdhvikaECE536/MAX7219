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
const char* ssid = "<your ssid>";
const char* password = "<your password>";

// ================= WEATHER API ====================
String URL = "http://api.openweathermap.org/data/2.5/weather?";
String ApiKey = "<your APIkey>";

// Location
String lat = "<lon>";
String lon = "<lat>";

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 30000; // Fetch new data every 30 seconds

// Store weather data
String weatherDesc = "...";
float weatherTemp = 0;
float weatherFeels = 0;
int weatherHumidity = 0;
int weatherPressure = 0;
float weatherWind = 0;
bool dataFetched = false;

uint8_t stage = 0;

// Buffer for display text (must be persistent)
char displayBuffer[100];

void setup() {
  Serial.begin(115200);

  // MAX7219 init
  display.begin();
  display.setIntensity(5);
  display.displayClear();

  strcpy(displayBuffer, "CONNECTING WIFI");
  display.displayText(
    displayBuffer,
    PA_CENTER,
    60,
    2000,  // 2 second pause
    PA_SCROLL_LEFT,
    PA_SCROLL_LEFT
  );

  // WiFi connect
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    display.displayAnimate();
    delay(10);
  }

  Serial.println("WiFi Connected!");
  
  display.displayClear();
  strcpy(displayBuffer, "WIFI CONNECTED");
  display.displayText(
    displayBuffer,
    PA_CENTER,
    60,
    2000,  // 2 second pause
    PA_SCROLL_LEFT,
    PA_SCROLL_LEFT
  );
  
  // Let the "WIFI CONNECTED" message finish
  while (!display.displayAnimate()) {
    delay(10);
  }
  
  display.displayClear();
  
  // Fetch initial weather data
  fetchWeatherData();
}

void fetchWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {
    
    Serial.println("Fetching weather data...");
    
    HTTPClient http;
    http.begin(URL + "lat=" + lat + "&lon=" + lon + "&units=metric&appid=" + ApiKey); // change here for C to F
    
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      
      String JSON_Data = http.getString();
      Serial.println("Response received");
      
      DynamicJsonDocument doc(2048);
      DeserializationError error = deserializeJson(doc, JSON_Data);
      
      if (!error) {
        weatherDesc = String((const char*)doc["weather"][0]["description"]);
        weatherTemp = doc["main"]["temp"];
        weatherFeels = doc["main"]["feels_like"];
        weatherHumidity = doc["main"]["humidity"];
        weatherPressure = doc["main"]["pressure"];
        weatherWind = doc["wind"]["speed"];
        dataFetched = true;
        
        Serial.println("Weather data updated successfully!");
      } else {
        Serial.println("JSON parsing failed!");
        weatherDesc = "JSON ERROR";
      }
      
    } else {
      Serial.println("HTTP request failed!");
      weatherDesc = "HTTP ERROR";
    }
    
    http.end();
  }
}

void showNextMessage() {
  String msg;
  
  switch (stage) {
    case 0:
      msg = "C: " + weatherDesc;
      break;
      
    case 1:
      msg = "T: " + String(weatherTemp, 1) + "C";
      break;
      
    case 2:
      msg = "FL: " + String(weatherFeels, 1) + "C";
      break;
      
    case 3:
      msg = "H: " + String(weatherHumidity) + "%";
      break;
      
    case 4:
      msg = "P: " + String(weatherPressure) + "hPa";
      break;
      
    case 5:
      msg = "W: " + String(weatherWind, 1) + "m/s";
      break;
  }
  
  stage = (stage + 1) % 6;
  
  Serial.println("Showing: " + msg);
  
  // Copy to persistent buffer
  msg.toCharArray(displayBuffer, 100);
  
  display.displayText(
    displayBuffer,
    PA_LEFT,
    60,          // Scroll speed
    3000,        // Pause for 3 seconds after scrolling in
    PA_SCROLL_LEFT,
    PA_SCROLL_LEFT
  );
  display.displayReset();
}

void loop() {
  // Check if animation is complete
  if (display.displayAnimate()) {
    // Animation finished, show next message
    if (dataFetched) {
      showNextMessage();
    }
  }
  
  // Check if it's time to fetch new weather data
  if (millis() - lastUpdate >= updateInterval || lastUpdate == 0) {
    fetchWeatherData();
    lastUpdate = millis();
  }
}
