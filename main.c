  // include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//function to convert from C to F
float celToFrah(float Celsius) {
    float Fahrenheit = (9.0/5.0)*(Celsius) + 32.0; 
    return Fahrenheit;
}

//funcion to conver F to C
float frahToCel(float Fahrenheit) {
    float Celsius = (5.0/9.0)*(Fahrenheit - 32.0);
    return Celsius;
}

//converts temp from potentiometer
int getTemp(){
  sensorValue = analogRead(A0);// read the input of the potentiometer (0 - 1023)
  temp = .1173*sensorValue; // scale to F
  return temp;
}
// gets the current status
int getStatus(){  
  if(getTemp() > 100){
    return 1;
  }
  return 0;
}


//button pin
const int buttonPin = 2;   
//warning light pin
int warning_LED = 13; 
// modify this value to change output tone/ frequency
int buzzer_tone_val = 500; 
//potentiometer pin
int pot = A0; 



int ledState = HIGH;         // the current state of the output pin...will be changed to current temp reading
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int alert_status=0;			 // current alert status


// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // pin for the button
  pinMode(buttonPin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("NORMAL");
  // pin for Alert LED
  pinMode(warning_LED, OUTPUT);
  // 8-ohm speaker on digital pin 'warning_Buzzer'
  pinMode(warning_Buzzer, OUTPUT); 
  //Potentiometer pin
  pinMode(A0, INPUT);
  
}
  


void loop() {
	delay(1000); 

if(getStatus == 1){
	digitalWrite(warning_LED, HIGH);  // LED turned ON
      /* Blinking mode
      // turn the LED on (HIGH is the voltage level)
      digitalWrite(warning_LED, HIGH);
      delay(500); // Wait for 500 millisecond(s)
      // turn the LED off by making the voltage LOW
      digitalWrite(warning_LED, LOW);
      delay(500); // Wait for 500 millisecond(s)
      */
      // read the state of the switch into a local variable:
	
	// BUZZER ON 
    // map the sensor reading to a range for the speaker
    tone(9, 440 * pow(2.0, (constrain(int(map(buzzer_tone_val, 0, 1023, 36, 84)), 35, 127) - 57) / 12.0), 1000);
	delay(10); // Delay a little bit to improve simulation performance
 
    int reading = digitalRead(buttonPin);

     // check to see if you just pressed the button
     // (i.e. the input went from LOW to HIGH),  and you've waited
     // long enough since the last press to ignore any noise:
     // If the switch changed, due to noise or pressing:
	 if (reading != lastButtonState) {
		// reset the debouncing timer
		lastDebounceTime = millis();
		 lcd.begin(16, 2);
		// Print a message to the LCD.
		lcd.print("OVERHEATED");
		lcd.setCursor(0, 1);
		lcd.print(celToFrah);
		}

	if ((millis() - lastDebounceTime) > debounceDelay) {
		// whatever the reading is at, it's been there for longer
		// than the debounce delay, so take it as the actual current state:
		// if the button state has changed:
		if (reading != buttonState) {
			buttonState = reading;
			// only toggle the LED if the new button state is HIGH
			if (buttonState == HIGH) {
				//ledState = !ledState;
				//add a function to change F to C
				// Print a message to the LCD.
				lcd.print("OVERHEATED");
				lcd.setCursor(0, 1);
				lcd.setCursor(0, 1);
				lcd.print(frahToCel);
				}			 
		}	
	}
 // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
					
					
}
else{
  digitalWrite(warning_LED, LOW); // LED turned OFF	
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
	if (reading != lastButtonState) {
		// reset the debouncing timer
		lastDebounceTime = millis();
		lcd.setCursor(0, 1);
		lcd.print("Temp in F");
		}	

	if ((millis() - lastDebounceTime) > debounceDelay) {
		// whatever the reading is at, it's been there for longer
		// than the debounce delay, so take it as the actual current state:
		// if the button state has changed:
			if (reading != buttonState) {
				buttonState = reading;
				// only toggle the LED if the new button state is HIGH
					if (buttonState == HIGH) {
						//ledState = !ledState;
						//add a function to change F to C
						lcd.setCursor(0, 1);
						lcd.print(frahToCel);
					}	
			}
	}	
	// save the reading.  Next time through the loop,
	// it'll be the lastButtonState:
	lastButtonState = reading;
}
}
