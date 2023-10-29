#include <stdio.h>
#include <stdlib.h>

float celsius(float fahrenheit)
{
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}

float fahrenheit(float celsius) {
    return celsius * (9.0 / 5.0) + 32.0;
}

typedef float (*degreeConverter)(float);

degreeConverter getTemperatureConverter(char inputUnit)
{
    degreeConverter func;
    
    if (inputUnit == 'F') {
        func = &celsius;
        printf("Fahrenheit  to  Celsius\n");
    } else if (inputUnit == 'C') {
        func = &fahrenheit;
        printf("Celsius  to  Fahrenheit\n");
    } else { return NULL; }

    return func;
}
