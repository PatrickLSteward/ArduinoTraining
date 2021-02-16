/*
  LiquidCrystal Library - Hello World
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 This sketch prints "Hello World!" to the LCD
 and shows the time.
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int overHeat = 0;
int prevTemp = 0;
int modeState = 0; // 0 = F, 1 = C
int pot = A0; //potentiometer pin
float temp = 125.0;
char mode = 'F';
int buttonPin = 7; // buttonPin
int buttonState; //current button reading
int lastButtonState = LOW; //previous button reading


int getStatus()
{ 
  if(temp>=100)
    return 1;
  //else if(mode=='C' && temp>= 37.7778)
    //return 1;
  return 0;
}

float frahToCel(float Fahrenheit) {
    float Celsius = (5.0/9.0)*(Fahrenheit - 32.0);
    mode = 'C'; // sets mode to celsius
    return Celsius;
}

float getTemp(){
  int sensorValue = 0; //potentiometer sensor value
  sensorValue = analogRead(A0);// read the input of the potentiometer (0 - 1023)
  temp = .1173*sensorValue; // scale to F
  //lcd.clear();
  return temp;
}
void checkWarning()
{ // Warning_Alert - Variables
	int buzzer_tone_val = 500; // modify this value to change output tone/ frequency
	int alert_status=1;
	int warning_Buzzer = 9; // 8-ohm speaker on digital pin 9
	int warning_LED = 13; // Buzzer connected to pin 13


  // Warning_alert (Buzzer, LED)
  alert_status = getStatus();
  if (alert_status==1){
   digitalWrite(warning_LED, HIGH);  // LED turned ON               
  // BUZZER ON (map the buzzer_tone_val to a range for the speaker)
  tone(9, 440 * pow(2.0, (constrain(int(map(buzzer_tone_val, 0, 1023, 36, 84)), 35, 127) - 57) / 12.0), 1000);
 // delay(10); // Delay a little bit to improve simulation performance
   }
  else {
  digitalWrite(warning_LED, LOW); // LED turned OFF
  // BUZZER OFF (map the ZERO to a range for the speaker)
  tone(9, 0 * pow(2.0, (constrain(int(map(0, 0, 1023, 36, 84)), 35, 127) - 57) / 12.0), 1000);
  }
}

void lcdDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  if(mode == 'F'){
    lcd.print(temp);
  }
  else{
    lcd.print(frahToCel(temp));
  }
  lcd.print(mode);
  
  lcd.setCursor(0, 1);
  if((temp < 10 && prevTemp >= 10)){
    lcd.clear();
  }
  if(mode == 'C'){
    int cont = 1; //flag variable denoting whether or not the first if statement was true
    if(frahToCel(temp) >-10 && frahToCel(prevTemp) <=-10){
      lcd.clear();
      cont = 0;
    }
    if(cont ==1 && (frahToCel(temp) > 0 && frahToCel(prevTemp) <= 0)){
      lcd.clear();
    }
  }
  if(getStatus()==1){
    lcd.print("Alr: OVERHEATING");
    overHeat = 1;
  }
  else{
    //delay(2000);
    if(overHeat == 1){
    	lcd.clear();
        overHeat = 0;
    }
  }
  prevTemp = temp;
}

void button(){
 //Serial.println(mode); 
 int reading = digitalRead(buttonPin);
 if (reading != buttonState) {
      buttonState = reading;
     
      if (buttonState == HIGH) {
       
        if(modeState == 0){
           mode = 'C';
           modeState = 1;
           lcd.clear();
        }
        else{
          mode = 'F';
          modeState = 0;
          lcd.clear();
        }
        Serial.println(mode);
      }
  		//else{
    		//mode = 'F';
  	  //}
    }
  lastButtonState = reading;
  Serial.println(mode);
}


// Warning_Alert - Variables
int buzzer_tone_val = 500; // modify this value to change output tone/ frequency
int alert_status=1;
int warning_Buzzer = 9; // Buzzer on digital pin 9
int warning_LED = 13; // Red LED connected to pin 13



void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(pot, INPUT); //potentiometer 
  pinMode(warning_LED, OUTPUT); // Warning LED 
  pinMode(warning_Buzzer, OUTPUT); // Buzzer
  pinMode(buttonPin, INPUT); //buttonPin
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  getTemp();
  button();
  lcdDisplay();
  checkWarning();
}
