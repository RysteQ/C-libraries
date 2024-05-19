#include "simpio.h"

/// @brief Gets a char input from the user
char GetChar() {
    char value;

    scanf("%c", &value);

    return value;    
}

/// @brief Gets a short input from the user
short GetShort() {
    short value;

    scanf("%s", &value);

    return value;    
}

/// @brief Gets a int input from the user
int GetInt() {
    int value;

    scanf("%i", &value);

    return value;    
}

/// @brief Gets a long input from the user
long GetLong() {
    long value;

    scanf("%lli", &value);

    return value;    
}

/// @brief Gets a float input from the user
float GetFloat() {
    float value;

    scanf("%f", &value);

    return value;    
}

/// @brief Gets a double input from the user
double GetDouble() {
    double value;

    scanf("%d", &value);

    return value;    
}
