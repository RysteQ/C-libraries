#ifndef stringh
#define stringh

/*
* Name: string
* Version: 1.0
* Author: RysteQ
*
* Purpose: The purpose of this library is to have easy access to strings in C
* in an easy and abstract way. 
*
* Performance: Performance should be optimal although I do fear that the
* performance in some methods might drop due to me constantly calling the
* realloc function in a few functions.
*
* Notes: The only thing you should really modify is the SCHAR, although I have
* not tested if this actually works since I don't really need to change it.
*/

#include <stdio.h>
#include <stdlib.h>

typedef char SCHAR;

typedef struct string {
    SCHAR* data;
    unsigned int length;
} string;

typedef struct string_list {
    string* tokens;
    unsigned int count;
} string_list;

string CreateEmptyString();
string CreateString(const SCHAR* value);
void PrintString(string value);
void FreeString(string* to_free);
void FreeStringList(string_list* to_free);
string CopyString(string to_copy);
string ConcatString(string first_string, string second_string);
string FormatString(string to_format, string to_format_with[]);
string SubString(string to_substring, int start, int count);
string TrimString(string to_trim, SCHAR character);
string TrimStartString(string to_trim, SCHAR character);
string TrimEndString(string to_trim, SCHAR character);
string RemoveStringFromString(string to_remove_from, string to_remove);
string RemoveCharFromString(string to_remove_from, SCHAR to_remove);
string PadString(string to_pad, SCHAR character, int count);
string PadStartString(string to_pad, SCHAR character, int count);
string PadEndString(string to_pad, SCHAR character, int count);
string_list SplitString(string to_split, SCHAR splitter);

#endif