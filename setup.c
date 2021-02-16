// General setup File

//Tempature Functions headers
float celToFrah(float);
float frahToCel(float);
float getTemp(); // changed from into to float 
int getStatus();  


int prevTemp = 0; // keeps track of the previous temp inorder to regulate display output
int overHeat = 0; // over heat toggle state variable
int sensorValue = 0; //potentiometer sensor value
int pot = A0; //potentiometer pin
float temp = 32.0; //temperature; // initialized to 32.0 but that changes as soon as the potentiometer has a value
char mode = 'F'; // global mode character // this might not be a good practice
// Warning_Alert - Variables
int buzzer_tone_val = 500; // modify this value to change output tone/ frequency
int alert_status=1;
int warning_Buzzer = 9; // 8-ohm speaker on digital pin 9
int warning_LED = 13; // Buzzer connected to pin 13

//Tempature Functions 
float celToFrah(float Celsius) {
    float Fahrenheit = (9.0/5.0)*(Celsius) + 32.0;
    mode = 'F'; // sets mode to Fahrenheit
    return Fahrenheit;
}

float frahToCel(float Fahrenheit) {
    float Celsius = (5.0/9.0)*(Fahrenheit - 32.0);
    mode = 'C'; // sets mode to celsius
    return Celsius;
}

float getTemp(){
  int sensorValue = analogRead(A0);// read the input of the potentiometer (0 - 1023) //added int 
  temp = .1173*sensorValue; // scale to F 
  return temp;
}

int getStatus(){ // gets the current status 
  if(getTemp() > 100){
    return 1;
  }
  return 0;
}

void lcdDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(mode);
  
  lcd.setCursor(0, 1);
  if(temp < 10 && prevTemp >= 10){
    lcd.clear();
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

void checkWarning()
{ 
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

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(pot, INPUT);
  pinMode(warning_LED, OUTPUT); // Warning LED 
  pinMode(warning_Buzzer, OUTPUT); // Buzzer
}
