#ifndef ADDITIONAL_FUNCTIONS_H
#define ADDITIONAL_FUNCTIONS_H

#include <stdlib.h>
#include "stack.h"
#include "BigInteger.h"


int generateRandomNumber(int min, int max);
int stack_contains(Stack *stack, DATA_TYPE value);
void stack_remove(Stack *stack, DATA_TYPE value);
void stack_fill(Stack *stack, DATA_TYPE value, size_t size);
DATA_TYPE stack_index_value(Stack *stack, int index);
void information(int start, int end, Stack *stack);

BigInteger newBigInteger(int n);
int bigIntCompareToInteger(BigInteger bigInt, int num);
int bigIntegerToInt(BigInteger bigInt);

void readParameters(int *plateAmount, int *initialTimeUnit, int *eatingTimeMax, int *eatingTimeMin, int *cleaningTime, int *entryChance);

#endif // ADDITIONAL_FUNCTIONS_H