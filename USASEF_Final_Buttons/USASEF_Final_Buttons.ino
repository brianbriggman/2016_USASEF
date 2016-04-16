/*
 *  2016 USASEF
 *  Code for the columns containing the buttons and neopixel strips 
 *  Brian Briggman
 */
 
#include <Adafruit_NeoPixel.h>

const int buttonPin2 = 3;     // the number of the pushbutton pin
const int buttonPin1 = 5;     // the number of the pushbutton pin
const int PIN =  9;      // the number of the LED pin

// variables will change:

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRBW + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int deviceSelected1 = 7;
int deviceSelected2 = 7;
int currentTop1 = 0;
int currentTop2 = 0;

int buttonState1 = LOW;             // the current reading from the input pin
int lastButtonState1 = LOW;   // the previous reading from the input pin
long lastDebounceTime1 = millis();  // the last time the output pin was toggled

int buttonState2 = LOW;             // the current reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin
long lastDebounceTime2 = millis();  // the last time the output pin was toggled

long debounceDelay = 50;    // the debounce time; increase if the output flickers

int min1;
int max1;
int min2;
int max2;

uint32_t DEFAULT_COLOR = strip.Color(0,127,127,0);

void setup() {
  // initialize the LED pin as an output:
  //  pinMode(ledPin, OUTPUT);
//  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(analogRead(0));

  deviceSelected1 = choose_random_index();
  currentTop1 = getCurrentMax(deviceSelected1);
  light_index(deviceSelected1,DEFAULT_COLOR);
  max1 = currentTop1;
  min1 = getCurrentMin(deviceSelected1);
  
  deviceSelected2 = 7 + choose_random_index();
  currentTop2 = getCurrentMax(deviceSelected2);
  light_index(deviceSelected2,DEFAULT_COLOR);
  max2 = currentTop2;
  min2 = getCurrentMin(deviceSelected2);

  strip.show();

//  light_index(7, strip.Color(0, 128, 128, 0));
//  light_index(8, strip.Color(0, 0, 255, 0));
//  light_index(9, strip.Color(255, 0, 0, 0));
//  light_index(10, strip.Color(128, 0, 128, 0));
//  light_index(11, strip.Color(0, 255, 0, 0));
//  light_index(12, strip.Color(128, 128, 0, 0));
//  light_index(13, strip.Color(0, 0, 255, 0));

//  strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
//  strip.setPixelColor(147, strip.Color(255, 0, 0, 0));
//  
//  strip.setPixelColor(76, strip.Color(0, 128, 128, 0));
//  strip.setPixelColor(77, strip.Color(0, 0, 255, 0));
//  strip.setPixelColor(78, strip.Color(255, 0, 0, 0));
//  strip.setPixelColor(79, strip.Color(128, 0, 128, 0));
//  strip.setPixelColor(80, strip.Color(0, 255, 0, 0));
//  strip.setPixelColor(81, strip.Color(128, 128, 0, 0));
//  strip.setPixelColor(82, strip.Color(0, 0, 255, 0));

//  light_index(0, strip.Color(0, 0, 255, 0));

  strip.show();

}

#define TABLET 0  // pixels 3-6
#define SCHOOLID 1 // 11-14
#define GPS 2 // 19-22
#define SMARTPHONE 3 // 26-29
#define VRGOGGLES 4 // 34-39
#define CAR 5 // 41-45
#define LAPTOP 6 // 49-51

long millisCounter = 0;
bool flashOnOff = false;

bool animationRunning1 = false;
bool animationRunning2 = false;

#define BOTTOM1 0
#define TOP1 75
#define TOP2 76
#define BOTTOM2 147

bool goingUp1 = false;
bool goingUp2 = false;

