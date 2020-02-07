/*
  
 
 This example code is in the public domain.
 */
#include <SoftwareSerial.h>
#include <SparkFunDS1307RTC.h>
#include <Wire.h>
SoftwareSerial mySerial(12, 11); // RX, TX
////RTC definitions
#define PRINT_USA_DATE

#define SQW_INPUT_PIN 2   // Input pin to read SQW
#define SQW_OUTPUT_PIN 13 // LED to indicate SQW's state
byte inByte;

long startTime;
int counter=1;
void setup() {
  // initialize serial:
  Serial.begin(9600);
  mySerial.begin(9600);
 ////RTC functions
 
 //RTC functions
   pinMode(SQW_INPUT_PIN, INPUT_PULLUP);
  pinMode(SQW_OUTPUT_PIN, OUTPUT);
  digitalWrite(SQW_OUTPUT_PIN, digitalRead(SQW_INPUT_PIN));
  //uncomment below to set time
  /*
  rtc.begin(); // Call rtc.begin() to initialize the library
  // (Optional) Sets the SQW output to a 1Hz square wave.
  // (Pull-up resistor is required to use the SQW pin.)
  rtc.writeSQW(SQW_SQUARE_1);

  // Now set the time...
  // You can use the autoTime() function to set the RTC's clock and
  // date to the compiliers predefined time. (It'll be a few seconds
  // behind, but close!)
  rtc.autoTime();
  // Or you can use the rtc.setTime(s, m, h, day, date, month, year)
  // function to explicitly set the time:
  // e.g. 7:32:16 | Monday October 31, 2016:
  rtc.setTime(16, 36, 14, 2, 05, 02, 20);  // Uncomment to manually set time
  // rtc.set12Hour(); // Use rtc.set12Hour to set to 12-hour mode
*/

}

void loop() {

//RTC functions
static int8_t lastSecond = -1;
  
  // Call rtc.update() to update all rtc.seconds(), rtc.minutes(),
  // etc. return functions.
  rtc.update();
///endRTC
  
writeA();
//Serial.println("a");
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int unitNum = Serial.parseInt(); 
    // do it again:
    int flow = Serial.parseInt(); 
    // do it again:
    int temp = Serial.parseInt(); 
   // printTime();
 Serial.print(String(rtc.hour()) + ":"); // Print hour
  if (rtc.minute() < 10)
    Serial.print('0'); // Print leading '0' for minute
  Serial.print(String(rtc.minute()) + ":"); // Print minute
  if (rtc.second() < 10)
    Serial.print('0'); // Print leading '0' for second
  Serial.print(String(rtc.second())); // Print second
  Serial.print(",");
   ///
    Serial.print(unitNum);
    Serial.print(",");
    Serial.print(flow);
    Serial.print(",");
    Serial.println(temp);
    mySerial.print(unitNum);
    mySerial.print(",");
    mySerial.print(flow);
    mySerial.print(",");
    mySerial.println(temp);
    // look for the newline. That's the end of your
    // sentence:
    /*if (Serial.read() == '\n') {}*/
  }
  
}

void writeA()
{
  if(millis()-startTime>3000&& counter==1)
  {
  Serial.println('a');
  startTime=millis();
  }
  /*
  if(millis()-startTime>3000&& counter==2)
  {
  Serial.println('b');
  startTime=millis();
  }
  if(millis()-startTime>3000&& counter==3)
  {
  Serial.println('c');
  startTime=millis();
  }
  if(millis()-startTime>3000&& counter==4)
  {
  Serial.println('d');
  startTime=millis();
  }
 counter++; */
}



void printTime()
{
  Serial.print(String(rtc.hour()) + ":"); // Print hour
  if (rtc.minute() < 10)
    Serial.print('0'); // Print leading '0' for minute
  Serial.print(String(rtc.minute()) + ":"); // Print minute
  if (rtc.second() < 10)
    Serial.print('0'); // Print leading '0' for second
  Serial.print(String(rtc.second())); // Print second

  if (rtc.is12Hour()) // If we're in 12-hour mode
  {
    // Use rtc.pm() to read the AM/PM state of the hour
    if (rtc.pm()) Serial.print(" PM"); // Returns true if PM
    else Serial.print(" AM");
  }
  
  Serial.print(" | ");

  // Few options for printing the day, pick one:
  Serial.print(rtc.dayStr()); // Print day string
  //Serial.print(rtc.dayC()); // Print day character
  //Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)
  Serial.print(" - ");
#ifdef PRINT_USA_DATE
  Serial.print(String(rtc.month()) + "/" +   // Print month
                 String(rtc.date()) + "/");  // Print date
#else
  Serial.print(String(rtc.date()) + "/" +    // (or) print date
                 String(rtc.month()) + "/"); // Print month
#endif
  Serial.println(String(rtc.year()));        // Print year
 /* Serial.print(String(rtc.year()));        // replaced comment line above
  Serial.print(",");*/
}





