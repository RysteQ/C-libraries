#include "string.h"

/// @brief Allocates a new empty string
string CreateEmptyString() {
    string new_string;

    new_string.data = malloc(sizeof(SCHAR));
    new_string.data[0] = '\0';
    new_string.length = 0;

    return new_string;
}

/// @brief Creates a new string with the specified value
string CreateString(const SCHAR* value) {
    string new_string;

    new_string.length = 0;

    while (value[new_string.length] != '\0')
        new_string.length++;

    new_string.data = malloc(sizeof(SCHAR) * (new_string.length + 1));

    for (int i = 0; i < new_string.length + 1; i++)
        new_string.data[i] = value[i];

    return new_string;
}

/// @brief Prints the specified string to the terminal as is
void PrintString(string value) {
    printf("%s", value.data);
}

/// @brief Frees the memory of the specified string and resets the length
void FreeString(string* to_free) {
    free(to_free->data);
    to_free->length = 0;
}

/// @brief Frees the memory of the specified string list and resets the count
void FreeStringList(string_list* to_free) {    
    for (int i = 0; i < to_free->count; i++)
        FreeString(&to_free->tokens[i]);
    
    free(to_free->tokens);
    to_free->count = 0;
}

/// @brief Returns a copy of a string
string CopyString(string to_copy) {
    string new_string;

    new_string.data = malloc(sizeof(SCHAR) * (to_copy.length + 1));
    new_string.length = to_copy.length;

    for (int i = 0; i < to_copy.length + 1; i++)
        new_string.data[i] = to_copy.data[i];

    return new_string;
}

/// @brief Concats two strings together into a new string
/// @param first_string The left part of the new string
/// @param second_string The right part of the new string
string ConcatString(string first_string, string second_string) {
    string new_string;

    new_string.data = malloc(sizeof(SCHAR) * (first_string.length + second_string.length + 1));
    new_string.length = first_string.length + second_string.length;

    for (int i = 0; i < first_string.length; i++)
        new_string.data[i] = first_string.data[i];

    for (int i = 0; i < second_string.length; i++)
        new_string.data[first_string.length + i] = second_string.data[i];

    return new_string;
}

/// @brief Formats a given string into a new string
/// @param to_format The string to format, the format should look like {x} where x is the index
/// @param to_format_with The array of the strings to replace the placeholders
string FormatString(string to_format, string to_format_with[]) {
    string new_string = CreateEmptyString();
    int format_counter = 0;

    for (int i = 0; i < to_format.length; i++) {
        if (to_format.data[i] == '{') {
            int number = 0;
            char found = 1;
            int j;

            for (j = i + 1; j < to_format.length; j++) {
                if (to_format.data[j] >= '0' && to_format.data[j] <= '9') {
                    number *= 10;
                    number += to_format.data[j] - '0';
                } else if (to_format.data[j] != '}') {
                    found = 0;
                } else {
                    break;
                }
            }

            if (found == 0)
                continue;
            
            i += j - i;

            for (int j = 0; j < to_format_with[number].length; j++) {
                new_string.data = realloc(new_string.data, sizeof(SCHAR) * (new_string.length + 2));
                new_string.data[new_string.length] = to_format_with[number].data[j];
                new_string.data[new_string.length + 1] = '\0';
                new_string.length++;
            }
        } else {
            new_string.data = realloc(new_string.data, sizeof(SCHAR) * (new_string.length + 2));
            new_string.data[new_string.length] = to_format.data[i];
            new_string.data[new_string.length + 1] = '\0';
            new_string.length++;
        }
    }

    return new_string;   
}

/// @brief Returns a slice of the given string as a new string
/// @param start The start index
/// @param count The total amount of characters to read
string SubString(string to_substring, int start, int count) {
    string new_string;

    new_string.data = malloc(sizeof(SCHAR) * (count + 1));
    new_string.length = count;
    new_string.data[count] = '\0';

    for (int i = 0; i < count; i++)
        new_string.data[i] = to_substring.data[start + i];

    return new_string;
}

/// @brief Trims the specified character from the start and end of the given string and returns the result as a new string
string TrimString(string to_trim, SCHAR character) {
    string trim_start = TrimStartString(to_trim, character);
    string result = TrimEndString(trim_start, character);
    
    FreeString(&trim_start);

    return result;
}

/// @brief Trims the specified character from the start of the given string and returns the result as a new string
string TrimStartString(string to_trim, SCHAR character) {
    string new_string;
    int i;

    for (i = 0; i < to_trim.length; i++)
        if (to_trim.data[i] != character)
            break;
    
    new_string.data = malloc(sizeof(SCHAR) * (to_trim.length - i + 1));
    new_string.data[to_trim.length - i] = '\0';
    new_string.length = to_trim.length - i;

    for (int j = i; j < to_trim.length; j++)
        new_string.data[j - i] = to_trim.data[j];

    return new_string;
}

