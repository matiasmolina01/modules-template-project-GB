/*
 * -----------------------------------------------------------------------------
 * stack.h
 *
 * Usage:
 *     si
 *
 * Status:
 *     Finished.
 *
 * 
 * Author: [---]
 * -----------------------------------------------------------------------------
 */

#ifndef MODULE_STACK_H
#define MODULE_STACK_H

typedef struct Stack Stack;

#include "../main.h"

typedef struct StackItem {
	int symbol_id;
	int state;
} StackItem;

typedef struct Stack {
	StackItem *stack_list;
	int top;
	int capacity;
} Stack;

/* Creates and initializes a stack with given capacity. Returns a pointer to the stack or NULL on failure. */
Stack *create_stack(int capacity);

/* Frees all memory used by the stack. */
void destroy_stack(Stack *stack);

/* Pushes a new StackItem with symbol_id and state into the stack. Returns 1 on success, 0 on failure. */
int stack_push(Stack *stack, int symbol_id, int state);

/* Removes the top element of the stack. Returns 1 on success, 0 if stack is empty. */
int stack_pop(Stack *stack);

/* Returns a pointer to the top StackItem, or NULL if stack is empty. */
StackItem *stack_peek(Stack *stack);

/* Returns 1 if the stack is empty, 0 otherwise. */
int stack_is_empty(Stack *stack);

/* Returns 1 if the stack is full, 0 otherwise. */
int stack_is_full(Stack *stack);

/* Resets the stack to empty state. */
void stack_clear(Stack *stack);

//returns the state of the top element of the stack
int stack_top_state(Stack *stack);

#endif