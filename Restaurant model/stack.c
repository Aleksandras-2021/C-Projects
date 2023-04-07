#include "stack.h"

/*
 *Returns pointer to new stack
 */
Stack* stack_create(){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "stack is full");
	exit(1);
    }
    stack->top = NULL;
    return stack;
}

/*
 *Destroys the stack, makes it inaccessible
 */
void stack_done(Stack** stack){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }

    Node* current = (*stack)->top;
    while (current != NULL){
	Node* temp = current;
	current = current->next;
	free(temp);
    }
    (*stack)->top = NULL;
    free(*stack);
    *stack = NULL;
}

int stack_count(Stack *stack){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }

    int count = 0;
    Node *current = stack->top;
    while (current != NULL){
	++count;
	current = current->next;
    }
    return count;
}

unsigned char stack_is_empty(Stack *stack){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }

    if (stack->top == NULL){
	return 1;
    }
    else{
	return 0;
    }
}

unsigned char stack_is_full(Stack *stack){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }

    Node *test = malloc(sizeof(Node));
    if (test == NULL){
	return 1;
    }
    else{
	free(test);
	return 0;
    }
}

Stack *stack_clone(Stack *source){
    if (source == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }
    if (source->top == NULL){
	return stack_create();
    }

    Stack *clone_reversed = stack_create();

    Node *current = source->top;
    while(current != NULL){
	stack_push(clone_reversed, current->data);
	current = current->next;
    }

    Stack *destination = stack_create();

    current = clone_reversed->top;
    while(current != NULL){
	stack_push(destination, current->data);
	current = current->next;
    }

    return destination;
}

/*
 *Empties the stack, but doesn't destroy it
 */
void stack_make_empty(Stack *stack){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }
    Node* current = stack->top;
    while (current != NULL){
	Node* temp = current;
	current = current->next;
	free(temp);
    }
    stack->top = NULL;
}

void stack_push(Stack* stack, int value){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }
    if (stack_is_full(stack)){
	fprintf(ERROR_FORMAT, "stack overflow");
	exit(1);
    }

    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = value;

    new_node->next = stack->top;
    stack->top = new_node;
}

void stack_print(Stack *stack){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }
    Node *current = stack->top;
    while(current != NULL){
	printf("%d ", current->data);
	current = current->next;
    }
    printf("\n");
}

DATA_TYPE stack_pop(Stack* stack){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }
    if (stack_is_empty(stack)){
	fprintf(ERROR_FORMAT, "stack underflow");
	exit(1);
    }

    Node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);

    return data;
}

DATA_TYPE stack_top(Stack* stack){
    if (stack == NULL){
	fprintf(ERROR_FORMAT, "acessing non-existant stack");
	exit(1);
    }
    if (stack_is_empty(stack)){
	fprintf(ERROR_FORMAT, "stack overflow");
	exit(1);
    }
    
    return stack->top->data;
}