void loop() {

//  Serial.print("millisCounter = ");
//  Serial.print(millisCounter);
//  Serial.print("  deviceSelected1 = ");
//  Serial.print(deviceSelected1);
//  Serial.print("  deviceSelected2 = ");
//  Serial.println(deviceSelected2);
  int reading1 = digitalRead(buttonPin1);
  int reading2 = digitalRead(buttonPin2);
//  int reading1 = LOW;
//  int reading2 = LOW;
//  Serial.print("reading1 = ");
//  Serial.print(reading1);
//  Serial.print("  lastButtonState1 = ");
//  Serial.println(lastButtonState1);
//  Serial.print("  reading2 = ");
//  Serial.print(reading2);
//    Serial.print("  lastButtonState2 = ");
//  Serial.println(lastButtonState2);

  if ((reading1 != lastButtonState1) && (reading2 == lastButtonState2)) {
    // reset the debouncing timer
//    Serial.println(" *** BUTTON 1 PRESSED!!!");
    lastDebounceTime1 = millis();
  }
  
  if ((reading1 == lastButtonState1) && (reading2 != lastButtonState2)) {
    // reset the debouncing timer
//    Serial.println("* BUTTON 2 PRESSED!!!");
    lastDebounceTime2 = millis();
  }

  if (!animationRunning1 && ((millis() - lastDebounceTime1) > debounceDelay)) {
    // if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      if (buttonState1 == LOW) {
        animationRunning1 = true;
        goingUp1 = true;
      }
    }
  }

  if (!animationRunning2 && ((millis() - lastDebounceTime2) > debounceDelay)) {
    // if the button state has changed:
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == LOW) {
        animationRunning2 = true;
        goingUp2 = true;
      }
    }
  }

  if(animationRunning1)
  {
//    Serial.println("ANIMATION RUNNING 1");
    if(goingUp1)
    {
      currentTop1 = currentTop1 + 1;
      light_index(deviceSelected1,DEFAULT_COLOR);
      strip.setPixelColor(currentTop1,DEFAULT_COLOR);
      strip.show();
    }
    if(currentTop1 == TOP1)
    {
      goingUp1 = false;
    }
    if(!goingUp1)
    {
      currentTop1 = currentTop1 - 1;
      strip.setPixelColor(currentTop1+1,strip.Color(0,0,0,0));
      strip.show();

      if(currentTop1 == max1)
      {
        animationRunning1 = false;
        light_index(deviceSelected1,strip.Color(0,0,0,0));
        strip.show();
        deviceSelected1 = choose_random_index();
        currentTop1 = getCurrentMax(deviceSelected1);
        max1 = currentTop1;
        min1 = getCurrentMin(deviceSelected1);
      }
    }
  }
  
  if(animationRunning2)
  {
//    Serial.println("ANIMATION RUNNING 2");
    if(goingUp2)
    {
      currentTop2 = currentTop2 - 1;
      light_index(deviceSelected2,DEFAULT_COLOR);
      strip.setPixelColor(currentTop2,DEFAULT_COLOR);
      strip.show();
   }
    if(currentTop2 == TOP2)
    {
      goingUp2 = false;
    }
    if(!goingUp2)
    {
      currentTop2 = currentTop2 + 1;
      strip.setPixelColor(currentTop2,strip.Color(0,0,0,0));
      strip.show();

      if(currentTop2 == max2)
      {
        animationRunning2 = false;
        light_index(deviceSelected2,strip.Color(0,0,0,0));
        strip.show();
        deviceSelected2 = 7 + choose_random_index();
        currentTop2 = getCurrentMax(deviceSelected2);
        max2 = currentTop2;
        min2 = getCurrentMin(deviceSelected2);

      }
    }
  }
  
  // Figure out when to toggle the correct device lights on or off
  if(millisCounter % 500 == 0)
  {
    millisCounter = 0;
    flashOnOff = !flashOnOff;      
    
    if(flashOnOff)
    {
//      Serial.println("flashOn");
      if(!animationRunning1)
      {
//        Serial.println("   turningOn1!");
        light_index(deviceSelected1,DEFAULT_COLOR);
      }
      if(!animationRunning2)
      {
//        Serial.println("   turningOn2!");
        light_index(deviceSelected2,DEFAULT_COLOR);
      }
    }
    else
    {
//      Serial.println("flashOff");
      if(!animationRunning1)
      {
//        Serial.println("   turningOff1!");
        light_index(deviceSelected1,strip.Color(0,0,0,0));
      }
      if(!animationRunning2)
      {
//        Serial.println("   turningOff2!");
        light_index(deviceSelected2,strip.Color(0,0,0,0));
      }
    }
    strip.show();
  }

  lastButtonState1 = reading1;
  lastButtonState2 = reading2;

  millisCounter = millisCounter + 50;
  delay(50);
  
  // read the state of the pushbutton value:

  //  button1State = digitalRead(button1Pin);
  //  button2State = digitalRead(button2Pin);
  //
  //  // check if the pushbutton is pressed.
  //  // if it is, the buttonState is HIGH:
  //  if (button1State == HIGH) {
  //    // turn LED on:
  //    //digitalWrite(ledPin, HIGH);
  //    Serial.println("BUTTON 1 HIGH");
  //    light_index(state, strip.Color(0, 0, 0, 0));
  //  }
  //  else {
  //    // turn LED off:
  //    //digitalWrite(ledPin, LOW);
  //    Serial.println("BUTTON 1 LOW");
  //    state = choose_random_index();
  //    light_index(state, strip.Color(0, 128, 128, 0));
  ////    strip_on();
  //  }
  //  if (button2State == HIGH) {
  //    // turn LED on:
  //    //digitalWrite(ledPin, HIGH);
  //    Serial.println("BUTTON 2 HIGH");
  //    strip_off();
  //  }
  //  else {
  //    // turn LED off:
  //    //digitalWrite(ledPin, LOW);
  //    Serial.println("BUTTON 2 LOW");
  //    strip_on();
  //  }
}


