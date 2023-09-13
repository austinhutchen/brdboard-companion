
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define ADC_REF                                                                \
  5 // reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
#define GROVE_VCC 5    // VCC of the grove interface is normally 5v
#define FULL_ANGLE 300 // full value of the rotary angle is 300 degrees
#include <HID.h>
#include <Wire.h>
#include <math.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const int buttonRPin = 3; // the number of the pushbutton pin
const int buttonLPin = 6; // the number of the pushbutton pin
int buttonLState = 0;     // variable for reading the pushbutton status
int buttonRState = 0;
int potentiometerPIN = 2;
#define ROTARY_ANGLE_SENSOR A2
int pvalue = 0; // value initialized to store the coming value from the sensor
// It reads the value from the sensor, ranging
// from 0 to 1023 convert to volume
#define sensorPin1 7
#define sensorPin2 8
#define exitpin 2
// Variable to store the time when last event happened
unsigned long lastEvent1 = 0;
unsigned long lastEvent2 = 0;
/************************************************************************/
/*Function: Get the angle between the mark and the starting position    */
/*Parameter:-void                                                       */
/*Return:   -int,the range of degrees is 0~300                          */
int getDegree() {
  int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
  float voltage;
  voltage = (float)sensor_value * ADC_REF / 1023;
  float degrees = (voltage * FULL_ANGLE) / GROVE_VCC;
  return degrees;
}

void setup(void) {
  Serial.begin(9600);
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
  pinsInit();
}
void pinsInit() { pinMode(ROTARY_ANGLE_SENSOR, INPUT); }
void loop(void) {

  int degrees;
  degrees = getDegree();
  Serial.println(degrees);

  /* this will be the volume outputted to the laptop */

  int brightness;
  /* Normalise to 255 (max brightness)*/

  /* sleep for half a second */
  delay(500);
  int soundValue = 0; // create variable to store many different readings
  for (int i = 0; i < 32; i++) // create a for loop to read
  {
    soundValue += analogRead(sensorPin2);
    soundValue += analogRead(sensorPin1);
  } // read the sound sensor

  soundValue >>= 7; // bitshift operation
  // if a value higher than 500 is registered, we will print the following
  // this is done so that we can clearly see if the threshold is met
  if (soundValue > 500) {
    display.print("DECIBELS: ");
    display.println(soundValue); // print the value of sound sensor
    display.println("         ||        ");
    display.println("       ||||||      ");
    display.println("     |||||||||     ");
    display.println("   |||||||||||||   ");
    display.println(" ||||||||||||||||| ");
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

  if (digitalRead(exitpin) == HIGH) {
    display.setCursor(0, 0);
    // Display static text
    display.clearDisplay();
    display.println("<0xf> WAITS.");
    display.display();
    delay(100);
  }
}
