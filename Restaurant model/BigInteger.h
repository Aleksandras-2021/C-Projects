#include <stddef.h>

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

typedef struct Digit
{
    char digit;
    struct Digit *next;
} *Digit;

typedef struct BigInteger
{
    Digit head;
    char sign;
    size_t size;
    char *str;
} *BigInteger;

//Functions that are required for the lab assignment.
BigInteger createBigInteger();
const char *bigIntegerToString(BigInteger bigInt);
BigInteger bigIntegerClone(BigInteger bigInt);
size_t count(BigInteger bigInt);
void makeEmpty(BigInteger bigInt);
int isEmpty(BigInteger bigInt);
void bigIntegerFree(BigInteger bigInt);//Done() destroys the linked list

//Basic arithmetic functions
BigInteger bigIntegerAdd(BigInteger a, BigInteger b);
BigInteger bigIntegerSubtract(BigInteger a, BigInteger b);
BigInteger bigIntegerMultiply(BigInteger a, BigInteger b);
BigInteger bigIntegerDivide(BigInteger a, BigInteger b);
BigInteger bigIntegerMod(BigInteger a, BigInteger b);
int bigIntegerCompare(BigInteger a, BigInteger b);

//Additional functions that are useful
BigInteger bigIntegerCreateFromString(const char *numbers);
Digit createDigit(char val);//This function only used by other functions
int getSign(BigInteger bigInt);
void printBigInteger(BigInteger bigInt);
void removeZeros(BigInteger bigInt);

#endif