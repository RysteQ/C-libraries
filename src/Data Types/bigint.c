#include "bigint.h"

/// @brief Allocates memory for a new Bigint
/// @return A Bigint with the value zero
Bigint CreateBigint() {
    return calloc(SIZE_OF_BIGINT, sizeof(char));
}

/// @brief Allocates memory for a new Bigint
/// @param value The value of the new Bigint, it must be a 64bit number
Bigint CreateBigintFromUlong(unsigned long long value) {
    Bigint to_return = CreateBigint();

    for (int i = 0; i < 8; i++)
        to_return[i] = (value & (0xFF00000000000000 >> ((7 - i) * 8))) >> (8 * i);

    return to_return;
}

/// @brief Prints a Bigint number to the terminal
void PrintBigint(Bigint value) {
    for (int i = SIZE_OF_BIGINT - 1; i > -1; i--)
        printf("%x ", value[i]);
}

/// @brief Frees a Bigint from memory
void FreeBigint(Bigint* to_free) {
    free(*to_free);
}

/// @brief Copies the value of one Bigint and returns a new one with said value
Bigint CopyBigint(Bigint value) {
    Bigint copied_bigint = CreateBigint();

    for (int i = 0; i < SIZE_OF_BIGINT; i++)
        copied_bigint[i] = value[i];

    return copied_bigint;
}

/// @brief Adds two numbers together
/// @param number_two An unsigned 64bit number
Bigint AddToBigint(Bigint number_one, unsigned long long number_two) {
    Bigint bigint_one = CopyBigint(number_one);
    Bigint bigint_two = CreateBigintFromUlong(number_two);
    Bigint result = AddBigints(bigint_one, bigint_two);

    FreeBigint(&bigint_one);
    FreeBigint(&bigint_two);

    return result;
}

/// @brief Subtracts two numbers together
/// @param number_two An unsigned 64bit number
Bigint SubToBigint(Bigint number_one, unsigned long long number_two) {
    Bigint bigint_one = CopyBigint(number_one);
    Bigint bigint_two = CreateBigintFromUlong(number_two);
    Bigint result = SubBigints(bigint_one, bigint_two);

    FreeBigint(&bigint_one);
    FreeBigint(&bigint_two);

    return result;
}

/// @brief Divides two numbers together only if both numbers are bigger than zero
/// @param number_two An unsigned 64bit number
/// @return The result of the division of both numbers if the division is allowed, otherwise returns zero
Bigint DivTobigint(Bigint number_one, unsigned long long number_two) {
    Bigint bigint_one = CopyBigint(number_one);
    Bigint bigint_two = CreateBigintFromUlong(number_two);
    Bigint result = DivBigints(bigint_one, bigint_two);

    FreeBigint(&bigint_one);
    FreeBigint(&bigint_two);

    return result;
}

/// @brief Executes the modulo operation only if both numbers are bigger than zero
/// @param number_two An unsigned 64bit number
/// @return The result of the modulo operation of both numbers if the modulo operation is allowed, otherwise returns zero
Bigint ModTobigint(Bigint number_one, unsigned long long number_two) {
    Bigint bigint_one = CopyBigint(number_one);
    Bigint bigint_two = CreateBigintFromUlong(number_two);
    Bigint result = ModBigints(bigint_one, bigint_two);

    FreeBigint(&bigint_one);
    FreeBigint(&bigint_two);

    return result;
}

/// @brief Multiplies two numbers together
/// @param number_two An unsigned 64bit number
Bigint MulTobigint(Bigint number_one, unsigned long long number_two) {
    Bigint bigint_one = CopyBigint(number_one);
    Bigint bigint_two = CreateBigintFromUlong(number_two);
    Bigint result = MulBigints(bigint_one, bigint_two);

    FreeBigint(&bigint_one);
    FreeBigint(&bigint_two);

    return result;
}

