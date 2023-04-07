#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "BigInteger.h"

BigInteger createBigInteger()
{
    BigInteger newBigInt = (BigInteger)malloc(sizeof(struct BigInteger));

    if (!newBigInt)
    {
        return NULL;
    }

    newBigInt->sign = 0;
    newBigInt->size = 0;
    newBigInt->head = NULL;
    newBigInt->str = NULL;

    return newBigInt;
}

Digit createDigit(char val)
{
    Digit digitt = (Digit)malloc(sizeof(struct Digit));

    if (!digitt)
    {
        return NULL;
    }

    digitt->digit = val;
    digitt->next = NULL;

    return digitt;
}

void bigIntegerFree(BigInteger bigInt)
{
    if (!bigInt)
    {
        return;
    }

    free(bigInt->str);
    Digit digit = bigInt->head;

    while (digit)
    {
        Digit prev = digit;
        digit = digit->next;
        free(prev);
    }
    free(bigInt);
}

void removeZeros(BigInteger bigInt)
{
    if (!bigInt)
    {
        return;
    }

    size_t size = 0;
    Digit iterator = bigInt->head;
    Digit last = bigInt->head;
    size_t i = 0;

    while (iterator)
    {
        ++i;
        if (size == 0)
        {
            ++size;
            iterator = iterator->next;
            continue;
        }
        if (iterator->digit != 0)
        {
            last = iterator;
            size = i;
        }

        iterator = iterator->next;
    }

    iterator = last;
    bigInt->size = size;
    Digit temp = iterator;
    iterator = iterator->next;
    temp->next = NULL;

    while (iterator)
    {
        temp = iterator;
        iterator = iterator->next;
        free(temp);
    }
    if (bigInt->size == 1 && bigInt->head->digit == 0)
    {
        bigInt->sign = 0;
    }
}

int getSign(BigInteger bigInt)
{
    if (!bigInt)
    {
        // If the bigInt parameter is null, return 0 to indicate an error
        return 0;
    }
    else if (bigInt->sign == 1)
    {
        // If the bigInt parameter is negative, return -1
        return -1;
    }
    else
    {
        // If the bigInt parameter is non-negative, return 1
        return 1;
    }
}

BigInteger bigIntegerCreateFromString(const char *numbers)
{
    size_t size = 0; // count the number of digits in string
    char sign = 0;

    if (!numbers)
    {
        return NULL;
    }

    while (isspace(*numbers))
    {
        ++numbers;
    }

    if (*numbers == '+')
    {
        ++numbers;
    }
    else if (*numbers == '-')
    {
        sign = 1;
        ++numbers;
    }

    while (1)
    {
        if (isdigit(*numbers))
        {
            ++numbers;
            ++size;
        }
        else
        {
            --numbers;
            break;
        }
    }

    if (size == 0)
    {
        return NULL;
    }

    BigInteger number = createBigInteger();

    if (!number)
    {
        return NULL;
    }

    number->sign = sign;
    number->size = size;

    Digit *ptr = &(number->head);

    while (isdigit(*numbers))
    {
        *ptr = createDigit(*numbers - '0');
        if (!*ptr)
        {
            bigIntegerFree(number);
            return NULL;
        }
        ptr = &((*ptr)->next);
        --numbers;
    }
    removeZeros(number);

    return number;
}

const char *bigIntegerToString(BigInteger bigInt)
{
    if (!bigInt)
    {
        return NULL;
    }

    size_t size = bigInt->size;

    if (bigInt->sign == 1)
    {
        size += 1; // extra space for '-' sign
    }

    size_t totalSize = size + 1;
    
    if (bigInt->sign)
    {
        totalSize += 1;
    }
    char *string = (char *)realloc(bigInt->str, totalSize);

    if (!string)
    {
        return NULL;
    }

    size_t i = bigInt->size;
    if (bigInt->sign == 1)
    {
        i++;
    }

    string[i--] = '\0';

    Digit currentDigit = bigInt->head;

    while (currentDigit && i >= 0)
    {
        string[i--] = currentDigit->digit + '0';
        currentDigit = currentDigit->next;
    }

    if (bigInt->sign)
    {
        string[0] = '-'; // adds '-' at the beginning of string
    }

    bigInt->str = string;

    return string;
}

size_t count(BigInteger bigInt)
{
    if (!bigInt)
    {
        return -1;
    }
    return bigInt->size;
}

// BigInteger bigIntegerClone(BigInteger bigInt)
//{
//   return bigIntegerCreateFromString(bigIntegerToString(bigInt));
//}

