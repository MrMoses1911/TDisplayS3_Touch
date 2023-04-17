/*
  This library (fbiego CST816s) has been modified by Bruno Bortoletto aiming to offer a viable and simple 
  option for those who want to use the touch capabilities of LilyGo's "T-Display S3 Touch" model due to the
  official LilyGo's "TouchLib" library having a lot of problems and being overly complicated.

  This example shows how to use the "T-Display S3 Touch" screen as a touch input for various projects.
  Open the serial monitor to see it in action.
*/
#include <TDS3_CST816.h>

TDS3_CST816 touch(18, 17, 21, 16);	//  sda, scl, rst, irq of T-DisplayS3 Touch.

void setup() {
  Serial.begin(115200); // Iniates the serial communication with ESP32-S3.
  touch.begin();  //  Initiates the I2C communication with CST816 touch display IC.
}

void loop() {
  if (touch.available()) {  //  Checks for a touch input and returns parameters in the "data" structure.
    Serial.print("Gesture: ");
    Serial.print(touch.gesture());  //  Gesture ID: NONE, SWIPE DOWN, SWIPE UP, SWIPE LEFT, SWIPE RIGHT, SINGLE_CLICK, DOUBLE_CLICK, LONG_PRESS.
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(touch.data.x); //  Display X coordinate (0 to 170).
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(touch.data.y); //  Display Y coordinate (0 to 255). Goes back to 0 when sector = 1.
    Serial.print("\t");
    Serial.print("Sector: ");
    Serial.print(touch.data.sector);  //  Screen division in sectors. 0: Y <= 255; 1: Y > 255.
    Serial.print("\t");
    Serial.print("Full Y: ");
    Serial.print(touch.data.full_y);  //  Real display Y coordinate (0 to 359). Use this parameter for touch inputs. full_y = y + (sector * 255)
    Serial.print("\t");
    Serial.print("Radial button: ");
    Serial.println(touch.data.radial_button); //  Display radial button. true: y = 104 or full_y = 359         
  }
}

/*
MIT License

Copyright (c) 2023 Bruno Bortoletto
Copyright (c) 2021 Felix Biego

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/