/// @brief Trims the specified character from the end of the given string and returns the result as a new string
string TrimEndString(string to_trim, SCHAR character) {
    string new_string;
    int i;

    for (i = 0; i < to_trim.length; i++)
        if (to_trim.data[to_trim.length - 1 - i] != character)
            break;
    
    new_string.data = malloc(sizeof(SCHAR) * (to_trim.length - i + 1));
    new_string.data[to_trim.length - i] = '\0';
    new_string.length = to_trim.length - i;

    for (int j = 0; j < to_trim.length - i; j++)
        new_string.data[j] = to_trim.data[j];

    return new_string;
}

/// @brief Removes a string from another string and returns the result as a new string
string RemoveStringFromString(string to_remove_from, string to_remove) {
    string new_string = CreateEmptyString();

    for (int i = 0; i < to_remove_from.length; i++) {
        if (to_remove_from.data[i] == to_remove.data[0]) {
            int j;
            
            for (j = 1; j < to_remove.length; j++)
                if (to_remove_from.data[i + j] != to_remove.data[j])
                    break;

            i += j;
        }

        new_string.data = realloc(new_string.data, new_string.length + 2);
        new_string.data[new_string.length] = to_remove_from.data[i];
        new_string.data[new_string.length + 1] = '\0';
        new_string.length++;
    }

    return new_string;
}


/// @brief Removes a character from a string and returns the result as a new string
string RemoveCharFromString(string to_remove_from, SCHAR character) {
    string new_string = CreateEmptyString();

    for (int i = 0; i < to_remove_from.length; i++) {
        if (to_remove_from.data[i] == character)
            continue;
        
        new_string.data = realloc(new_string.data, sizeof(SCHAR) * (new_string.length + 2));
        new_string.data[new_string.length] = to_remove_from.data[i];
        new_string.data[new_string.length + 1] = '\0';
        new_string.length++;
    }

    return new_string;
}

/// @brief Pads the string at the start and at the end and returns the result as a new string
string PadString(string to_pad, SCHAR character, int count) {
    string padded_start = PadStartString(to_pad, character, count);
    string result = PadEndString(padded_start, character, count);

    FreeString(&padded_start);

    return result;
}

/// @brief Pads the string at the start and returns the result as a new string
string PadStartString(string to_pad, SCHAR character, int count) {
    string new_string;

    new_string.data = malloc(sizeof(SCHAR) * (to_pad.length + count + 1));
    new_string.data[to_pad.length + count] = '\0';
    new_string.length = to_pad.length + count;

    for (int i = 0; i < count; i++)
        new_string.data[i] = character;
    
    for (int i = 0; i < to_pad.length; i++)
        new_string.data[count + i] = to_pad.data[i];

    return new_string;
}

/// @brief Pads the string at the end and returns the result as a new string
string PadEndString(string to_pad, SCHAR character, int count) {
    string new_string;

    new_string.data = malloc(sizeof(SCHAR) * (to_pad.length + count + 1));
    new_string.data[to_pad.length + count] = '\0';
    new_string.length = to_pad.length + count;

    for (int i = 0; i < to_pad.length; i++)
        new_string.data[i] = to_pad.data[i];

    for (int i = 0; i < count; i++)
        new_string.data[to_pad.length + i] = character;

    return new_string;
}

/// @brief Takes a string and outputs a string_list with all the string tokens
string_list SplitString(string to_split, SCHAR splitter) {
    string_list new_string_list;
    int token_length = 0;

    new_string_list.tokens = malloc(sizeof(string));
    new_string_list.count = 0;

    for (int i = 0; i < to_split.length + 1; i++) {
        if (to_split.data[i] != splitter && to_split.data[i] != '\0') {
            token_length++;
            continue;
        }

        new_string_list.tokens = realloc(new_string_list.tokens, sizeof(string) * (new_string_list.count + 1));
        new_string_list.count++;

        new_string_list.tokens[new_string_list.count - 1].data = malloc(sizeof(SCHAR) * (token_length + 1));
        new_string_list.tokens[new_string_list.count - 1].data[token_length] = '\0';
        new_string_list.tokens[new_string_list.count - 1].length = token_length;

        for (int j = 0; j < token_length; j++)
            new_string_list.tokens[new_string_list.count - 1].data[j] = to_split.data[i + j - token_length];

        token_length = 0;
    }

    return new_string_list;
}