#ifndef biginth
#define biginth

/*
* Name: bigint
* Version: 1.0
* Author: RysteQ
*
* Purpose: Give an easy way for programmers to have big integers in their code
* without doing anything in the .c file and with numerous and easy to
* understand functions.
*
* Performance: The functions might not be the most performant out there but
* are decent in their time complexity and have been tested for memory leaks.
*
* Notes: The only thing you should modify is the SIZE_OF_BIGINT definition,
* it declares the amount of bytes a bigint will have. I specifically chose
* bytes due to them being easier to understand, you can easily modify the code
* and have x4 or x8 the performance if you went for 8 bytes. Also, all of the
* numbers are positive, this library (at least as of now) does not support
* negative numbers.
*
* Credit: I should give credit to some lads, specifically two guys I only know
* as StaticSaga and mid that saw the first version of the code and pointed me
* in the right direction to make it at least decent in terms of time
* complexity. Without their help this library would be a shameful side project
* of mine that would never see the light of day and nothing more.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_BIGINT 16

typedef unsigned char* Bigint;

Bigint CreateBigint();
Bigint CreateBigintFromUlong(unsigned long long value);
void PrintBigint(Bigint value);
void FreeBigint(Bigint* to_free);
Bigint CopyBigint(Bigint value);
Bigint AddToBigint(Bigint number_one, unsigned long long number_two);
Bigint SubToBigint(Bigint number_one, unsigned long long number_two);
Bigint DivToBigint(Bigint number_one, unsigned long long number_two);
Bigint ModToBigint(Bigint number_one, unsigned long long number_two);
Bigint MulToBigint(Bigint number_one, unsigned long long number_two);
Bigint PowToBigint(Bigint number_one, unsigned long long number_two);
Bigint AddBigints(Bigint number_one, Bigint number_two);
Bigint SubBigints(Bigint number_one, Bigint number_two);
Bigint DivBigints(Bigint number_one, Bigint number_two);
Bigint ModBigints(Bigint number_one, Bigint number_two);
Bigint MulBigints(Bigint number_one, Bigint number_two);
Bigint PowBigints(Bigint number_one, Bigint number_two);
void OverrideBigint(Bigint* target, Bigint value);
char IsBigintBiggerThan(Bigint number_one, Bigint number_two);
char IsBigintSmallerThan(Bigint number_one, Bigint number_two);
char IsBigintEqual(Bigint number_one, Bigint number_two);

#endif
