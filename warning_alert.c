// #include "settings.h"


int buzzer_tone_val = 500; // modify this value to change output tone/ frequency
int alert_status=0;
int warning_Buzzer = 9; // 8-ohm speaker on digital pin 9
int warning_LED = 13; // pin number assigned tentativel. may need to change depending on LCD connection.

int getStatus(); // returns a corresponding alert flag for a specified threshold (defined elsewhere)
  //  - 0 = normal
  //  - 1 = high (alert)

/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

void setup()
{
  pinMode(warning_LED, OUTPUT); // Warning LED  connected to pin 'warning_LED'
  pinMode(warning_Buzzer, OUTPUT); // 8-ohm speaker on digital pin 'warning_Buzzer'
}

void loop()
{

delay(1000); // Wait for 1000 millisecond(s)
alert_status = getStatus;

if (alert_status==1)
  {
  // LED ON
  digitalWrite(warning_LED, HIGH);  // LED turned ON
  
                    /* Blinking mode
                      // turn the LED on (HIGH is the voltage level)
                    digitalWrite(warning_LED, HIGH);
                    delay(500); // Wait for 500 millisecond(s)
                    // turn the LED off by making the voltage LOW
                    digitalWrite(warning_LED, LOW);
                    delay(500); // Wait for 500 millisecond(s)
                    */
  // BUZZER ON 
  
  // map the sensor reading to a range for the speaker
  tone(9, 440 * pow(2.0, (constrain(int(map(buzzer_tone_val, 0, 1023, 36, 84)), 35, 127) - 57) / 12.0), 1000);
  delay(10); // Delay a little bit to improve simulation performance
    }
else
  {
  digitalWrite(warning_LED, LOW); // LED turned OFF
  }
  
}



