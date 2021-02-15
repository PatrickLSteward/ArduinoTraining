float celToFrah(float Celsius) {
    float Fahrenheit = (9.0/5.0)*(Celsius) + 32.0; 
    mode = 'F'; // sets mode to Fahrenheit
    return Fahrenheit;
}


float frahToCel(float Fahrenheit) {
    float Celsius = (5.0/9.0)*(Fahrenheit - 32.0);
    mode = 'C'; // sets mode to Celsius
    return Celsius;
}
