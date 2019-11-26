
#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

struct stack {

    int* arr;
    int top;

    int size;
    int capacity;
};

typedef struct stack Stack;

Stack* init_stack(int capacity) {

    Stack* stack = (Stack*) malloc(sizeof(Stack));

    stack->arr = (int*) malloc(sizeof(int) * capacity);
    
    stack->top = -1;
    stack->size = 0;
    stack->capacity = capacity;

    return stack;
}

int stack_empty(Stack* stack) {
    return stack->size == 0;
}

int stack_full(Stack* stack) {
    return stack->size == stack->capacity;
}

void push(Stack* stack, int data) {

    if(!stack_full(stack)) {

        stack->top++;

        stack->arr[stack->top] = data;
        stack->size++;

    } else {
        printf("STACK FULL\n");
    }
}

int pop(Stack* stack) {

    if(!stack_empty(stack)) {

        int data = stack->arr[stack->top--];
        stack->size--;

        return data;

    } else {
        return -1;
    }
}

int peek(Stack* stack) {

    if(stack_empty(stack)) {

        int data = stack->arr[stack->top];
        return data;

    } else {
        return -1;
    }
}

void print_stack(Stack* stack) {

    if(stack) {

        for(int i = stack->top; i >= 0; i--) {
            printf("%d ", stack->arr[i]);
        }

        printf("\n");
    }
}

#endif