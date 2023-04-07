#include "additionalFunctions.h"
#include "stack.h"
#include "BigInteger.h"

int generateRandomNumber(int min, int max)
{
    int random_number;

    random_number = rand() % max + min;

    return random_number;
}

int stack_contains(Stack *stack, DATA_TYPE value) // checks if stack contains a certain value, if yes returns 1, else returns 0
{
    Node *current = stack->top;
    while (current != NULL)
    {
        if (current->data == value)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void stack_remove(Stack *stack, DATA_TYPE value)
{
    Node *current = stack->top;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (current->data == value)
        {
            if (previous == NULL)
            {
                // remove the top node from the stack
                stack->top = current->next;
            }
            else
            {
                // remove a middle or bottom node from the stack
                previous->next = current->next;
            }
            Node *temp = current;
            current = current->next; // move current to next node
            free(temp);              // deallocate memory for the removed node
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}

void stack_fill(Stack *stack, DATA_TYPE value, size_t size)
{
    for (int i = 0; i < size; ++i)
        stack_push(stack, value);
}


DATA_TYPE stack_index_value(Stack *stack, int index)
{
    int size = 0;
    Node *current = stack->top;

    // calculate size of stack
    while (current != NULL)
    {
        size++;
        current = current->next;
    }

    // check if index is within range
    if (index < 0 || index >= size)
    {
        printf("Index out of range.\n");
        exit(1);
    }

    // traverse stack to desired index
    current = stack->top;
    for (int i = 0; i < size - index - 1; i++)
    {
        current = current->next;
    }

    // return data at index
    return current->data;
}

void information(int start, int end, Stack *stack) // Information on free plates
{
    int temp = 0;
    int max = 0;
    BigInteger min = bigIntegerCreateFromString("999999999999999999");
    double sum = 0;
    start-=1;
    int counted = 0;

    for (int i = start; i < end; i++)
    {
        temp = stack_index_value(stack, i);

       // printf("TIME:%d | FREE PLATES: %d \n",i+1,temp);
        sum += temp;
        counted++;

        if (max < temp)
            max = temp;

        if (bigIntCompareToInteger(min,temp) == 1){
            makeEmpty(min);
            BigInteger tempInt = newBigInteger(temp);
            min = bigIntegerAdd(tempInt,newBigInteger(0));
            bigIntegerFree(tempInt);
            }

    }
    const char *c = bigIntegerToString(min);
    double average = sum / counted;

    printf("Time: %d - %d | Maximum free plates: %d | Minimum free plates %s | Average: %0.3f \n",start+1, end, max, c, average);
    bigIntegerFree(min);
   

}

BigInteger newBigInteger(int n)
{
    // check if n is 0
    if (n == 0)
    {
        BigInteger zero = createBigInteger();
        zero->sign = 0;
        zero->size = 1;
        zero->head = createDigit(0);
        return zero;
    }

    // count number of digits
    int size = 0;
    int temp = abs(n);
    while (temp != 0)
    {
        ++size;
        temp /= 10;
    }

    // create BigInteger struct
    BigInteger bigInt = createBigInteger();
    if (!bigInt)
    {
        return NULL;
    }

    // set sign and size
    bigInt->sign = (n < 0) ? 1 : 0;
    bigInt->size = size;

    // create digits
    Digit *ptr = &(bigInt->head);
    temp = abs(n);
    while (temp != 0)
    {
        *ptr = createDigit(temp % 10);
        if (!*ptr)
        {
            bigIntegerFree(bigInt);
            return NULL;
        }
        ptr = &((*ptr)->next);
        temp /= 10;
    }
    removeZeros(bigInt);

    return bigInt;
}

int bigIntCompareToInteger(BigInteger bigInt, int num)
{
    // Check sign of bigInt and num
    if (bigInt->sign == '-' && num >= 0)
        return -1;
    else if (bigInt->sign == '+' && num < 0)
        return 1;

    // Convert num to a BigInteger
    BigInteger intAsBigInt = newBigInteger(num);

    // Compare bigInt to intAsBigInt
    int comparison = bigIntegerCompare(bigInt, intAsBigInt);

    // Free memory allocated for intAsBigInt
   bigIntegerFree(intAsBigInt);

    return comparison;
}

int bigIntegerToInt(BigInteger bigInt) {
    if (!bigInt || bigInt->size > 10) {
        return 0;  // return 0 if bigInt is NULL or larger than the maximum int value (10 digits)
    }
    
    int result = 0;
    int sign = (bigInt->sign == 1) ? -1 : 1;
    Digit currentDigit = bigInt->head;
    
    while (currentDigit) {
        result = result * 10 + currentDigit->digit;
        currentDigit = currentDigit->next;
    }
    
    if (sign == -1 && result > 0) {
        // check for overflow if the result is negative
        return 0;
    }
    
    return sign * result;
}

void readParameters(int *plateAmount, int *initialTimeUnit, int *eatingTimeMax, int *eatingTimeMin, int *cleaningTime, int *entryChance)
{
    FILE *fp;
    char filename[] = "parameters.txt";
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fscanf(fp, "%d%*[^\n]", plateAmount);
    fscanf(fp, "%d%*[^\n]", initialTimeUnit);
    fscanf(fp, "%d%*[^\n]", eatingTimeMax);
    fscanf(fp, "%d%*[^\n]", eatingTimeMin);
    fscanf(fp, "%d%*[^\n]", cleaningTime);
    fscanf(fp, "%d%*[^\n]", entryChance);
    fclose(fp);
}