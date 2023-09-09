#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const int buttonRPin = 3; // the number of the pushbutton pin
const int buttonLPin = 6; // the number of the pushbutton pin
int buttonLState = 0;     // variable for reading the pushbutton status
int buttonRState = 0;

void setup() {
  Serial.begin(115200);
  pinMode(buttonRPin, INPUT);
  pinMode(buttonLPin, INPUT);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Scrolling Hello");
  display.display();
  delay(100);
}

void loop() {
  buttonRState = digitalRead(buttonRPin);
  buttonLState = digitalRead(buttonLPin);
  if (buttonRState == HIGH && buttonLState != HIGH) {
    display.startscrollright(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrolldiagright(0x00, 0x07);
    delay(2000);
  } else if (buttonRState != HIGH && buttonLState == HIGH) {
    display.startscrollleft(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrolldiagleft(0x00, 0x07);
    delay(2000);
  }
  // Scroll in various directions, pausing in-between:

  display.stopscroll();
  delay(1000);
}