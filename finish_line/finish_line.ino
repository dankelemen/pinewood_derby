#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
/****************
// Pinewood Derby Finish Line
// Conor and Dan Kelemen
// Jan, 2017
// Pack 23 Suffern, NY
// dkelemen@gmail.com

Summary: Read 4 infrared emmitter/sensors for voltage drop indicating car crossing over finish line (four lanes)
As they change, mark them first, second, third, fourth place by lighting up the RGB LED for each lane Green, Blue, Yellow, or Red

-------------------------------------
Component list:
Using Elegoo arduino uno (https://www.amazon.com/Elegoo-ATmega328P-ATMEGA16U2-Compatible-Arduino/dp/B01EWOE0UU) - $10.86 for one
4x opitcal detector/phototransisor (https://www.sparkfun.com/products/246) - $3.80 for five

Connect a QRD1114, 330 resistor and 10k pullup resistor as (clockwise from dot):

QRD1114 Pin ---- Arduino ---- Resistors
    1              A0      10k Pull-up to 5V  (changed to INTERNAL_PULLUP after found out about it)
    2              GND
    3                      330 Resistor to 5V
    4              GND

As an object comes closer to the QRD1114, the voltage on A0 should go down.

4x addressable (single pin) RGB LEDs (https://www.sparkfun.com/products/12986) - $2.36 for five
Flat side down, top to bottom is digital in, 5v, ground, digital out
use adafruit library to talk to the circuit in the LED, send values for Green, Red, Blue

Misc wire bits cannabilized out of old network cable
12x 330 ohm resistors for LEDs/infrared emitters
heat shrink tubing from home depot: $2

**********************/

// Setup Lane sensors (IR emitter/detector)
const int LANE1_SENSOR_PIN = A0; // Sensor outputs voltage, must be pulled up to 5v
const int LANE2_SENSOR_PIN = A1; 
const int LANE3_SENSOR_PIN = A2; 
const int LANE4_SENSOR_PIN = A3; 

