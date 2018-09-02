#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>

#define STACK_INITIAL_CAP (8)

typedef struct _StackRecord {
  int capacity;
  int top;
  stack_element_t *array;
} * Stack;

Stack stack_create() {
  Stack s = malloc(sizeof(struct _StackRecord));
  s->capacity = STACK_INITIAL_CAP;
  s->top = -1;
  s->array = malloc(sizeof(stack_element_t) * s->capacity);
  return s;
}

void stack_destroy(Stack s) {
  if (!s)
    return;
  free(s->array);
  free(s);
}

int stack_empty(Stack s) { return s->top == -1; }

stack_element_t stack_top(Stack s) {
  if (s->top == -1)
    exit(1);
  return s->array[s->top];
}

void stack_push(Stack s, stack_element_t e) {
  s->top++;
  if (s->top >= s->capacity) {
    s->capacity *= 2;
    s->array = realloc(s->array, sizeof(stack_element_t) * s->capacity);
  }
  s->array[s->top] = e;
}

void stack_pop(Stack s) {
  if (s->top == -1)
    exit(1);
  s->top--;
}

#endif
