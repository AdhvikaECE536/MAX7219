## 📂 Repository Structure
- `serial_input.ino` - ESP32 code to fetch and display text from SerialMonitor
- `weather_API.ino`  - ESP32 code to fetch and display weather from API


---

# serial_input.ino

### ✨ Features

- **Real-time Text Display**: Send messages through Serial Monitor and see them instantly on the LED matrix
- **Smooth Scrolling Animation**: Text scrolls smoothly from right to left with customizable speed
- **Multiple Matrix Support**: Supports up to 4 chained LED matrix modules (easily expandable)
- **Adjustable Brightness**: Set display intensity from 0-15
- **Simple Serial Interface**: Easy-to-use text input via Serial Monitor at 115200 baud

### 🛠️ Hardware Requirements

| Component                 | Specification             | Quantity |
| ------------------------- | ------------------------- | -------- |
| ESP32 Development Board   | ESP32-WROOM-32 or similar | 1        |
| MAX7219 LED Matrix Module | FC16 type (32x8 pixels)   | 1        |
| USB Cable                 | Micro USB or USB-C        | 1        |
| Breadboard (Optional)     | Standard size             | 1        |
| Jumper Wires              | Male-to-Female            | 5        |

### 🔌 Connections

The MAX7219 LED Matrix Module is connected to ESP32 through suggested conections:

```
ESP32          MAX7219 LED
─────────────────────────────────
5V(Vin)  →     VCC (power supply)
GND      →     GND (ground)
GPIO23   →     DIN (data input)
GPIO18   →     CLK (clock signal)
GPIO05   →     CS  (chip select)
```

### 📦 Software Installations and Setup