// Setup finish line RGB LEDs (num_leds, pin, type by instantiating objects (constructors)
Adafruit_NeoPixel led1 = Adafruit_NeoPixel(1, 2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led2 = Adafruit_NeoPixel(1, 3, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led3 = Adafruit_NeoPixel(1, 4, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led4 = Adafruit_NeoPixel(1, 5, NEO_RGB + NEO_KHZ800);

// Misc globals
  const int DIFF = 10; // How much drop do we want to see before triggering a finish? (in DELAY milliseconds)
  const int DELAY = 1;  // loop delay. DIFF drop has to happen within this time (not spread out, slow will not trip)
  const int START_WAIT = 2000; // how long (millis) to rest/calibrate on startup before checking for cars?
  unsigned long loopIndex = 0; // how many times through the loop so far?
  int lane1Old = 0; // previous voltage/value for lane1 (compare to new for DIFF drop)
  int lane2Old = 0;
  int lane3Old = 0;
  int lane4Old = 0;
  unsigned long lane1Finished = 0; // Did lane 1 car cross yet? at which loop count?
  unsigned long lane2Finished = 0;
  unsigned long lane3Finished = 0;
  unsigned long lane4Finished = 0;
  int finishedCount = 0; // how many cars finished? (hopefully between 0 and 4)
  
void setup() {
  Serial.begin(9600); // set baud for writing back to terminal/computer
  // set sensors to PULLUP 5v so they start at 1024 and drop as they detect reflection of IR
  pinMode(LANE1_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LANE2_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LANE3_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LANE4_SENSOR_PIN, INPUT_PULLUP);

  delay(START_WAIT);  

  led1.begin(); // This initializes the NeoPixel library for the LED
  led1.setPixelColor(0,0,0,0);  // turn off the LED
  led1.show();  // send to LED
  led2.begin();
  led2.setPixelColor(0,0,0,0);
  led2.show();
  led3.begin();
  led3.setPixelColor(0,0,0,0);
  led3.show();
  led4.begin();
  led4.setPixelColor(0,0,0,0);
  led4.show();
}

void loop() {
  // todo : Add some baselineing/calibration on first iteration, getting loest value durnig setup maybe after a few samples?
  // todo : Measure lag between checking lanes assuming finishes? Optimize? maybe move lights out until end of loop?
  // todo : add some status LED on side? (ready/error?)
  // On reset/startup let's wait/calibrate for a few tics

  // ---------- Check Lane 1 ------------------------------  
  int lane1New = analogRead(LANE1_SENSOR_PIN); //Read in the ADC from lane 1 sensor
  Serial.print("Lane 1: ");
  Serial.println(lane1New);
  
  // Compare to old value. is it lower by more than diff, and never finished yet?
  if ((lane1Old > 0) and !lane1Finished and ((lane1Old - lane1New) > DIFF)) {
    if (finishedCount == 0) {  // Congratulations, First Place (Green)
      led1.setPixelColor(0,0,150,0);
    }
    else if (finishedCount == 1) {  // Second Place (Blue)
      led1.setPixelColor(0,0,0,150);
    }    
    else if (finishedCount == 2) {  // Third Place (Yellow)
      led1.setPixelColor(0,150,200,0);
    }    
    else if (finishedCount == 3) {  // Fourth Place (Red)
      led1.setPixelColor(0,150,5,5);
    }    
    led1.show(); // This sends the updated color to the hardware.
    finishedCount++;
    lane1Finished = loopIndex;
    Serial.print("Lane 1 Finished at loop index: " );
    Serial.println(loopIndex);
  }
  lane1Old = lane1New;
  
  // ---------- Check Lane 2 ------------------------------  
  int lane2New = analogRead(LANE2_SENSOR_PIN); //Read in the ADC from lane 2 sensor
//  Serial.print("Lane 2: ");
//  Serial.println(lane2New);

  if ((lane2Old > 0) and !lane2Finished and ((lane2Old - lane2New) > DIFF)) {
    if (finishedCount == 0) {  // Congratulations, First Place (Green)
      led2.setPixelColor(0,0,150,0);
    }
    else if (finishedCount == 1) {  // Second Place (Blue)
      led2.setPixelColor(0,0,0,150);
    }    
    else if (finishedCount == 2) {  // Third Place (Yellow)
      led2.setPixelColor(0,150,200,0);
    }    
    else if (finishedCount == 3) {  // Fourth Place (Red)
      led2.setPixelColor(0,150,0,0);
    }    
    led2.show(); // This sends the updated color to the hardware.
    finishedCount++;
    lane2Finished = loopIndex;
    Serial.print("Lane 2 Finished at loop index: " );
    Serial.println(loopIndex);
  }
  lane2Old = lane2New;
  
  // ---------- Check Lane 3 ------------------------------    
  int lane3New = analogRead(LANE3_SENSOR_PIN); //Read in the ADC from lane 3 sensor
//  Serial.print("Lane 3: ");
//  Serial.println(lane3New);

  if ((lane3Old > 0) and !lane3Finished and ((lane3Old - lane3New) > DIFF)) {
    if (finishedCount == 0) {  // Congratulations, First Place (Green)
      led3.setPixelColor(0,0,150,0);
    }
    else if (finishedCount == 1) {  // Second Place (Blue)
      led3.setPixelColor(0,0,0,150);
    }    
    else if (finishedCount == 2) {  // Third Place (Yellow)
      led3.setPixelColor(0,150,200,0);
    }    
    else if (finishedCount == 3) {  // Fourth Place (Red)
      led3.setPixelColor(0,150,0,0);
    }    
    led3.show(); // This sends the updated color to the hardware.
    finishedCount++;
    lane3Finished = loopIndex;
    Serial.print("Lane 3 Finished at loop index: " );
    Serial.println(loopIndex);
  }
  lane3Old = lane3New;
  
  // ---------- Check Lane 4 ------------------------------    
  int lane4New = analogRead(LANE4_SENSOR_PIN); //Read in the ADC from lane 3 sensor
//  Serial.print("Lane 4: ");
//  Serial.println(lane4New);

  if ((lane4Old > 0) and !lane4Finished and ((lane4Old - lane4New) > DIFF)) {
    if (finishedCount == 0) {  // Congratulations, First Place (Green)
      led4.setPixelColor(0,0,150,0);
    }
    else if (finishedCount == 1) {  // Second Place (Blue)
      led4.setPixelColor(0,0,0,150);
    }    
    else if (finishedCount == 2) {  // Third Place (Yellow)
      led4.setPixelColor(0,150,200,0);
    }    
    else if (finishedCount == 3) {  // Fourth Place (Red)
      led4.setPixelColor(0,150,0,0);
    }    
    led4.show(); // This sends the updated color to the hardware.
    finishedCount++;
    lane4Finished = loopIndex;
    Serial.print("Lane 4 Finished at loop index: " );
    Serial.println(loopIndex);
  }
  lane4Old = lane4New;
//  delay(DELAY);
}
