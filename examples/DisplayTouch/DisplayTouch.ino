/*
  This library (fbiego CST816s) has been modified by Bruno Bortoletto aiming to offer a viable and simple 
  option for those who want to use the touch capabilities of LilyGo's "T-Display S3 Touch" model due to the
  official LilyGo's "TouchLib" library having a lot of problems and being overly complicated.

  This example shows how to use the "T-Display S3 Touch" screen as a touch input for various projects.
  Open the serial monitor to see it in action.
*/

#include <TFT_eSPI.h>
#include <TDS3_CST816.h>

TFT_eSPI tft = TFT_eSPI();
TDS3_CST816 touch(18, 17, 21, 16);	//  sda, scl, rst, irq of T-DisplayS3 Touch.

String full_y, x_tft, gesture;
bool radial_bt;

void setup() {
  touch.begin();  //  Initiates the I2C communication with CST816 touch display IC.

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  if (touch.available()){
      x_tft = String(touch.data.x);
      full_y = String(touch.data.full_y);
      radial_bt = touch.data.radial_button;
      gesture = touch.gesture();
  }

  tft.drawString("X:  " + x_tft + "         ", 0, 0, 4);
  tft.drawString("Y:  " + full_y + "        ", 0, 28, 4);
  tft.drawString(gesture + "                       ", 0, 120, 4);

  if(radial_bt == true) {
   tft.drawString("  Radial Button                 ", 0, 200, 4);
   tft.drawString("       Pressed!                 ", 0, 226, 4);   
  }
  else {
   tft.drawString("                                ", 0, 200, 4);
   tft.drawString("                                ", 0, 226, 4);  
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