/// @brief Raises the number_one to the power of number_two
/// @param number_two An unsigned 64bit number
Bigint PowToBigint(Bigint number_one, unsigned long long number_two) {
    Bigint bigint_one = CopyBigint(number_one);
    Bigint bigint_two = CreateBigintFromUlong(number_two);
    Bigint result = PowBigints(bigint_one, bigint_two);
    
    FreeBigint(&bigint_one);
    FreeBigint(&bigint_two);

    return result;
}

/// @brief Adds two numbers together
Bigint AddBigints(Bigint number_one, Bigint number_two) {
    Bigint result = CreateBigint();
    char carry_over = 0;
    short addition = 0;

    for (int i = 0; i < SIZE_OF_BIGINT; i++) {
        addition = number_one[i] + number_two[i] + carry_over;
        carry_over = addition >> 8;
        result[i] = addition & 0x00FF;
    }

    return result;
}

/// @brief Subtracts two numbers together
Bigint SubBigints(Bigint number_one, Bigint number_two) {
    Bigint result = CreateBigint();
    Bigint one = CreateBigintFromUlong(1);
    Bigint number_two_copy = CopyBigint(number_two);

    for (int i = 0; i < SIZE_OF_BIGINT; i++)
        number_two_copy[i] = ~number_two_copy[i];
    
    OverrideBigint(&result, AddBigints(number_one, number_two_copy));
    OverrideBigint(&result, AddBigints(result, one));

    for (int i = SIZE_OF_BIGINT - 1; i > -1; i++) {
        if (result[i] == 0)
            continue;

        result[i] = ((result[i] << (128 / result[i])) >> (128 / result[i]));

        break;
    }

    FreeBigint(&one);
    FreeBigint(&number_two_copy);

    return result;
}

/// @brief Divides two numbers together only if both numbers are bigger than zero
/// @return The result of the division of both numbers if the division is allowed, otherwise returns zero
Bigint DivBigints(Bigint number_one, Bigint number_two) {
    Bigint result = CreateBigint();
    Bigint subtractor = CreateBigint();

    for (int i = 0; i < SIZE_OF_BIGINT * 8; i++) {
        subtractor[SIZE_OF_BIGINT - 1] = subtractor[SIZE_OF_BIGINT - 1] << (i % 8);

        for (int j = SIZE_OF_BIGINT - 2; j > -1; j--) {
            short bit_shift = subtractor[j] << 1;
            subtractor[j] = bit_shift & 0x00FF;
            subtractor[j + 1] +=  bit_shift >> 8;
        }

        if ((number_one[SIZE_OF_BIGINT - 1 - (i / 8)] & (0b10000000 >> (i % 8))) != 0)
            OverrideBigint(&subtractor, AddToBigint(subtractor, 1));

        if (IsBigintSmallerThan(number_two, subtractor) || IsBigintEqual(number_two, subtractor)) {
            OverrideBigint(&subtractor, SubBigints(subtractor, number_two));
            result[SIZE_OF_BIGINT - 1 - (i / 8)] += 0b100000000 >> ((i % 8) + 1);
        }
    }

    FreeBigint(&subtractor);

    return result;
}

/// @brief Executes the modulo operation only if both numbers are bigger than zero
/// @return The result of the modulo operation of both numbers if the modulo operation is allowed, otherwise returns zero
Bigint ModBigints(Bigint number_one, Bigint number_two) {
    Bigint result = CreateBigint();

    for (int i = 0; i < SIZE_OF_BIGINT * 8; i++) {
        result[SIZE_OF_BIGINT - 1] = result[SIZE_OF_BIGINT - 1] << (i % 8);

        for (int j = SIZE_OF_BIGINT - 2; j > -1; j--) {
            short bit_shift = result[j] << 1;
            result[j] = bit_shift & 0x00FF;
            result[j + 1] +=  bit_shift >> 8;
        }

        if ((number_one[SIZE_OF_BIGINT - 1 - (i / 8)] & (0b10000000 >> (i % 8))) != 0)
            OverrideBigint(&result, AddToBigint(result, 1));

        if (IsBigintSmallerThan(number_two, result) || IsBigintEqual(number_two, result))
            OverrideBigint(&result, SubBigints(result, number_two));
    }

    return result;
}

