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

void setup()
{
  pinMode(A0, INPUT);
}

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
