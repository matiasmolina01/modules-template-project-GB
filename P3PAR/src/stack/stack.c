/*
 * -----------------------------------------------------------------------------
 * stack.c
 *
 * Usage:
 *     Simple stack
 *
 * Status:
 *     Finished.
 *
 * 
 * Author: [Marti Ponsa Ramila]
 * -----------------------------------------------------------------------------
 */

 #include "./stack.h"

 /* Allocates memory for the stack structure and its internal array. */
Stack *create_stack(int capacity)
{
    if (capacity <= 0)
        return NULL;

    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
        return NULL;

    stack->stack_list = (StackItem *)malloc(sizeof(StackItem) * capacity);
    if (!stack->stack_list)
    {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->top = -1;

    return stack;
}

/* Frees the stack array and the stack structure. */
void destroy_stack(Stack *stack)
{
    if (!stack)
        return;

    free(stack->stack_list);
    free(stack);
}

/* Inserts a new StackItem at the top of the stack. */
int stack_push(Stack *stack, int symbol_id, int state)
{
    if (!stack || stack_is_full(stack))
        return 0;

    printf("pushing(%d, %d)\n", symbol_id, state);
    
    stack->top++;
    stack->stack_list[stack->top].symbol_id = symbol_id;
    stack->stack_list[stack->top].state = state;

    return 1;
}

/* Removes the top StackItem from the stack. */
int stack_pop(Stack *stack)
{
    if (!stack || stack_is_empty(stack))
        return 0;

    stack->top--;
    return 1;
}

/* Returns the top StackItem without removing it. */
StackItem *stack_peek(Stack *stack)
{
    if (!stack || stack_is_empty(stack))
        return NULL;

    return &stack->stack_list[stack->top];
}

int stack_top_state(Stack *stack)
{
	if (!stack || stack_is_empty(stack))
		return -1; // Return -1 to indicate an error or empty stack

	return stack->stack_list[stack->top].state;
}

/* Checks whether the stack contains no elements. */
int stack_is_empty(Stack *stack)
{
    if (!stack)
        return 1;

    return stack->top == -1;
}

/* Checks whether the stack reached its maximum capacity. */
int stack_is_full(Stack *stack)
{
    if (!stack)
        return 0;

    return stack->top == stack->capacity - 1;
}

/* Resets the stack to its initial empty state. */
void stack_clear(Stack *stack)
{
    if (!stack)
        return;

    stack->top = -1;
}