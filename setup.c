// General setup File

//Tempature Functions headers
float celToFrah(float);
float frahToCel(float);


int pot = A0; // potentionmeter analog pin


void setup()
{
  pinMode(A0, INPUT);
}

float celToFrah(float Celsius) {
    float Fahrenheit = (9.0/5.0)*(Celsius) + 32.0; 
    return Fahrenheit;
}

float frahToCel(float Fahrenheit) {
    float Celsius = (5.0/9.0)*(Fahrenheit - 32.0);
    return Celsius;
}