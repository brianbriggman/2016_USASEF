/*
 *  2016 USASEF
 *  Code for animating the little clouds - WORK IN PROGRESS - We never had time to actually work with these as promised...
 *  Brian Briggman
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 9

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1425,PIN,NEO_GRBW + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

//  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(255);
  for(int i=0; i<8; i++)
  {
    large_on(i, strip.Color(255, 255, 255, 255));
  }
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
//  large_theatre_chase(strip.Color(255, 255, 255, 255), 0);
//  large_theatre_chase(strip.Color(255, 0, 0, 0), 10);
//  large_theatre_chase(strip.Color(0, 255, 0, 0), 10);
//  large_theatre_chase(strip.Color(0, 0, 255, 0), 10);
//  large_theatre_chase(strip.Color(0, 0, 0, 255), 10);

  
//  colorWipe(strip.Color(255, 0, 0,0), 5); // Red
//  colorWipe(strip.Color(0, 255, 0,0), 5); // Green
//  colorWipe(strip.Color(0, 0, 255,0), 5); // Blue
//  colorWipe(strip.Color(255, 255, 255, 255), 0); // White
  // Send a theater pixel chase in...
//  theaterChase(strip.Color(0, 0, 0,255), 50); // White
//  theaterChase(strip.Color(127, 0, 0), 50); // Red
//  theaterChase(strip.Color(0, 0, 127), 50); // Blue

//  for(int i=0; i<9; i++)
//  {
//    large_on(i, strip.Color(255, 255, 255, 255));
//    large_off(i-1);
//    strip.show(); // Initialize all pixels to 'off'
//    delay(25);
//  }

//for(int i=0; i<3; i++)
//{
//  medium_on(0, strip.Color(0, 0, 0, 0));
//  medium_on(1, strip.Color(0, 0, 0, 0));
//  medium_on(2, strip.Color(0, 0, 0, 0));
//  medium_on(i, strip.Color(0, 0, 255, 0));
//  strip.show();
//  delay(1000);
//}
//strip.show();
//delay(100000);
//  rainbow(20);
//  rainbowCycle(20);
//  theaterChaseRainbow(50);
}

void large_theatre_chase(uint32_t c, uint8_t wait)
{
  for(int i=0; i<50; i++)
  {
    for (int q=0; q < 3; q++) {
      for (int i=0; i < 8; i=i+3) {
        large_on(i+q, c);    //turn every third large globe on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        large_off(i+q);        //turn every third large globe off
      }
      strip.show();
    }
  }
}

void large_on(uint8_t index, uint32_t c)
{
  for(uint16_t i=index*150; i<(index*150)+150; i++) {
    if(index == 0 || index == 3 || index == 6)
    {
      byte red = (byte)((c & 0x00ff0000 ) >> 16);
      byte green = (byte)((c & 0x000000ff));
      byte blue = (byte)((c & 0xff000000) >> 24);
      byte white = (byte)((c & 0x0000ff00) >> 8);
      c = strip.Color(blue,blue,red,green);
//      Serial.print("color = ");
//      Serial.print(red);
//      Serial.print(",");
//      Serial.print(green);
//      Serial.print(",");
//      Serial.print(blue);
//      Serial.print(",");
//      Serial.print(white);
//      Serial.println();
//      c = strip.Color((byte)c&0x000000ff,(byte)c&0x0000ff00>>8,(byte)c&0x00ff0000>>16,(byte)c&0xff000000>>24);
//      c = strip.Color(0,255,0,0); // Blue(purple),Red(orange),W,G
    }
    strip.setPixelColor(i, c);
  }
}

void medium_on(uint8_t index, uint32_t c)
{
  for(uint16_t i=1200+(index*75); i<1200+(index*75)+75; i++) {
    strip.setPixelColor(i, c);
  }
}

void large_off(uint8_t index)
{
  for(uint16_t i=index*150; i<(index*150)+150; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0,0));
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
