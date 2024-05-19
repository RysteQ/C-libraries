#ifndef simpioh
#define simpioh

/*
* Name: Simpio
* Version: 1.0
* Author: RysteQ
*
* Purpose: Make the boring work of getting input from the user a little bit
* less tedious.
*
* Performance: Who cares, it is literally the scanf function.
*
* Notes: This library does not have file I/O and most likely won't have IO
* anytime soon if at all. I am planning this to be solely a command line input
* library, hence the simpio name which stands for simple I/O.
*/

#include <stdio.h>

char GetChar();
short GetShort();
int GetInt();
long GetLong();
float GetFloat();
double GetDouble();

#endif