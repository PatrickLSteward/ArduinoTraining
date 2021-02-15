// General setup File

//Tempature Functions headers
float celToFrah(float);
float frahToCel(float);
float getTemp(); // changed from into to float 
int getStatus();  

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
