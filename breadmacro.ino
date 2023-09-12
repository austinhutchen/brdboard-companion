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
#define sensorPin1 7
#define sensorPin2 8
#define exitpin 2
// Variable to store the time when last event happened
unsigned long lastEvent1 = 0;
unsigned long lastEvent2 = 0;
void setup() {
  Serial.begin(115200);
  pinMode(buttonRPin, INPUT);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(buttonLPin, INPUT);
    pinMode(exitpin, INPUT);
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
  display.println("<0xf> WAITS.");
  display.display();
  delay(100);
}

void loop() {
C1:
  if (digitalRead(sensorPin1) == LOW) {
    display.println("SOUND [0x7]. ");
    display.display();
    // If 25ms have passed since last LOW state, it means that
    // the clap is detected and not due to any spurious sounds
    display.stopscroll();
    // Remember when last event happened
    lastEvent1 = millis();
  }
  if (digitalRead(sensorPin2) == LOW) {
    display.println("SOUND [0x8].");
    display.display();
    // If 25ms have passed since last LOW state, it means that
    // the clap is detected and not due to any spurious sounds
    display.stopscroll();
    // Remember when last event happened
    lastEvent2 = millis();

  }
  if (digitalRead(buttonRPin) == HIGH && digitalRead(buttonLPin) != HIGH) {
    display.println("<0x3C> RIGHT.");
    display.display();
    delay(500);
    display.startscrollright(0x00, 0x0F);
    delay(1000);
    display.stopscroll();
  }
  if (digitalRead(buttonRPin) != HIGH && digitalRead(buttonLPin) == HIGH) {
    display.println("<0x3C>  LEFT.");
    display.display();
    delay(500);
    display.startscrollleft(0x00, 0x0F);
    delay(1000);
    display.stopscroll();
  }

  // If pin goes LOW, sound is detected
 
  if(digitalRead(exitpin)==HIGH){
  display.setCursor(0, 0);
  // Display static text
   display.clearDisplay();
  display.println("<0xf> WAITS.");
  display.display();
  delay(100);
  goto C1;
  }
}
