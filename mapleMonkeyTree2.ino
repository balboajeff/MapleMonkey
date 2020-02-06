#include <SoftwareSerial.h>
#include "SparkFunTMP102.h" 
SoftwareSerial mySerial(10, 11); // RX, TX
////////TMP102

// Connections
// VCC = 3.3V
// GND = GND
// SDA = A4
// SCL = A5
const int ALERT_PIN = A3;

TMP102 sensor0(0x48); // Initialize sensor at I2C address 0x48
// Sensor address can be changed with an external jumper to:
// ADD0 - Address
//  VCC - 0x49
//  SDA - 0x4A
//  SCL - 0x4B
//////End TMP102
bool pin1;
bool pin2;
bool pin3;
bool pin4;
bool pin5;
bool pin6;
bool pin7;
int flow = 0;
String inChar;
void setup()
{
  pinMode(3, INPUT_PULLUP); //pin1
  pinMode(4, INPUT_PULLUP); //pin2
  pinMode(5, INPUT_PULLUP); //pin3
  pinMode(6, INPUT_PULLUP); //pin4
  pinMode(7, INPUT_PULLUP); //pin5
  pinMode(8, INPUT_PULLUP); //pin6
  pinMode(9, INPUT_PULLUP); //pin7
  Serial.begin(9600);
  //SoftwareSerial.begin(9600);
///////TMP 102
 pinMode(ALERT_PIN,INPUT);  // Declare alertPin as an input
  sensor0.begin();  // Join I2C bus

  // Initialize sensor0 settings
  // These settings are saved in the sensor, even if it loses power

  // set the number of consecutive faults before triggering alarm.
  // 0-3: 0:1 fault, 1:2 faults, 2:4 faults, 3:6 faults.
  sensor0.setFault(0);  // Trigger alarm immediately

  // set the polarity of the Alarm. (0:Active LOW, 1:Active HIGH).
  sensor0.setAlertPolarity(1); // Active HIGH

  // set the sensor in Comparator Mode (0) or Interrupt Mode (1).
  sensor0.setAlertMode(0); // Comparator Mode.

  // set the Conversion Rate (how quickly the sensor gets a new reading)
  //0-3: 0:0.25Hz, 1:1Hz, 2:4Hz, 3:8Hz
  sensor0.setConversionRate(2);

  //set Extended Mode.
  //0:12-bit Temperature(-55C to +128C) 1:13-bit Temperature(-55C to +150C)
  sensor0.setExtendedMode(0);

  //set T_HIGH, the upper limit to trigger the alert on
  sensor0.setHighTempF(85.0);  // set T_HIGH in F
  //sensor0.setHighTempC(29.4); // set T_HIGH in C

  //set T_LOW, the lower limit to shut turn off the alert
  sensor0.setLowTempF(84.0);  // set T_LOW in F
  //sensor0.setLowTempC(26.67); // set T_LOW in C
//////end TMP102
}

void loop()
{
  readPins();
  if (Serial.available() > 0)
  {
    inChar = Serial.readStringUntil('\r');
             if (inChar == "a")
    {
    //Serial.println(inChar);
      Serial.print(flow);
      getTemp();
    }
  }
}

void readPins()
{
  pin1 = digitalRead(3);
  pin2 = digitalRead(4);
  pin3 = digitalRead(5);
  pin4 = digitalRead(6);
  pin5 = digitalRead(7);
  pin6 = digitalRead(8);
  pin7 = digitalRead(9);

  if (pin1 == 1 && pin2 == 1 && pin3 == 1 && pin4 == 1 && pin5 == 1 && pin6 == 1 && pin7 == 1)
  {
    flow = 0;
  }
  if (pin1 == 0 && pin2 == 1 && pin3 == 1 && pin4 == 1 && pin5 == 1 && pin6 == 1 && pin7 == 1)
  {
    flow = 1;
  }
  if (pin1 == 0 && pin2 == 0 && pin3 == 1 && pin4 == 1 && pin5 == 1 && pin6 == 1 && pin7 == 1)
  {
    flow = 2;
  }
  if (pin1 == 0 && pin2 == 0 && pin3 == 0 && pin4 == 1 && pin5 == 1 && pin6 == 1 && pin7 == 1)
  {
    flow = 3;
  }
  if (pin1 == 0 && pin2 == 0 && pin3 == 0 && pin4 == 0 && pin5 == 1 && pin6 == 1 && pin7 == 1)
  {
    flow = 4;
  }
  if (pin1 == 0 && pin2 == 0 && pin3 == 0 && pin4 == 0 && pin5 == 0 && pin6 == 1 && pin7 == 1)
  {
    flow = 5;
  }
  if (pin1 == 0 && pin2 == 0 && pin3 == 0 && pin4 == 0 && pin5 == 0 && pin6 == 0 && pin7 == 1)
  {
    flow = 6;
  }
  if (pin1 == 0 && pin2 == 0 && pin3 == 0 && pin4 == 0 && pin5 == 0 && pin6 == 0 && pin7 == 0)
  {
    flow = 7;
  }
  /* word boolNum =(pin1 + pin2 + pin3 + pin4 + pin5);
    Serial.println(boolNum);
  */
}

void getTemp()
{
  float temperature;
  boolean alertPinState, alertRegisterState;

  // Turn sensor on to start temperature measurement.
  // Current consumtion typically ~10uA.
  sensor0.wakeup();

  // read temperature data
  temperature = sensor0.readTempF();
  //temperature = sensor0.readTempC();

  // Check for Alert
  alertPinState = digitalRead(ALERT_PIN); // read the Alert from pin
  alertRegisterState = sensor0.alert();   // read the Alert from register

  // Place sensor in sleep mode to save power.
  // Current consumtion typically <0.5uA.
  sensor0.sleep();

  // Print temperature and alarm state
  //Serial.print("Temperature: ");
  Serial.print(", ");
  Serial.println(temperature);

  //Serial.print("\tAlert Pin: ");
  //Serial.print(alertPinState);

  //Serial.print("\tAlert Register: ");
  //Serial.println(alertRegisterState);
}