BigInteger bigIntegerAdd(BigInteger a, BigInteger b)
{
    if (!a || !b)
    {
        return NULL;
    }

    if (a->sign == b->sign)
    {
        BigInteger result = createBigInteger();
        if (!result)
        {
            return NULL;
        }

        result->sign = a->sign;

        Digit digitA = a->head, digitB = b->head;
        Digit *resultDigit = &(result->head);

        int carry = 0;
        size_t size = 0;

        while (digitA || digitB || carry)
        {
            int sum = carry;
            if (digitA)
            {
                sum += digitA->digit;
                digitA = digitA->next;
            }
            if (digitB)
            {
                sum += digitB->digit;
                digitB = digitB->next;
            }

            *resultDigit = createDigit(sum % 10);
            carry = sum / 10;

            if (!*resultDigit)
            {
                bigIntegerFree(result);
                return NULL;
            }
            resultDigit = &((*resultDigit)->next);
            ++size;
        }

        result->size = size;
        removeZeros(result);

        return result;
    }

    if (a->sign)
    {
        a->sign = 0;
        BigInteger result = bigIntegerSubtract(b, a);
        a->sign = 1;
        return result;
    }
    b->sign = 0;
    BigInteger result = bigIntegerSubtract(a, b);
    b->sign = 1;
    return result;
}

BigInteger bigIntegerSubtract(BigInteger a, BigInteger b)
{
    if (!a || !b)
    {
        return NULL;
    }

    if (a->sign == b->sign)
    {
        Digit a_ptr = a->head, b_ptr = b->head;
        BigInteger result = createBigInteger();

        if (!result)
        {
            return NULL;
        }
        result->sign = a->sign;

        Digit *result_ptr = &(result->head);
        int borrow = 0;

        while (a_ptr)
        {
            int difference = a_ptr->digit;
            a_ptr = a_ptr->next;
            if (b_ptr)
            {
                difference -= b_ptr->digit;
                b_ptr = b_ptr->next;
            }
            if (borrow)
            {
                --difference;
                borrow = 0;
            }
            if (difference < 0)
            {
                difference += 10;
                borrow = 1;
            }
            *result_ptr = createDigit(difference);
            if (!*result_ptr)
            {
                bigIntegerFree(result);
                return NULL;
            }
            result_ptr = &((*result_ptr)->next);
            ++result->size;
        }

        if (b_ptr || borrow)
        {
            bigIntegerFree(result);
            result = bigIntegerSubtract(b, a);

            if (a->sign)
            {
                result->sign = 0;
            }
            else
            {
                result->sign = 1;
            }

            removeZeros(result);
            return result;
        }
        removeZeros(result);
        return result;
    }

    if (a->sign)
    {
        b->sign = 1;
        BigInteger result = bigIntegerAdd(a, b);
        b->sign = 0;
        return result;
    }

    b->sign = 0;
    BigInteger result = bigIntegerAdd(a, b);
    b->sign = 1;

    return result;
}

int bigIntegerCompare(BigInteger a, BigInteger b)
{
    // Compute the difference between a and b
    BigInteger diff = bigIntegerSubtract(a, b);

    if (!diff)
    {
        return -2; // error code for failed subtraction
    }

    // Extract the sign, size, and digit of the difference
    char sign = diff->sign;
    size_t size = diff->size;
    char digit = diff->head->digit;

    bigIntegerFree(diff);

    if (size == 1 && digit == 0)
    {
        return 0; // a and b are equal
    }
    else if (sign)
    {
        return -1; // a is less than b
    }
    else
    {
        return 1; // a is greater than b
    }
}

BigInteger bigIntegerMultiply(BigInteger multiplier, BigInteger multiplicand)
{
    if (!multiplier || !multiplicand)
    {
        return NULL;
    }

    BigInteger product = createBigInteger();
    size_t currentDigitPosition = 0;

    if (!product)
    {
        return NULL;
    }

    Digit currentDigit = multiplicand->head;
    while (currentDigit)
    {
        BigInteger temp = createBigInteger();

        if (!temp)
        {
            bigIntegerFree(product);
            return NULL;
        }

        Digit *digitToMultiply = &(temp->head);
        for (size_t i = 0; i < currentDigitPosition; ++i)
        {
            *digitToMultiply = createDigit(0);

            if (!*digitToMultiply)
            {
                bigIntegerFree(product);
                bigIntegerFree(temp);
                return NULL;
            }

            digitToMultiply = &((*digitToMultiply)->next);
            ++temp->size;
        }

        Digit digitToMultiplyValue = multiplier->head;
        int carry = 0;

        while (digitToMultiplyValue || carry)
        {
            int digitProduct = 0;

            digitProduct += carry;

            carry = 0;

            if (digitToMultiplyValue)
            {
                digitProduct += currentDigit->digit * digitToMultiplyValue->digit;
                digitToMultiplyValue = digitToMultiplyValue->next;
            }

            *digitToMultiply = createDigit(digitProduct % 10);

            if (!*digitToMultiply)
            {
                bigIntegerFree(product);
                bigIntegerFree(temp);
                return NULL;
            }

            carry = digitProduct / 10;
            digitToMultiply = &((*digitToMultiply)->next);
        }

        BigInteger temp2 = bigIntegerAdd(product, temp);

        if (!temp2)
        {
            bigIntegerFree(product);
            bigIntegerFree(temp);
            return NULL;
        }

        bigIntegerFree(product);
        bigIntegerFree(temp);
        product = temp2;
        ++currentDigitPosition;
        currentDigit = currentDigit->next;
    }

    if (multiplier->sign + multiplicand->sign == 1)
    {
        product->sign = 1;
    }

    removeZeros(product);
    return product;
}

