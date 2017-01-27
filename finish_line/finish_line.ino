// Pinewood Derby Finish Line
// Daniel Kelemen
// Jan, 2017
// Pack 23 Suffern

/****************
Summary: Read 3 infrared emmitter/sensors for voltage drop/change
As they change, mark them first, second, third place
by lighting up the RGB LED for each lane Green, Yellow, or Red

each time through loop, check 

-------------------------------------
Component list:
Using arduino redboard (https://www.sparkfun.com/products/12757)
3x opitcal detector/phototransisor (https://www.sparkfun.com/products/246)
3x RGB LEDs (https://www.sparkfun.com/products/12986)

Connect a QRD1114, 330 resistor and 10k resistor as follows:

QRD1114 Pin ---- Arduino ---- Resistors
    1              A0      10k Pull-up to 5V
    2              GND
    3                      330 Resistor to 5V
    4              GND

As an object comes closer to the QRD1114, the voltage on A0 should go down.

**********************/

// Setup Lane sensors (IR emitter/detector)
const int LANE1_SENSOR_PIN = A0; // Sensor output voltage
const int LANE2_SENSOR_PIN = A1; 
const int LANE3_SENSOR_PIN = A2; 
const int LANE4_SENSOR_PIN = A3; 

// Setup finish line RGB LEDs (3 pins each :( )
const int LANE1_RED_PIN = 2; // RGB LED
const int LANE1_GREEN_PIN = 3;
const int LANE1_BLUE_PIN = 4; 
const int LANE2_RED_PIN = 5;
const int LANE2_GREEN_PIN = 6;
const int LANE2_BLUE_PIN = 7;
const int LANE3_RED_PIN = 8;
const int LANE3_GREEN_PIN = 9;
const int LANE3_BLUE_PIN = 10;
const int LANE4_RED_PIN = 11;
const int LANE4_GREEN_PIN = 12;
const int LANE4_BLUE_PIN = 13;

// Misc globals
const int DIFF = 50; // How much drop do we want to see before triggering a finish?
const int DELAY = 1;  // loop delay
  int loopInex = 0; // how many times through the loop
  int lane1Old = 0;
  int lane2Old = 0;
  int lane3Old = 0;
  int lane4Old = 0;
  int firstPlaceWinner = 0; // which lane came in first
  int secondPlaceWinner = 0; 
  int thirdPlaceWinner = 0; 
void setup() {

  Serial.begin(9600);
  pinMode(LANE1_SENSOR_PIN, INPUT);
  pinMode(LANE2_SENSOR_PIN, INPUT);
  pinMode(LANE3_SENSOR_PIN, INPUT);
  pinMode(LANE4_SENSOR_PIN, INPUT);
  pinMode(LANE1_RED_PIN, OUTPUT);
  pinMode(LANE1_GREEN_PIN, OUTPUT);
  pinMode(LANE1_BLUE_PIN, OUTPUT);
  pinMode(LANE2_RED_PIN, OUTPUT);
  pinMode(LANE2_GREEN_PIN, OUTPUT);
  pinMode(LANE2_BLUE_PIN, OUTPUT);
  pinMode(LANE3_RED_PIN, OUTPUT);
  pinMode(LANE3_GREEN_PIN, OUTPUT);
  pinMode(LANE4_BLUE_PIN, OUTPUT);
  pinMode(LANE4_RED_PIN, OUTPUT);
  pinMode(LANE4_GREEN_PIN, OUTPUT);
  pinMode(LANE4_BLUE_PIN, OUTPUT);

}

void loop() {

// Check Lane 1  
  //Read in the ADC from lane 1 
  int lane1New = analogRead(LANE1_SENSOR_PIN);
  Serial.println(lane1New);
  
  // Compare to old value
  if ((lane1Old > 100) and ((lane1Old - lane1New) > DIFF)) {
    digitalWrite(LANE1_RED_PIN, HIGH);
  }
  lane1Old = lane1New;
  
// Check Lane 2 
  
  delay(DELAY);

}
