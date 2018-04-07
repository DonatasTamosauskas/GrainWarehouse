#include <stdio.h>
#include "stack.h"

int main()
{
    StackContentType content;
    StackType* stack;

    printf("Ar pavyko sukurti stack: %d.\n", stack_create(&stack));

    printf(
        "Ar stack tuščias: %d; ar stack pilnas: %d; elementų skaičius: %d.\n",
        stack_is_empty(stack),
        stack_is_full(stack),
        stack_length(stack)
    );

    stack_push(stack, 599);
    stack_push(stack, 11);
    stack_push(stack, 333);
    stack_push(stack, 23);
    stack_push(stack, 345);

    printf(
        "Ar stack tuščias: %d; elementų skaičius: %d.\n\n",
        stack_is_empty(stack),
        stack_length(stack)
    );

    stack_peak(stack, &content);
    printf("Peak: %d, elementų skaičius: %d\n", content, stack_length(stack));

    while (stack_pop(stack, &content)) {
        printf("%d\n", content);
    }

    printf("Ar stack tuščias: %d.\n\n", stack_is_empty(stack));

    printf("Ar pavyko sunaikinti stack: %d.\n", stack_destroy(stack));

    return 1;
}
