#include "easyrpn.h"
#include <stdio.h>
#include <stdlib.h>

// -- Calculator State --

rpn_calc *rpn_init() {
  rpn_calc *calc = malloc(sizeof(rpn_calc));
  if (calc == NULL)
    return NULL;

  // initialize the stack
  calc->stack.top = NULL;
  calc->stack.bottom = NULL;
  calc->stack.size = 0;

  return calc;
}

void rpn_deinit(rpn_calc *calc) {
  rpn_stacknode *ptr = calc->stack.bottom;
  if (ptr != NULL) {
    rpn_stacknode *next = ptr->next;
    while (ptr != NULL) {
      next = ptr->next;
      free(ptr);
      ptr = next;
    }
  }
  free(calc);
}

rpn_stacknode *rpn_stack_empty_node() {
  rpn_stacknode *node = malloc(sizeof(rpn_stacknode));
  if (node == NULL)
    return NULL;
  node->next = NULL;
  node->prev = NULL;
  node->data = 0.0;
  return node;
}

int rpn_stack_push(rpn_calc *calc, double num) {
  rpn_stacknode *prev_top = calc->stack.top;
  rpn_stacknode *top = rpn_stack_empty_node();
  if (top == NULL) {
    return -1;
  }
  top->data = num;

  if (prev_top != NULL) {
    top->prev = prev_top;
    prev_top->next = top;
  } else {
    // If no items in the stack, add to bottom too
    calc->stack.bottom = top;
  }
  calc->stack.top = top;
  calc->stack.size++;

  return 0;
}

double rpn_stack_drop(rpn_calc *calc) {
  rpn_stacknode *prev_top = calc->stack.top;
  rpn_stacknode *new_top = prev_top->prev;
  double data = prev_top->data;

  if (new_top != NULL) {
    new_top->next = NULL;
  } else {
    calc->stack.bottom = NULL;
  }
  calc->stack.top = new_top;
  free(prev_top);
  calc->stack.size--;

  return data;
}

int rpn_stack_swap(rpn_calc *calc) {
  rpn_stacknode *x = calc->stack.top;
  if (x == NULL)
    return -1;
  rpn_stacknode *y = x->next;
  if (y == NULL)
    return -1;

  x->prev = y->prev;
  x->next = y;
  y->prev = x;
  y->next = NULL;

  return 0;
}

void rpn_stack_roll(rpn_calc *calc) {
  rpn_stacknode *top = calc->stack.top;
  if (top == NULL || top->prev == NULL)
    return;
  calc->stack.top = top->prev;
  top->next = calc->stack.bottom;
  calc->stack.bottom = top;
}

// -- Basic Arithmetic --

#define DOUBLE_ARGUMENT(name, operation)                                       \
                                                                               \
  int rpn_##name(rpn_calc *calc) {                                             \
    if (calc->stack.size < 2)                                                  \
      return -1;                                                               \
    double dropped = rpn_stack_drop(calc);                                     \
    calc->stack.top->data = calc->stack.top->data operation dropped;           \
    return 0;                                                                  \
  }

DOUBLE_ARGUMENT(add, +);
DOUBLE_ARGUMENT(subtract, -);
DOUBLE_ARGUMENT(multiply, *);
DOUBLE_ARGUMENT(divide, /);
