#include "easyrpn.h"
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
  rpn_stacknode *prev_top = calc->stack.top;
  while (prev_top != NULL) {
    calc->stack.top = prev_top->prev;
    free(prev_top);
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

int rpn_stack_push(rpn_calc *calc, float num) {
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

float rpn_stack_drop(rpn_calc *calc) {
  rpn_stacknode *prev_top = calc->stack.top;
  float data = prev_top->data;

  calc->stack.top = prev_top->prev;
  if (prev_top->prev == NULL) {
    calc->stack.bottom = NULL;
  }
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

int rpn_add(rpn_calc *calc) {
  if (calc->stack.top == NULL)
    return -1;
  rpn_stacknode *new_top = calc->stack.top->next;
  if (new_top == NULL)
    return -1;

  new_top->data += rpn_stack_drop(calc);
  calc->stack.top = new_top;

  return 0;
}
