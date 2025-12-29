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

### 📦 Setup

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


# weather_API.ino
