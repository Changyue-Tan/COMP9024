
// an implementation of Stack ADT using array

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIAL_STACK_SIZE 2
#define TOP_POS_FOR_EMPTY_STACK -1

typedef long STACK_ITEM_T;

struct Stack {
    long size;
    long top;
    STACK_ITEM_T *pItems;
};

struct Stack *CreateStack(void);
void ReleaseStack(struct Stack *pStack);
void StackPush(struct Stack *pStack, STACK_ITEM_T item);
STACK_ITEM_T StackPop(struct Stack *pStack);
STACK_ITEM_T StackPeek(struct Stack *pStack);
int StackIsEmpty(struct Stack *pStack);

void printStack(struct Stack *pStack);

int main(void) {
    struct Stack *stack = CreateStack();
    StackPush(stack, 1);
    printStack(stack);
    StackPush(stack, 2);
    printStack(stack);
    StackPush(stack, 3);
    printStack(stack);
    StackPush(stack, 4);
    printStack(stack);
    StackPush(stack, 5);
    printStack(stack);
    return 0;
}

static int StackIsFull(struct Stack *pStack) {
    // if the top of the stack has index of size - 1. then stack is full
    return pStack->top == pStack->size - 1;    
}

int StackIsEmpty(struct Stack *pStack) {
    // if the top of the stack has index of - 1. then stack is empty
    return pStack->top == TOP_POS_FOR_EMPTY_STACK;
}

// Create a stack
struct Stack *CreateStack(void) {
    struct Stack *pStack;
    STACK_ITEM_T *pItems;

    pStack = (struct Stack *) malloc(sizeof(struct Stack));
    pItems = (STACK_ITEM_T *) malloc(sizeof(STACK_ITEM_T) * INITIAL_STACK_SIZE);
    // pStack = malloc(sizeof(struct Stack));
    // pItems = malloc(sizeof(STACK_ITEM_T) * INITIAL_STACK_SIZE);
    // NOTE:
    //      ChatGPT says it is good In modern C, 
    //      it's considered good practice to avoid casting malloc 
    //      unless you're dealing with C++.
    
    assert(pStack && pItems);

    pStack->size = INITIAL_STACK_SIZE;    
    pStack->top = TOP_POS_FOR_EMPTY_STACK;
    pStack->pItems = pItems;

    return pStack;
}

void ReleaseStack(struct Stack *pStack) {
    if (pStack) {
        free(pStack->pItems);
        free(pStack);
    }
}

// Push an item onto/at the top of the stack 
void StackPush(struct Stack *pStack, STACK_ITEM_T item) {
    if (StackIsFull(pStack)) {
        /*
            Please complete the following code in Q1-Q5.

            Q1. call malloc() to allocate enough bytes of heap memory,
                and save the return value in a pointer variable named as newItems           
          
            Q2. call memcpy() to copy the items pointed to by pStack->pItems 
                to the heap memory pointed to by newItems

                For help, please type 'man memcpy' in the command line.

                $ man memcpy
             
            Q3. call free() to release the unused heap memory
            Q4. double the capacity size of the stack
            Q5. let pStack->pItems point to the heap space allocated in Q1

            You need to echo these questions in our weekly Quiz.
            Our tutors will NOT answer these questions in the tutorial.

            To test the code you have completed, you can set INITIAL_STACK_SIZE to be 2 (line 8 in Stack.c)
         */
    
        // Double the capacity of the stack        
        
        // Q1. ___________________
        STACK_ITEM_T *newItems = malloc(2 * pStack->size * sizeof(STACK_ITEM_T));
        
        assert(newItems);
        // Q2. ___________________
        memcpy(newItems, pStack->pItems, pStack->size * sizeof(STACK_ITEM_T));
        // Q3. ___________________
        free(pStack->pItems);
        // Q4. ___________________
        pStack->size = pStack->size * 2;
        // Q5. ___________________
        pStack->pItems = newItems;
    }

    // Now the stack is not full. Let us do the push operation.
    pStack->top++;
    pStack->pItems[pStack->top] = item;
}

// Pop the top item from the stack
STACK_ITEM_T StackPop(struct Stack *pStack) {
    assert(!StackIsEmpty(pStack));

    STACK_ITEM_T item = pStack->pItems[pStack->top];
    pStack->top--;

    return item;
}

// Peek the top item without popping
STACK_ITEM_T StackPeek(struct Stack *pStack) {
    assert(!StackIsEmpty(pStack));

    STACK_ITEM_T item = pStack->pItems[pStack->top];
    return item;
}

void printStack(struct Stack *pStack) {
    int i = 0;
    int n = pStack->top;
    for (; i <= n; i++) {
        printf("%ld ", pStack->pItems[i]);
    }
    printf("\n");
}