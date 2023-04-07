#include "stack.h"
#include "BigInteger.h"
#include "additionalFunctions.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[])
{
    srand(time(NULL)); // initialize random seed

    BigInteger customerAmountTotal = newBigInteger(0);
    BigInteger pseudoUsedPlates = newBigInteger(0);
    BigInteger pseudoMax = newBigInteger(0);

    Stack *usedPlateStack = stack_create();
    Stack *plateStack = stack_create();
    Stack *customerInfo = stack_create();
    Stack *notServedCustomers = stack_create();
    Stack *totalFreePlateAmount = stack_create();
    Stack *additionalNeededPlates = stack_create();

    /*To log information into log.txt file*/
    FILE *logFile;
    logFile = fopen("log.txt", "w");
    /**************************************/

    int plateAmount, initialTimeUnit, eatingTimeMax, eatingTimeMin, cleaningTime, entryChance;
    int timeUnit = 1;
    int maxiPlatesUsed = 0;

    if (argc == 2 && strcmp(argv[1], "randomized") == 0 || strcmp(argv[1], "r") == 0) // randomize data
    {
        plateAmount = generateRandomNumber(1, 100);
        initialTimeUnit = generateRandomNumber(1, 1000000);
        eatingTimeMax = generateRandomNumber(1, 15);
        eatingTimeMin = generateRandomNumber(1, eatingTimeMax);
        entryChance = generateRandomNumber(10, 100);
        cleaningTime = generateRandomNumber(1, 20);

        printf("Initial data (randomized) \n");
        printf("Plate Amount: %d\n", plateAmount);
        printf("Time units: %d\n", initialTimeUnit);
        printf("Max eating time: %d\n", eatingTimeMax);
        printf("Min eating time : %d\n", eatingTimeMin);
        printf("Customer entry chance: %d %%\n", entryChance);
        printf("Cleaning time: %d\n\n", cleaningTime);
    }
    else if (argc == 2 && strcmp(argv[1], "f") == 0 || strcmp(argv[1], "fixed") == 0) // Dont randomize data
    {
        readParameters(&plateAmount, &initialTimeUnit, &eatingTimeMax, &eatingTimeMin, &cleaningTime, &entryChance);

        printf("Initial data (Not - randomized) \n");
        printf("Plate Amount: %d\n", plateAmount);
        printf("Time units: %d\n", initialTimeUnit);
        printf("Max eating time: %d\n", eatingTimeMax);
        printf("Min eating time : %d\n", eatingTimeMin);
        printf("Customer entry chance: %d %%\n", entryChance);
        printf("Cleaning time: %d\n\n", cleaningTime);
    }

    int totalPlateAmount = plateAmount;

    stack_fill(plateStack, 0, totalPlateAmount);

    while (timeUnit <= initialTimeUnit)
    {

        /*Code for freeing the plates after they are washed*/

        if (stack_contains(usedPlateStack, timeUnit))
        {
            /*Free all the plates that are done cleaning at this timeUnit*/
            stack_remove(usedPlateStack, timeUnit);

            /*Refresh the plateAmount with new plates(it gets bigger)*/
            plateAmount = totalPlateAmount - stack_count(usedPlateStack);

            while (plateAmount != stack_count(plateStack))
            {
                stack_push(plateStack, timeUnit); // Free plate stack gets another plate added;
            }

            fprintf(logFile, "TIME: %d | ACTION: Customer left | Plates left free %d\n", timeUnit, plateAmount);
             /*******************************************************/
        }
       

        /*Not served costumer situation code*/
        if (plateAmount <= 0)
        {
            fprintf(logFile, "TIME: %d Customer not served due to plate shortage \n", timeUnit);
            stack_push(notServedCustomers, timeUnit);
            stack_push(additionalNeededPlates, timeUnit + generateRandomNumber(eatingTimeMin, eatingTimeMax) + cleaningTime);
            pseudoUsedPlates = bigIntegerAdd(pseudoUsedPlates, newBigInteger(1));
        }

        while (stack_contains(additionalNeededPlates, timeUnit))
        {
            stack_pop(additionalNeededPlates);
            pseudoUsedPlates = bigIntegerSubtract(pseudoUsedPlates, newBigInteger(1));
        }

        if (bigIntegerCompare(pseudoUsedPlates,pseudoMax ) == 1)
        {
            pseudoMax = bigIntegerCreateFromString("0");
            pseudoMax = bigIntegerAdd(pseudoMax, pseudoUsedPlates);
        }
        /***********************************/

        if (generateRandomNumber(1, 100) <= entryChance && stack_count(usedPlateStack) < totalPlateAmount && stack_count(plateStack) > 0)
        {
            stack_push(customerInfo, timeUnit); // Information when customers arrived;
            stack_pop(plateStack);
            plateAmount--;
            customerAmountTotal = bigIntegerAdd(customerAmountTotal, newBigInteger(1));
            fprintf(logFile, "TIME: %d | ACTION: Customer arrived | ", timeUnit);

            int eatingTime = generateRandomNumber(eatingTimeMin, eatingTimeMax);

            fprintf(logFile, "eating time: %d | Will be done at: %d | Plates left free %d\n", eatingTime, timeUnit + eatingTime + cleaningTime, stack_count(plateStack));

            stack_push(usedPlateStack, timeUnit + eatingTime + cleaningTime); // used plate with info when its going to be free again

            /* Situation if customer eats after restoraunt closes*/
            if (eatingTime + cleaningTime >= initialTimeUnit - timeUnit)
            {
                stack_pop(usedPlateStack);
                stack_push(plateStack, timeUnit);

                plateAmount = stack_count(plateStack);
                customerAmountTotal = bigIntegerSubtract(customerAmountTotal, newBigInteger(1));
                fprintf(logFile, "TIME: %d | ACTION: Not enough time to eat, customer left | Plate amount left:  %d \n", timeUnit, plateAmount);
            }
            /*********************************************************/
            stack_push(totalFreePlateAmount, plateAmount);
            timeUnit++;
        }
        else
        {
            stack_push(totalFreePlateAmount, plateAmount);
            timeUnit++;
        }

        // Maximum amount of plates used at the same time
        if (stack_count(usedPlateStack) > maxiPlatesUsed)
            maxiPlatesUsed = stack_count(usedPlateStack);
    }

    fclose(logFile);

    printf("MAX Plates used at the same time: %d | Total customers served:  %s | Not served: %d\n", maxiPlatesUsed, bigIntegerToString(customerAmountTotal), stack_count(notServedCustomers));

    printf("Restaurant needs in total %.0f plates\n", ceil((maxiPlatesUsed + bigIntegerToInt(pseudoMax) ) * 1.1) );

    // UI
    while (1)
    {
        printf("\nEnter 1 to analyze a time frame, 2 to quit: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Please enter start and end time (separated by a space): ");
            int start, end;
            scanf("%d %d", &start, &end);
            if (start < end && start >= 0 && start <= initialTimeUnit && end <= initialTimeUnit)
            {
                printf("\n");
                information(start, end, totalFreePlateAmount);
            }
            else
            {
                printf("Invalid information provided \n");
            }
        }
        else if (choice == 2)
        {
            printf("Exiting program...\n");
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
            fflush(stdin);
        }
    }

    stack_done(&usedPlateStack);
    stack_done(&plateStack);
    stack_done(&customerInfo);
    stack_done(&notServedCustomers);
    stack_done(&totalFreePlateAmount);
    stack_done(&additionalNeededPlates);
    bigIntegerFree(customerAmountTotal);
    bigIntegerFree(pseudoMax);
    bigIntegerFree(pseudoUsedPlates);

    return 0;
}