/// @brief Multiplies two numbers together
Bigint MulBigints(Bigint number_one, Bigint number_two) {
    Bigint result = CreateBigint();
    Bigint* bigints_to_add = malloc(sizeof(Bigint) * SIZE_OF_BIGINT * 8);

    for (int i = 0; i < SIZE_OF_BIGINT * 8; i++) {
        if ((number_two[i / 8] & (0b00000001 << (i % 8))) == 0) {
            bigints_to_add[i] = CreateBigint();
            continue;
        }

        bigints_to_add[i] = CopyBigint(number_one);

        for (int j = SIZE_OF_BIGINT - 1; j > -1 + (i / 8); j--)
            bigints_to_add[i][j] = bigints_to_add[i][j - (i / 8)];
        
        for (int j = 0; j < i / 8; j++)
            bigints_to_add[i][j] = 0;

        bigints_to_add[i][SIZE_OF_BIGINT - 1] = bigints_to_add[i][SIZE_OF_BIGINT - 1] << (i % 8);

        for (int j = SIZE_OF_BIGINT - 2; j > -1; j--) {
            short bit_shift = bigints_to_add[i][j] << (i % 8);
            bigints_to_add[i][j] = bit_shift & 0x00FF;
            bigints_to_add[i][j + 1] +=  bit_shift >> 8;
        }
    }

    for (int i = 0; i < SIZE_OF_BIGINT * 8; i++) {
        OverrideBigint(&result, AddBigints(result, bigints_to_add[i]));
        FreeBigint(&bigints_to_add[i]);
    }

    free(bigints_to_add);

    return result;
}

/// @brief Raises the number_one to the power of number_two
Bigint PowBigints(Bigint number_one, Bigint number_two) {
    Bigint result = CopyBigint(number_one);
    Bigint times = CopyBigint(number_two);
    Bigint zero = CreateBigint();
    Bigint one = CreateBigintFromUlong(1);

    if (IsBigintEqual(number_two, zero)) {
        FreeBigint(&result);
        FreeBigint(&times);
        FreeBigint(&zero);
        FreeBigint(&one);

        return CreateBigintFromUlong(1);
    }
    
    while (IsBigintEqual(times, one) == 0) {
        OverrideBigint(&times, SubBigints(times, one));
        OverrideBigint(&result, MulBigints(result, number_one));
    }

    FreeBigint(&times);
    FreeBigint(&zero);
    FreeBigint(&one);

    return result;
}

/// @brief A useful tiny function to assign new values to bigints without having a memory leak
/// @param target The bigint to be overriden
/// @param value The new value of the bigint
void OverrideBigint(Bigint* target, Bigint value) {
    FreeBigint(target);
    *target = value;
}

/// @brief Checks if number_one is larger than number_two
/// @return 1 if number_one > number_two, otherwise 0
char IsBigintBiggerThan(Bigint number_one, Bigint number_two) {
    for (int i = SIZE_OF_BIGINT - 1; i > -1; i--)
        if (number_one[i] != 0 || number_two[i] != 0)
            return number_one[i] > number_two[i];

    return 0;
}

/// @brief Checks if number_one is smaller than number_two
/// @return 1 if number_one < number_two, otherwise 0
char IsBigintSmallerThan(Bigint number_one, Bigint number_two) {
    for (int i = SIZE_OF_BIGINT - 1; i > -1; i--)
        if (number_one[i] != 0 || number_two[i] != 0)
            return number_one[i] < number_two[i];
    
    return 0;
}

/// @brief Checks if number_one is equal to number_two
/// @return 1 if number_one == number_two, otherwise 0
char IsBigintEqual(Bigint number_one, Bigint number_two) {
    for (int i = 0; i < SIZE_OF_BIGINT; i++)
        if (number_one[i] != number_two[i])
            return 0;
    
    return 1;
}