1. **Install Arduino IDE**
   - Download from [arduino.cc](https://www.arduino.cc/en/software)
   - Install version 2.0 or higher

2. **Add ESP32 Board Support**
   - Open Arduino IDE
   - Go to `File` → `Preferences`
   - Add this URL to "Additional Board Manager URLs":
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
   - Go to `Tools` → `Board` → `Boards Manager`
   - Search for "ESP32" and install "esp32 by Espressif Systems"

3. **Install Required Libraries**
   
   Go to `Sketch` → `Include Library` → `Manage Libraries` and install:
   
   - **MD_Parola** (by MajicDesigns)
	   - Provides text effects and animations
   - **MD_MAX72XX** (by MajicDesigns)
	   - Controls MAX7219 LED matrix driver IC
   - **SPI** (Built-in)
	   - Enables hardware SPI communication

3. Configure the Code
  - Clone this repository
  - Open the `serial_input.ino` file in Arduino IDE


### 📖 How It Works

1. **Initialization**: ESP32 starts Serial communication at 115200 baud and configures the LED matrix display
2. **Display Setup**: Sets brightness to level 8 (range: 0-15) and shows "READY" message
3. **Character Reception**: Reads incoming characters from Serial Monitor one by one
4. **Message Building**: Accumulates characters into a complete message string
5. **Display Trigger**: When newline character is detected, updates the LED matrix with the new message
6. **Animation Loop**: Continuously scrolls the text across the display until a new message arrives

Display Configuration
```cpp
display.displayText( 
	"Your Text", // Message content 
	PA_CENTER, // Text alignment 
	100, // Scroll speed (lower = faster) 
	1000, // Pause duration (milliseconds) 
	PA_SCROLL_LEFT, // Entry animation 
	PA_SCROLL_LEFT // Exit animation );
```


### 🎨 Customization

- **Scroll Speed**: `100` (adjust for faster/slower scrolling)
    - Lower values = faster scrolling
    - Higher values = slower scrolling

- **Brightness**: `8` (0 = dimmest, 15 = brightest)

- **Pause Duration**: `1000ms` (pause before text starts scrolling)


### 🐛 Troubleshooting

##### 1. Display Not Working
1. **Check Power Supply**
    - Ensure 5V and GND are properly connected
    - Multiple modules may require external 5V power supply
2. **Verify Pin Connections**
    - Confirm DIN, CLK, and CS pins match the code
    - Most common issue: incorrect CS pin (should be GPIO 5)
3. **Hardware Type Mismatch**
    - Ensure `HARDWARE_TYPE` matches your module:

``` cpp
     #define HARDWARE_TYPE MD_MAX72XX::FC16_HW  // For FC16 modules
```

- Other options: `PAROLA_HW`, `GENERIC_HW`, `ICSTATION_HW`

##### 2. Text Not Displaying
- **Open Serial Monitor** at 115200 baud
- **Check for carriage return** (newline) after your message
- **Verify** the message string is not empty

##### 3. Garbled Display
- **Reduce number of devices** to test
- **Check data line integrity** (use shorter wires)
- **Verify power supply** is stable and sufficient


### 🎓 Learning Outcomes

- **SPI Communication**: Understanding hardware-level communication protocol (DIN, CLK, CS pins)
- **Serial Communication**: UART data transfer between computer and ESP32
- **LED Matrix Control**: Working with MAX7219 driver IC and dot matrix displays
- **Arduino Libraries**: Using third-party libraries (MD_Parola, MD_MAX72XX)
- **ESP32 Programming**: GPIO configuration and pin mapping on ESP32
- **Text Animation**: Implementing scrolling effects and display animations
- **Hardware Integration**: Connecting and controlling external display modules
- **Debugging Skills**: Troubleshooting hardware connections and serial communication


### 🚀 Future Enhancements

- **WiFi Integration**: Display messages received over WiFi
- **Web Interface**: Control display through a web browser
- **Bluetooth Control**: Send messages from smartphone app
- **Multiple Animations**: Add support for different text effects
- **Clock Display**: Show real-time clock using NTP
- **Sensor Integration**: Display temperature, humidity, etc.
- **Message Queue**: Store and cycle through multiple messages
- **Brightness Auto-adjust**: Use light sensor for adaptive brightness

---

## PART 02: Weather API on `MAX7219`

### ✨ Features

- 🌡️ **Real-Time Weather Data** - Fetches live temperature, humidity, pressure, and weather conditions
- 📡 **WiFi Connectivity** - Connects to your home WiFi network
- 🖥️ **LED Matrix Display** - Shows weather information on 32x8 pixel scrolling display
- 🔄 **Auto-Rotation** - Cycles through different weather parameters automatically
- 💡 **Smooth Animations** - Scrolling text effects for easy reading
- ⚡ **Low Power** - Efficient ESP32 implementation with adjustable brightness

### 🛠️ Hardware Requirements

| Component                 | Specification             | Quantity |
| ------------------------- | ------------------------- | -------- |
| ESP32 Development Board   | ESP32-WROOM-32 or similar | 1        |
| MAX7219 LED Matrix Module | FC16 type (32x8 pixels)   | 1        |
| USB Cable                 | Micro USB or USB-C        | 1        |
| Breadboard (Optional)     | Standard size             | 1        |
| Jumper Wires              | Male-to-Female            | 5        |

### 🔌 Connections

The MAX7219 LED Matrix Module is connected to ESP32 through suggested conections:

```
ESP32          MAX7219 LED
─────────────────────────────────
5V(Vin)  →     VCC (power supply)
GND      →     GND (ground)
GPIO23   →     DIN (data input)
GPIO18   →     CLK (clock signal)
GPIO05   →     CS  (chip select)
```

### 📦 Software Installations

1. **Install Arduino IDE**
   - Download from [arduino.cc](https://www.arduino.cc/en/software)
   - Install version 2.0 or higher

2. **Add ESP32 Board Support**
   - Open Arduino IDE
   - Go to `File` → `Preferences`
   - Add this URL to "Additional Board Manager URLs":
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
   - Go to `Tools` → `Board` → `Boards Manager`
   - Search for "ESP32" and install "esp32 by Espressif Systems"

3. **Install Required Libraries**
   
   Go to `Sketch` → `Include Library` → `Manage Libraries` and install:
   
- **MD_Parola** (by MajicDesigns)
	- Provides text effects and animations
- **MD_MAX72XX** (by MajicDesigns)
	-  Controls MAX7219 LED matrix driver IC
- **SPI** (Built-in)
	- Enables hardware SPI communication
- **WiFi** (Pre-installed with ESP32)
- **HTTPClient** (usually pre-installed with ESP32)
- **ArduinoJson** (by Benoit Blanchon) 
	- for parsing weather data

### 🚀 Setup Steps

#### Step 1: Get OpenWeatherMap API Key
1. Go to [OpenWeatherMap](https://openweathermap.org/api)
2. Sign up for a free account
3. Navigate to API Keys section in 
4. Copy your API key (looks like: `a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6`)

#### Step 2: Get location coordinates
1. Go to [Google Maps](https://www.google.com/maps)
2. Right-click on any location of choice
3. Copy the coordinates information (lat, lon)

#### Step 3: Configure the Code
1. Clone this repository
2. Open the `weather_API.ino` file in Arduino IDE
2. Update these lines with your information:
   
```cpp
// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// OpenWeatherMap API
String apiKey = "YOUR_API_KEY_HERE";

// Coordinates 
String lat = "<your lat>";
String lon = "<your lon>";
```

#### Step 4: Upload to ESP32
1. Connect ESP32 to your computer via USB
2. Select board: `Tools` → `Board` → `ESP32 Dev Module`
3. Select correct COM port: `Tools` → `Port` → `COMx` (Windows) or `/dev/ttyUSB0` (Linux/Mac)
4. Click the **Verify** button (✓) 
5. Click the **Upload** button (→)
6. Wait for "Done uploading" message

#### Step 5: Monitor Serial Output
1. Open Serial Monitor: `Tools` → `Serial Monitor`
2. Set baud rate to `115200` and `new line`
3. You should see connection status and weather data!

### 📊 Display Information

The LED matrix cycles through these views automatically:

1. **Weather Condition** - Description (e.g., "clear sky", "light rain")
2. **Temperature & Feels Like** - Current temp and apparent temperature (°C)
3. **Humidity & Pressure** - Humidity (%) and atmospheric pressure (hPa)
4. **Wind Speed** - Wind speed in m/s

Each view scrolls across the display and automatically switches to the next after a delay.

### 📖 How It Works

- **WiFi Connection**: ESP32 connects to your WiFi network (displays "CONNECTING WIFI" message)
- **Connection Confirmation**: Once connected, displays "WIFI CONNECTED"
- **API Request**: Sends HTTP GET request to OpenWeatherMap API with your coordinates
- **JSON Parsing**: Receives and parses JSON response containing weather data
- **Data Extraction**: Extracts weather parameters (condition, temp, humidity, pressure, wind)
- **Display Rotation**: Cycles through 4 different weather views with scrolling animation
- **Loop**: Updates weather data every 30 seconds and continues cycling

### Display Flow

```
Stage 0: COND: [weather description]
   ↓
Stage 1: TEMP: [temperature]C  FL: [feels like]C
   ↓
Stage 2: HUM: [humidity]%  PRES: [pressure]hPa
   ↓
Stage 3: WIND: [wind speed] m/s
   ↓
(Repeat from Stage 0)
```

### 🎨 Customization
##### Change Display Brightness

```cpp
display.setIntensity(5);  // Range: 0 (dimmest) - 15 (brightest)
```

##### Change Scroll Speed

```cpp
display.displayText(
  msg.c_str(),
  PA_LEFT,
  40,        // ← Speed (lower = faster, higher = slower)
  2500,      // ← Pause duration in milliseconds
  PA_SCROLL_LEFT,
  PA_SCROLL_LEFT
);
```

##### Change Update Interval

```cpp
delay(1000);  // Update every 30 seconds (30000 ms)
              // Change to 60000 for 1 minute, 600000 for 10 minutes
```

##### Change Temperature Unit

```cpp
// In the API URL, change the units parameter:
"&units=metric"    // For Celsius (default)
// OR
"&units=imperial"  // For Fahrenheit
```


### 🐛 Troubleshooting

##### 1. Display Not Working

**Check Power Supply**
- Ensure 5V and GND are properly connected
- Multiple modules may require external 5V power supply (each module draws ~320mA)

**Verify Pin Connections**
- Confirm DIN (GPIO23), CLK (GPIO18), and CS (GPIO5) pins match the code
- Most common issue: incorrect CS pin

**Hardware Type Mismatch**
- Ensure `HARDWARE_TYPE` matches your module:
```cpp
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  // For FC16 modules
```

- Other options: `PAROLA_HW`, `GENERIC_HW`, `ICSTATION_HW`

##### 2. WiFi Connection Failed
- Double-check SSID and password (case-sensitive!)
- Make sure WiFi is 2.4GHz (ESP32 doesn't support 5GHz)
- Check if WiFi has special characters in password
- Try moving ESP32 closer to router
- Watch LED matrix for "CONNECTING WIFI" message

##### 3. API Not Responding
- Verify API key is correct (no extra spaces)
- Check latitude and longitude values
- Ensure you have internet connection
- Wait a few minutes (new API keys can take time to activate)
- Check API usage limits (free tier: 60 calls/minute, 1,000,000 calls/month)
- Watch Serial Monitor for JSON response

##### 4. Display Shows "ERROR FETCHING DATA"
- Check Serial Monitor for HTTP error codes
- Verify WiFi connection is stable
- Confirm API URL is correct
- Check if OpenWeatherMap service is online

##### 5. Garbled or Missing Text
- Reduce number of devices to test
- Check data line integrity (use shorter wires)
- Verify power supply is stable and sufficient
- Lower the brightness if power supply is weak

##### 6. Code Won't Upload
- Hold `BOOT` button on ESP32 while uploading
- Check USB cable (some cables are power-only)
- Select correct COM port
- Try a different USB port
- Install CH340/CP2102 drivers if needed

### 🎓 Learning Outcomes
- **WiFi Connectivity** - Connecting ESP32 to wireless networks
- **HTTP API Requests** - Making GET requests to web services
- **JSON Data Parsing** - Extracting data from API responses
- **SPI Communication** - Hardware-level communication with LED displays
- **LED Matrix Control** - Working with MAX7219 driver IC
- **Text Animation** - Implementing scrolling effects and display cycling
- **Arduino Libraries** - Using third-party libraries effectively
- **ESP32 Programming** - GPIO configuration and pin mapping
- **State Management** - Cycling through different display modes
- **Debugging Skills** - Troubleshooting WiFi, API, and hardware issues
- **IoT Development** - Building internet-connected embedded systems

### 🚀 Future Enhancements
- **Real-Time Clock Display** - Show current time using NTP server
- **Multiple Locations** - Switch between different cities via Serial input
- **Weather Alerts** - Display warnings for severe weather conditions
- **Weather Forecast** - Show 5-day forecast data
- **Local Sensors** - Integrate DHT22 for indoor vs outdoor comparison
- **Custom Icons** - Add weather-specific pixel art animations
- **Adaptive Brightness** - Adjust LED intensity based on time of day
- **Mobile Control** - Web interface for location and display settings
- **Data Logging** - Store historical weather data on SD card
- **Voice Announcements** - Add MP3 module for weather audio updates
- **Alarm Integration** - Wake-up display with weather briefing
- **Home Assistant** - MQTT integration for smart home systems

---

## 📄 License

This project is open source and available for educational purposes. 

---

## 👤 Author

[@AdhvikaECE536](https://github.com/AdhvikaECE536)

---

## 🙏 Acknowledgments
Special thanks to GMR Airports Ltd for proving me the environment to learn, explore and grow. 

---

**Note**: This is a learning project. It uses open-source libraries and public APIs. Feel free to experiment and modify the code!


---

Made with ❤️ using ESP32
