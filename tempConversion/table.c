#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "tempConvert.c"

#define UPPER 150
#define STEP  10
#define LOWER 0
#define helpMsg "Usage:\ttable <end> <step> <start>\n"\
                "Default args: -S 10 -e 150 -s 0\n"\
                "--step,  -S: <int>\n"\
                "--start, -s: <int>\n"\
                "--end,   -e: <int>\n"\
                "--celsius,     -f\n"\
                "--fahrenheit,  -f\n"\


int celsiusTable(int start, int end, int step);
int fahrenheitTable(int start, int end, int step);
int tempTable(char inputUnit, int end, int step, int start);


int main(int argc, char *argv[])
{
    float fahr, cels;

    int end, start, step;
    end = UPPER;
    step = STEP;
    start = LOWER;

    int fOption, cOption;
    fOption = 0;
    cOption = 0;

    struct option long_options[] = {
        { "start",  required_argument,  NULL, 's' },
        { "end",    required_argument,  NULL, 'e' },
        { "step",   required_argument,  NULL, 'S' },
        { "fahrenheit",  no_argument,  NULL, 'f' },
        { "celsius",  no_argument,  NULL, 'c' },
        { "help",  no_argument,  NULL, 'h' },
        { 0, 0, 0, 0 }
    };


    int optIndex, option;
    const char * optstring = "s:e:S:hfc";

    while ((option = getopt_long(argc, argv, optstring, long_options, &optIndex)) != -1) {
        switch (option) {
            case 's':
                printf("%d", atoi(optarg));
                start = atoi(optarg);
                break;
            case 'e':
                end = atoi(optarg);
                break;
            case 'S':
                step = atoi(optarg);
                break;
            case 'f':
                fOption = 1;
                break;
            case 'c':
                cOption = 1;
                break;
            case 'h':
                printf(helpMsg);
                return EXIT_SUCCESS;
                break;
        }
    }

    if (end - start < step) {
        puts("Invalid options:  <step> larger than total range");
        return EXIT_SUCCESS;
    }

    // Generate tables
    if (fOption == 1) { fahrenheitTable(start, end, step); }
    if (cOption == 1) { celsiusTable(start, end, step); }
    if (fOption != 1 && cOption != 1) {
        fahrenheitTable(start, end, step);
        celsiusTable(start, end, step);
    }

    return EXIT_SUCCESS;
}

int tempTable(char inputUnit, int end, int step, int start)
{
    float degrees;
    degreeConverter convert;
    inputUnit = toupper(inputUnit);

    /* Get function pointer to one of:
     * fahrenheit()
     * celsius() */
    convert = getTemperatureConverter(inputUnit);
    
    // Either: Upwards
    for (degrees = start; degrees <= end; degrees = degrees + step) {
        printf("%6.1f\t\t%6.1f\n", degrees, convert(degrees));
    }
    // Or: Downwards
    for (degrees = start; degrees >= end; degrees = degrees - step){
        printf("%6.1f\t\t%6.1f\n", degrees, convert(degrees));
    }
    return EXIT_SUCCESS;
}

int celsiusTable(int start, int end, int step)
{
    return tempTable('C', end, step, start);
}

int fahrenheitTable(int start, int end, int step)
{
    return tempTable('F', end, step, start);
}
