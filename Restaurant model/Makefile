main.exe : main.c BigInteger.h BigInteger.o additionalFunctions.h additionalFunctions.o stack.h stack.o
	gcc -std=c99 -o main.exe main.c BigInteger.o additionalFunctions.o stack.o 

BigInteger.o : BigInteger.c BigInteger.h
	gcc -c -std=c99 BigInteger.c
additionalFunctions.o : additionalFunctions.c additionalFunctions.h
	gcc -c -std=c99 additionalFunctions.c
stack.o : stack.c stack.h
	gcc -c -std=c99 stack.c
