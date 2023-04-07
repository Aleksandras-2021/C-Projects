#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_FORMAT stderr, "%s:%d error: %s\n", __FILE__, __LINE__

typedef int DATA_TYPE;

typedef struct Node{
    DATA_TYPE data;
    struct Node* next;
} Node;

typedef struct Stack{
    Node* top;
} Stack;

Stack* stack_create();
Stack *stack_clone(Stack *source);
unsigned char stack_is_empty(Stack *stack);
unsigned char stack_is_full(Stack *stack);
void stack_make_empty(Stack *stack);
void stack_done(Stack** stack);
void stack_push(Stack* stack, int value);
void stack_print(Stack* stack);
DATA_TYPE stack_pop(Stack* stack);
DATA_TYPE stack_top(Stack* stack);
int stack_count(Stack *stack);

#endif
