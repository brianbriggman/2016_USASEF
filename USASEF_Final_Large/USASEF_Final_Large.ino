/*
 *  2016 USASEF
 *  Code for animating the 8 large clouds 
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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1200,PIN,NEO_GRBW + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

#define SECTION_SIZE 9

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

//  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(255);
  delay(1000);
  for(int i=0; i<8; i++)
  {
    large_on(i, strip.Color(255, 255, 255, 255));
    strip.show();
    delay(1000);
  }
strip.show();
delay(10000);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
//  delay(2000);
//  for(int i=0; i<8; i++)
//  {
//    large_on(i, strip.Color(255, 255, 255, 255));
//    strip.show();
//    delay(2000);
//  }
  large_theatre_chase(strip.Color(255, 255, 255, 255), 5);
////  delay(10000);
  large_flashing(500,strip.Color(0,128,128,0));
////  delay(10000);
  large_fade_inout(1000,strip.Color(255,0,255,0));
//  delay(10000);
//  large_theatre_chase(strip.Color(255, 0, 0, 0), 10);
//  large_theatre_chase(strip.Color(0, 255, 0, 0), 10);
//  large_theatre_chase(strip.Color(0, 0, 255, 0), 10);
//  large_theatre_chase(strip.Color(0, 0, 0, 255), 10);

//flash(strip.Color(255,255,255,255), (uint32_t)10, (uint32_t)150);
//flash(strip.Color(255,255,255,255), (uint32_t)30, (uint32_t)450);
//flash(strip.Color(255,255,255,255), (uint32_t)30, (uint32_t)2000);

for(int i=0; i<60; i++)
{
  long off_delay = 2000 + random(0, 4000);
  flash_section(strip.Color(255, 255, 255, 255), (uint32_t)25, (uint32_t)150);
  flash_section(strip.Color(255, 255, 255, 255), (uint32_t)75, (uint32_t)off_delay);
}

  
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
//delay(50);
  for(int j=0; j<60; j++)
  {
//    delay(1000);
    for(int i=0; i<8; i++)
    {
      large_on(i, strip.Color(255, 255, 255, 255));
      strip.show();
      delay(1000);
    }
    for(int i=0; i<8; i++)
    {
      large_off(i);
      strip.show();
      delay(1000);
    }
  }
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

void flash(uint32_t c, uint32_t wait_on, uint32_t wait_off) 
{
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i,c);
  }
  strip.show();   
  delay(wait_on);
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i,strip.Color(0, 0, 0, 0));
  }
  strip.show();   
  delay(wait_off);  
}

void flash_section(uint32_t c, uint32_t wait_on, uint32_t wait_off) 
{
  long section1 = random(0, 32);
  side_on(section1);
  
  long section2 = random(0, 32);
  side_on(section2);
  strip.show();   

  // Random amount - up to 10% of wait_on value
  long random10 = random(0, wait_on/10);
  delay(wait_on + random10);

  // Turn off all
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i,strip.Color(0, 0, 0, 0));
  }
  strip.show();   
  delay(wait_off);  
}

void side_on(uint32_t side_index)
{
    for(int j=0; j<4; j++)
    {
      section_on(strip.Color(255,255,255,255), ((side_index/2)*8) + (side_index%2) + (j*2)); // i==side; j==section
    }
}

void side_off(uint32_t side_index)
{
  for(int j=0; j<4; j++)
  {
    section_on(strip.Color(0,0,0,0), ((side_index/2)*8) + (side_index%2) + (j*2)); // i==side; j==section
  }
}

void section_on(uint32_t c, uint32_t section) {
  for(int i=section*SECTION_SIZE; i<(section*SECTION_SIZE)+SECTION_SIZE; i++)
  {
    strip.setPixelColor(i,c);
  }
  strip.show();   
}

void section_off(uint32_t section) {
  for(int i=section*SECTION_SIZE; i<(section*SECTION_SIZE)+SECTION_SIZE; i++)
  {
    strip.setPixelColor(i,strip.Color(0,0,0,0));
  }
  strip.show();   
}

void large_flashing(uint16_t wait, uint32_t c)
{
  for(int j=0; j<50; j++)
  {
    for(int i=0; i<8; i++)
    {
      large_on(i,c);  
    }
    strip.show();
    delay(wait);
    for(int i=0; i<8; i++)
    {
      large_off(i);  
    }
    strip.show();
    delay(wait);
  }
}

void large_on(uint8_t index, uint32_t c)
{
  for(uint16_t i=index*150; i<(index*150)+150; i++) {
//    if(index == 0 || index == 3 || index == 6)
//    {
//      byte red = (byte)((c & 0x00ff0000 ) >> 16);
//      byte green = (byte)((c & 0x000000ff));
//      byte blue = (byte)((c & 0xff000000) >> 24);
//      byte white = (byte)((c & 0x0000ff00) >> 8);
//      c = strip.Color(blue,blue,red,green);
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
//    }
    strip.setPixelColor(i, c);
  }
}

void large_fade_inout(uint16_t time, uint32_t c)
{
//  Serial.print("color = ");
//  Serial.print(red);
//  Serial.print(",");
//  Serial.print(green);
//  Serial.print(",");
//  Serial.print(blue);
//  Serial.print(",");
//  Serial.print(white);
//  Serial.println();

  float percent;

uint32_t RED = strip.Color(255,0,0,0);
uint32_t ORANGE = strip.Color(255,128,0,0);
uint32_t YELLOW = strip.Color(255,255,20,0);
uint32_t GREEN = strip.Color(0,255,0,0);
uint32_t BLUE = strip.Color(0,0,255,0);
uint32_t PURPLE = strip.Color(255,0,255,0);
uint32_t COLOR1 = strip.Color(255,90,128,0);

  for(int i=0; i<8; i++)
  {
    if(i==0)
    {
      c = RED;
    }
    else if(i==1)
    {
      c = ORANGE;
    }
    else if(i==2)
    {
      c = YELLOW;
    }
    else if(i==3)
    {
      c = GREEN;
    }
    else if(i==4)
    {
      c = BLUE;
    }
    else if(i==5)
    {
      c = PURPLE;
    }
    else if(i==6)
    {
      c = COLOR1;
    }
    else if(i==7)
    {
      c = BLUE;
    }
    
  byte green = (byte)((c & 0xff000000) >> 24);
  byte red = (byte)((c & 0x00ff0000 ) >> 16);
  byte white = (byte)((c & 0x0000ff00) >> 8);
  byte blue = (byte)((c & 0x000000ff));

    for(int i=0; i<=255; i=i+8)
    {
      for(int k=0; k<8; k++)
      {
        large_on(k,strip.Color(i&red,i&green,i&blue,i&white));
      }
      strip.show();
    }
    for(int i=255; i>=0; i=i-8)
    {
      for(int k=0; k<8; k++)
      {
        large_on(k,strip.Color(i&red,i&green,i&blue,i&white));
      }
      strip.show();
    }
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