void strip_on()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(0, 128, 128, 0));
  }
  strip.show();
}

void strip_off()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
  }
  strip.show();
}

int choose_random_index()
{
  int index = random(7);
  return index;
}

void light_index(uint16_t index, uint32_t c)
{
  int min;
  int max;

  if (index == 0)
  {
    min = 2;
    max = 5;
  }
  else if (index == 1)
  {
    min = 10;
    max = 13;
  }
  else if (index == 2)
  {
    min = 18;
    max = 21;
  }
  else if (index == 3)
  {
    min = 25;
    max = 28;
  }
  else if (index == 4)
  {
    min = 33;
    max = 38;
  }
  else if (index == 5)
  {
    min = 41;
    max = 45;
  }
  else if (index == 6)
  {
    min = 49;
    max = 52;
  }
  else if (index == 7) // Second side
  {
    min = 147 - 2;
    max = 147 - 5 -1;
  }
  else if (index == 8) // Second side
  {
    min = 147 - 10;
    max = 147 - 13 -1;
  }
  else if (index == 9) // Second side
  {
    min = 147 - 18 -1;
    max = 147 - 21 -1;
  }
  else if (index == 10) // Second side
  {
    min = 147 - 25;
    max = 147 - 28 -1;
  }
  else if (index == 11) // Second side
  {
    min = 147 - 33 -1;
    max = 147 - 38 -1;
  }
  else if (index == 12) // Second side
  {
    min = 147 - 41;
    max = 147 - 45 -1;
  }
  else if (index == 13) // Second side
  {
    min = 147 - 49 -1;
    max = 147 - 52 -1;
  }
  if(index < 7)
  {
    for (int i = min; i <= max; i++)
    {
      strip.setPixelColor(i, c);
    }
  }
  else
  {
    for (int i = max; i <= min; i++)
    {
      strip.setPixelColor(i, c);
    }
  }
}

int getCurrentMax(uint8_t index)
{
  int min;
  int max;

  if (index == 0)
  {
    max = 5;
  }
  else if (index == 1)
  {
    max = 13;
  }
  else if (index == 2)
  {
    max = 21;
  }
  else if (index == 3)
  {
    max = 28;
  }
  else if (index == 4)
  {
    max = 38;
  }
  else if (index == 5)
  {
    max = 45;
  }
  else if (index == 6)
  {
    max = 52;
  }
  else if (index == 7) // Second side
  {
    min = 147 - 2;
    max = 147 - 5 -1;
  }
  else if (index == 8) // Second side
  {
    min = 147 - 10;
    max = 147 - 13 -1;
  }
  else if (index == 9) // Second side
  {
    min = 147 - 18 -1;
    max = 147 - 21 -1;
  }
  else if (index == 10) // Second side
  {
    min = 147 - 25;
    max = 147 - 28 -1;
  }
  else if (index == 11) // Second side
  {
    min = 147 - 33 -1;
    max = 147 - 38 -1;
  }
  else if (index == 12) // Second side
  {
    min = 147 - 41;
    max = 147 - 45 -1;
  }
  else if (index == 13) // Second side
  {
    min = 147 - 49 -1;
    max = 147 - 52 -1;
  }
  return max;
}

int getCurrentMin(uint8_t index)
{
  int min;
  int max;

  if (index == 0)
  {
    min = 2;
  }
  else if (index == 1)
  {
    min = 10;
  }
  else if (index == 2)
  {
    min = 18;
  }
  else if (index == 3)
  {
    min = 25;
  }
  else if (index == 4)
  {
    min = 33;
  }
  else if (index == 5)
  {
    min = 41;
  }
  else if (index == 6)
  {
    min = 49;
  }
  else if (index == 7) // Second side
  {
    min = 147 - 2;
    max = 147 - 5 -1;
  }
  else if (index == 8) // Second side
  {
    min = 147 - 10;
    max = 147 - 13 -1;
  }
  else if (index == 9) // Second side
  {
    min = 147 - 18 -1;
    max = 147 - 21 -1;
  }
  else if (index == 10) // Second side
  {
    min = 147 - 25;
    max = 147 - 28 -1;
  }
  else if (index == 11) // Second side
  {
    min = 147 - 33 -1;
    max = 147 - 38 -1;
  }
  else if (index == 12) // Second side
  {
    min = 147 - 41;
    max = 147 - 45 -1;
  }
  else if (index == 13) // Second side
  {
    min = 147 - 49 -1;
    max = 147 - 52 -1;
  }

  return min;
}
