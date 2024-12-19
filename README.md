# TDisplayS3_Touch

This library provides a reliable and straightforward solution for utilizing the touch features of LilyGo's "T-Display S3 Touch" model. It was developed as an alternative to the official "TouchLib" library, which is known to have significant issues and an overly complex implementation.

## Features
- Simplified integration for touch capabilities of the T-Display S3 Touch.
- Support for gestures such as swipe, single click, double click, and long press.
- Access to touch coordinates, gesture types, and radial button states.

## Examples

### DisplayTouch Example
This example demonstrates how to use the "T-Display S3 Touch" screen for graphical touch input. Open the serial monitor to observe the output.

```cpp
#include <TFT_eSPI.h>
#include <TDS3_CST816.h>

TFT_eSPI tft = TFT_eSPI();
TDS3_CST816 touch(18, 17, 21, 16);  // SDA, SCL, RST, IRQ pins of T-Display S3 Touch.

String full_y, x_tft, gesture;
bool radial_bt;

void setup() {
  touch.begin();  // Initiate I2C communication with CST816 touch display IC.

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  if (touch.available()) {
      x_tft = String(touch.data.x);
      full_y = String(touch.data.full_y);
      radial_bt = touch.data.radial_button;
      gesture = touch.gesture();
  }

  tft.drawString("X:  " + x_tft + "         ", 0, 0, 4);
  tft.drawString("Y:  " + full_y + "        ", 0, 28, 4);
  tft.drawString(gesture + "                       ", 0, 120, 4);

  if (radial_bt == true) {
    tft.drawString("  Radial Button                 ", 0, 200, 4);
    tft.drawString("       Pressed!                 ", 0, 226, 4);
  } else {
    tft.drawString("                                ", 0, 200, 4);
    tft.drawString("                                ", 0, 226, 4);
  }
}
```

### SerialTouch Example
This example demonstrates how to use the "T-Display S3 Touch" screen for serial output of touch data. Open the serial monitor to see the touch data in action.

```cpp
#include <TDS3_CST816.h>

TDS3_CST816 touch(18, 17, 21, 16);  // SDA, SCL, RST, IRQ pins of T-Display S3 Touch.

void setup() {
  Serial.begin(115200);  // Initiate serial communication with ESP32-S3.
  touch.begin();         // Initiate I2C communication with CST816 touch display IC.
}

void loop() {
  if (touch.available()) {  // Check for touch input and retrieve parameters in the "data" structure.
    Serial.print("Gesture: ");
    Serial.print(touch.gesture());  // Gesture ID: NONE, SWIPE DOWN, SWIPE UP, etc.
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(touch.data.x);  // X coordinate (0 to 170).
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(touch.data.y);  // Y coordinate (0 to 255).
    Serial.print("\t");
    Serial.print("Sector: ");
    Serial.print(touch.data.sector);  // Screen division into sectors.
    Serial.print("\t");
    Serial.print("Full Y: ");
    Serial.print(touch.data.full_y);  // Full Y coordinate (0 to 359).
    Serial.print("\t");
    Serial.print("Radial button: ");
    Serial.println(touch.data.radial_button);  // Radial button state.
  }
}
```

## API Overview
### Class `TDS3_CST816`
#### Constructor
```cpp
TDS3_CST816(int sda, int scl, int rst, int irq);
```
- `sda`: I2C data pin.
- `scl`: I2C clock pin.
- `rst`: Reset pin for the touch IC.
- `irq`: Interrupt pin for the touch IC.

#### Methods
- **`void begin(int interrupt = RISING)`**: Initializes the touch screen with the specified interrupt type.
- **`void sleep()`**: Puts the touch screen into standby mode.
- **`bool available()`**: Checks if a touch event is available.
- **`String gesture()`**: Retrieves the name of the current gesture.

#### Data Structure
```cpp
struct data_struct {
  byte gestureID;         // Gesture ID.
  byte points;            // Number of touch points.
  byte event;             // Event type (0 = Down, 1 = Up, 2 = Contact).
  uint16_t x;             // X coordinate (0 to 170).
  uint16_t y;             // Y coordinate (0 to 255).
  uint16_t full_y;        // Full Y coordinate (0 to 359).
  uint16_t sector;        // Screen sector.
  bool radial_button;     // Radial button state.
  uint8_t version;        // Version of the touch IC.
  uint8_t versionInfo[3]; // Additional version information.
};
```

## License
This library is released under the MIT License. See the LICENSE file for details.
