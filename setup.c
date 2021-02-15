// General setup File

//Tempature Functions headers
float celToFrah(float);
float frahToCel(float);
int getTemp();
int getStatus();  

int sensorValue = 0; //potentiometer sensor value
int pot = A0; //potentiometer pin
int temp = 32; //temperature;

void setup()
{
  pinMode(A0, INPUT);
}

//Tempature Functions 
float celToFrah(float Celsius) {
    float Fahrenheit = (9.0/5.0)*(Celsius) + 32.0; 
    return Fahrenheit;
}

float frahToCel(float Fahrenheit) {
    float Celsius = (5.0/9.0)*(Fahrenheit - 32.0);
    return Celsius;
}

int getTemp(){
  sensorValue = analogRead(A0);// read the input of the potentiometer (0 - 1023)
  temp = .1173*sensorValue; // scale to F
  return temp;
}

int getStatus(){ // gets the current status 
  if(getTemp() > 100){
    return 1;
  }
  return 0;
}
