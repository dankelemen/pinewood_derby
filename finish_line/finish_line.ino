#include <Adafruit_NeoPixel.h>
#ifdef __AVR__

  #include <avr/power.h>

#endif
// Pinewood Derby Finish Line
// Daniel Kelemen
// Jan, 2017
// Pack 23 Suffern

/****************
Summary: Read 4 infrared emmitter/sensors for voltage drop/change (four lanes)
As they change, mark them first, second, third, fourth place
by lighting up the RGB LED for each lane Green, Blue, Yellow, or Red

each time through loop, check 

-------------------------------------
Component list:
Using arduino redboard (https://www.sparkfun.com/products/12757)
3x opitcal detector/phototransisor (https://www.sparkfun.com/products/246)


Connect a QRD1114, 330 resistor and 10k resistor as follows:

QRD1114 Pin ---- Arduino ---- Resistors
    1              A0      10k Pull-up to 5V
    2              GND
    3                      330 Resistor to 5V
    4              GND

As an object comes closer to the QRD1114, the voltage on A0 should go down.

3x addressable (single pin) RGB LEDs (https://www.sparkfun.com/products/12986)
Flat side down, top to bottom is digital in, 5v, ground, digital out
use adafruit library to talk to the circuit in the LED, send values for Green, Red, Blue

**********************/

#include <Adafruit_NeoPixel.h> // lib for addressable RGB LEDs, so 1 pin out instead of 3
// Setup Lane sensors (IR emitter/detector)
const int LANE1_SENSOR_PIN = A0; // Sensor output voltage
const int LANE2_SENSOR_PIN = A1; 
const int LANE3_SENSOR_PIN = A2; 
const int LANE4_SENSOR_PIN = A3; 

// Setup finish line RGB LEDs (num_leds, pin, type?
Adafruit_NeoPixel led1 = Adafruit_NeoPixel(1, 2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led2 = Adafruit_NeoPixel(1, 3, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led3 = Adafruit_NeoPixel(1, 4, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led4 = Adafruit_NeoPixel(1, 5, NEO_RGB + NEO_KHZ800);

// Misc globals
  const int DIFF = 50; // How much drop do we want to see before triggering a finish?
  const int DELAY = 1;  // loop delay
  int loopIndex = 0; // how many times through the loop
  int lane1Old = 0;
  int lane2Old = 0;
  int lane3Old = 0;
  int lane4Old = 0;
  int lane1Finished = 0; // Did lane 1 car cross yet? at which loop count?
  int lane2Finished = 0;
  int lane3Finished = 0;
  int lane4Finished = 0;
  int finishedCount = 0; // how many cars fniished?
  
void setup() {

  Serial.begin(9600);
  led1.begin(); // This initializes the NeoPixel library.
  led1.setPixelColor(0,0,0,0);  // turn it off
  led1.show();  // send to LED
  led2.begin();
  led2.setPixelColor(0,0,0,0);
  led2.setPixelColor(0,led2.Color(0,0,0)); 
  led2.show();
  led3.begin();
  led3.setPixelColor(0,0,0,0);
  led3.show();
  led4.begin();
  led4.setPixelColor(0,0,0,0);
  led4.show();
}

void loop() {
  // todo : Add some baselineing/calibration on first iteration
  loopIndex++;  // how many times through the loop are we?
  
  // ---------- Check Lane 1 ------------------------------  
  int lane1New = analogRead(LANE1_SENSOR_PIN); //Read in the ADC from lane 1 sensor
  Serial.println(lane1New);
  
  // Compare to old value. is it lower by more than diff, and never finished yet?
  if ((lane1Old > 0) and !lane1Finished and ((lane1Old - lane1New) > DIFF)) {
    if (finishedCount == 0) {  // Congratulations, First Place (Green)
      led1.setPixelColor(0,0,150,0);
      led1.show(); // This sends the updated pixel color to the hardware.
    }
    else if (finishedCount == 1) {  // Second Place (Blue)
      led1.setPixelColor(0,0,0,150);
      led1.show(); // This sends the updated pixel color to the hardware.
    }    
    else if (finishedCount == 2) {  // Third Place (Yellow)
      led1.setPixelColor(0,130,100,0);
      led1.show(); // This sends the updated pixel color to the hardware.
    }    
    else if (finishedCount == 3) {  // Fourth Place (Red)
      led1.setPixelColor(0,150,0,0);
      led1.show(); // This sends the updated pixel color to the hardware.
    }    
    finishedCount++;
    lane1Finished = loopIndex;
    Serial.print("Lane 1 Finished at loop index: " );
    Serial.println(loopIndex);
  }
  lane1Old = lane1New;
  
  // ---------- Check Lane 2 ------------------------------  
  int lane2New = analogRead(LANE2_SENSOR_PIN); //Read in the ADC from lane 2 sensor
  Serial.println(lane2New);
  
  // Compare to old value. is it lower by more than diff, and never finished yet?
  if ((lane2Old > 0) and !lane2Finished and ((lane2Old - lane2New) > DIFF)) {
    if (finishedCount == 0) {  // Congratulations, First Place (Green)
      led2.setPixelColor(0,0,150,0);
      led2.show(); // This sends the updated pixel color to the hardware.
    }
    else if (finishedCount == 1) {  // Second Place (Blue)
      led2.setPixelColor(0,0,0,150);
      led2.show(); // This sends the updated pixel color to the hardware.
    }    
    else if (finishedCount == 2) {  // Third Place (Yellow)
      led2.setPixelColor(0,130,100,0);
      led2.show(); // This sends the updated pixel color to the hardware.
    }    
    else if (finishedCount == 3) {  // Fourth Place (Red)
      led2.setPixelColor(0,150,0,0);
      led2.show(); // This sends the updated pixel color to the hardware.
    }    
    finishedCount++;
    lane2Finished = loopIndex;
    Serial.print("Lane 1 Finished at loop index: " );
    Serial.println(loopIndex);
  }
  lane2Old = lane2New;
  
  // ---------- Check Lane 3 ------------------------------    
  delay(DELAY);
}
