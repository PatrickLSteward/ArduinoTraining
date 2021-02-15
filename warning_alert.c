// #include "settings.h"



int alert_status=0;
int warning_LED = 13; // pin number assigned tentativel. may need to change depending on LCD connection.

int getStatus(); // reurns a corresponding alert flag for a specified threshold
  //  - 0 = normal
  //  - 1 = high (alert)

/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

void setup()
{
  pinMode(warning_LED, OUTPUT);
}

void loop()
{

delay(1000); // Wait for 1000 millisecond(s)
alert_status = getStatus;

if (alert_status==1)
  {
  digitalWrite(warning_LED, HIGH);  // LED turned ON
  
                    /* Blinking mode
                      // turn the LED on (HIGH is the voltage level)
                    digitalWrite(warning_LED, HIGH);
                    delay(500); // Wait for 500 millisecond(s)
                    // turn the LED off by making the voltage LOW
                    digitalWrite(warning_LED, LOW);
                    delay(500); // Wait for 500 millisecond(s)
                    */
  
    }
else
  {
  digitalWrite(warning_LED, LOW); // LED turned OFF
  }
  
}
