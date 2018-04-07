/*
 * 307
 *
 * Stack structure is defined by StackType.
 *
 * To create stack:
 *
 * StackType *stack;
 * stack_create(&stack);
 */
#ifndef STACK_H
#define STACK_H

typedef int StackContentType;
typedef struct StackStructure StackType;
typedef struct StackElement StackElementType;

struct StackStructure
{
    StackElementType *top;
    int length;
};

struct StackElement
{
    StackContentType data;
    StackElementType *next;
};

/*
 * Initiates an empty instance of stack.
 *
 * Returns 1 if stack was initiated successfully. Returns 0 otherwise.
 */
int stack_create(StackType **stack);

/*
 * Frees memory used by the stack structure.
 *
 * Returns 1 if destruction was successful. Returns 0 otherwise.
 * Behaviour is undefined if the provided stack has not been properly initiated.
 */
int stack_destroy(StackType *stack);

/*
 * Pushes a piece of data into the stack.
 *
 * Returns 1 if the stack_push was successful. Returns 0 in case of failure.
 */
int stack_push(StackType *stack, StackContentType content);

/*
 * Pops a piece of data from the provided stack. Pushed value is assigned to the var the pointer points to.
 *
 * Returns 1 if the operation was successful. Returns 0 otherwise.
 */
int stack_pop(StackType *stack, StackContentType *content);

/*
 * Returns 1 if the provided instance of stack has no elements. Returns 0 otherwise.
 */
int stack_is_empty(StackType *stack);

/*
 * Returns 1 if it is possible to stack_push one more item into the provided stack. Returns 0 otherwise.
 */
int stack_is_full(StackType *stack);

/*
 * Returns count of elements in the provided stack.
 */
int stack_length(StackType *stack);

/*
 * Returns 1 if stack is not empty, returns 0 otherwise.
 */
int stack_peak(StackType *stack, StackContentType *content);

#endif