BigInteger bigIntegerDivide(BigInteger a, BigInteger b)
{
    if (!a || !b || (b->size == 1 && b->head->digit == 0))
    {
        return NULL;
    }

    BigInteger div = bigIntegerCreateFromString("0");

    if (!div)
    {
        return NULL;
    }

    BigInteger mod = bigIntegerClone(a);

    if (!mod)
    {
        bigIntegerFree(div);
        return NULL;
    }

    BigInteger one = bigIntegerCreateFromString("1");

    if (!one)
    {
        bigIntegerFree(div);
        bigIntegerFree(mod);

        return NULL;
    }

    int bs = b->sign;
    
    mod->sign = 0, b->sign = 0;

    while (mod->sign == 0)
    {
        BigInteger temp = bigIntegerSubtract(mod, b);
        if (!temp)
        {
            bigIntegerFree(div);
            bigIntegerFree(mod);
            bigIntegerFree(one);
            b->sign = bs;
            return NULL;
        }

        bigIntegerFree(mod);
        mod = temp;

        temp = bigIntegerAdd(div, one);
        if (!temp)
        {
            bigIntegerFree(div);
            bigIntegerFree(mod);
            bigIntegerFree(one);
            b->sign = bs;
            return NULL;
        }

        bigIntegerFree(div);
        div = temp;
    }

    b->sign = bs;

    if (a->sign + b->sign == 1)
    {
        div->sign = 1;
    }

    removeZeros(div);
    bigIntegerFree(one);
    bigIntegerFree(mod);
    div->head->digit--;

    return div;
}

BigInteger bigIntegerMod(BigInteger a, BigInteger b)
{
    if (!a || !b || (b->size == 1 && b->head->digit == 0))
    {
        return NULL;
    }

    BigInteger quotient = bigIntegerDivide(a, b);
    if (!quotient)
    {
        return NULL;
    }

    BigInteger remainder = bigIntegerSubtract(a, bigIntegerMultiply(quotient, b));
    if (!remainder)
    {
        bigIntegerFree(quotient);
        return NULL;
    }

    bigIntegerFree(quotient);

    return remainder;
}

void printBigInteger(BigInteger bigInt)
{
    if (!bigInt)
    {
        printf("NULL\n");
        return;
    }

    const char *str = bigIntegerToString(bigInt);

    if (!str)
    {
        printf("NULL\n");
        return;
    }

    printf("%s\n", str);
    free((void *)str);
}

BigInteger bigIntegerClone(BigInteger bigInt)
{
    if (!bigInt)
    {
        return NULL;
    }

    BigInteger clonedBigInt = createBigInteger();

    if (!clonedBigInt)
    {
        return NULL;
    }

    clonedBigInt->sign = bigInt->sign;
    clonedBigInt->size = bigInt->size;

    Digit currentDigit = bigInt->head;
    Digit *ptr = &(clonedBigInt->head);

    while (currentDigit)
    {
        *ptr = createDigit(currentDigit->digit);
        if (!*ptr)
        {
            bigIntegerFree(clonedBigInt);
            return NULL;
        }
        ptr = &((*ptr)->next);
        currentDigit = currentDigit->next;
    }

    removeZeros(clonedBigInt);

    return clonedBigInt;
}

void makeEmpty(BigInteger bigInt)
{
    if (!bigInt || isEmpty(bigInt) == 1)
    {
        return;
    }

    Digit digit = bigInt->head;
    while (digit)
    {
        Digit next = digit->next;
        free(digit);
        digit = next;
    }

    bigInt->head = NULL;
    bigInt->size = 0;
}

int isEmpty(BigInteger bigInt)
{
    if(!bigInt)
    {
        return -1;//error code
    }


    if (count(bigInt) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
