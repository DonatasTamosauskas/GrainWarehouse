#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stack_create(StackType **stack)
{
    *stack = malloc(sizeof(StackType));

    if (*stack != NULL) {
        (*stack)->top = NULL;
        (*stack)->length = 0;

        return 1;
    }

    return 0;
}

int stack_push(StackType *stack, StackContentType content)
{
    StackElementType *stack_element = malloc(sizeof(StackElementType));

    if (stack_element == NULL) {
        // Unable to allocate memory.
        return 0;
    }

    stack_element->data = content;
    stack_element->next = stack->top;
    stack->top = stack_element;
    stack->length++;

    return 1;
}

int stack_pop(StackType *stack, StackContentType *content)
{
    if (stack->top == NULL) {
        // Stack is empty.
        return 0;
    }

    StackElementType *tmp_element = stack->top;
    stack->top = tmp_element->next;
    stack->length--;
    *content = tmp_element->data;

    free(tmp_element);

    return 1;
}

int stack_destroy(StackType *stack)
{
    StackContentType *tmp = malloc(sizeof(StackContentType));

    while (stack_pop(stack, tmp));

    free(stack);
    free(tmp);

    return 1;
}

int stack_is_full(StackType *stack)
{
    StackElementType *stack_element = malloc(sizeof(StackElementType));

    if (stack_element != NULL) {
        free(stack_element);

        return 0;
    }

    return 1;
}

int stack_is_empty(StackType *stack)
{
    return stack->top == NULL;
}

int stack_length(StackType *stack)
{
    return stack->length;
}

int stack_peak(StackType *stack, StackContentType *content)
{
    if (stack->top == NULL) {
        // Stack is empty.
        return 0;
    }

    *content = stack->top->data;

    return 1;
}
