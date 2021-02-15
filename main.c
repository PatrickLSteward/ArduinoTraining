// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



//function to convert from C to F
float celToFrah(float Celsius) {	
    float Fahrenheit = (9.0/5.0)*(Celsius) + 32.0; 
    mode = 'F'; // sets mode to Fahrenheit
    return Fahrenheit;
}

//funcion to conver F to C
float frahToCel(float Fahrenheit) {
    float Celsius = (5.0/9.0)*(Fahrenheit - 32.0);
    mode = 'C'; // sets mode to Celsius
    return Celsius;
}

//converts temp from potentiometer
float getTemp(){
  int sensorValue = 0;
  sensorValue = analogRead(A0);// read the input of the potentiometer (0 - 1023)
  temp = .1173*sensorValue; // scale to F
  mode = 'F';
  return temp;
}

// gets the current status
int getStatus(){  
  if(getTemp() > 100){
    return 1;
  }
  return 0;
}

//Temp display funcion
void lcdDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(mode);
  
  lcd.setCursor(0, 1);
  if(getStatus()==1)
    lcd.print("Alr: OVERHEATING");
}

//button pin
const int buttonPin = 2;   
//warning light pin
int warning_LED = 13; 
// 8-ohm speaker on digital pin 9
int warning_Buzzer = 9;
// modify this value to change output tone/ frequency
int buzzer_tone_val = 500; 
//potentiometer pin
int pot = A0; 
// the current reading from the input pin
int buttonState;    
// the previous reading from the input pin
int lastButtonState = LOW;   
// current alert status
int alert_status=0;	   


unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // pin for the button
  pinMode(buttonPin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
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
 
    //Buttton to switch reading
    int reading = digitalRead(buttonPin);
    if (reading != lastButtonState) {
	// reset the debouncing timer
	lastDebounceTime = millis();
	lcd.begin(16, 2);
	lcd.print("OVERHEATEd");
	lcd.setCursor(0, 1);
	lcd.print(getTemp);
	lcd.print(mode);
	}

	if ((millis() - lastDebounceTime) > debounceDelay) {
		if (reading != buttonState) {
			buttonState = reading;
			// only toggle the LED if the new button state is HIGH
			if (buttonState == HIGH) {
				lcd.begin(16, 2);
				lcd.print("OVERHEATEd");
				lcd.setCursor(0, 1);
				lcd.print(frahToCel(getTemp);
				lcd.print(mode);
				}			 
		}	
	}
  lastButtonState = reading;
					
					
}
else{
  digitalWrite(warning_LED, LOW); // LED turned OFF	
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin)
	if (reading != lastButtonState) {
		// reset the debouncing timer
		lastDebounceTime = millis();
		lcd.begin(16, 2);
		lcd.setCursor(0, 1);
		lcd.print(getTemp);
		lcd.print(mode);
		}	
	if ((millis() - lastDebounceTime) > debounceDelay) {
			if (reading != buttonState) {
				buttonState = reading;
					if (buttonState == HIGH) {
						lcd.begin(16, 2);
						lcd.setCursor(0, 1);
						lcd.print(frahToCel(getTemp);
						lcd.print(mode);	
					}	
			}
	}	
	lastButtonState = reading;
}
}
