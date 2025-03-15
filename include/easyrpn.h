#ifndef LIBRPN_H
#define LIBRPN_H

// -- Calculator state --

typedef struct rpn_stacknode {
  double data;
  struct rpn_stacknode *next;
  struct rpn_stacknode *prev;
} rpn_stacknode;

typedef struct rpn_stack {
  rpn_stacknode *top;
  rpn_stacknode *bottom;
  int size;
} rpn_stack;

typedef struct rpn_calc {
  rpn_stack stack;
} rpn_calc;

/// Create a new calculator state
rpn_calc *rpn_init();
/// Destroy all app data, this frees `calc`
void rpn_deinit(rpn_calc *calc);
/// Adds `num` to the top of the stack
int rpn_stack_push(rpn_calc *calc, double num);
/// Remove the top number in the stack
double rpn_stack_drop(rpn_calc *calc);
/// Swap the top two values on the stack
int rpn_stack_swap(rpn_calc *calc);
/// Roll the top value to the last value and move every other value forwards.
void rpn_stack_roll(rpn_calc *calc);

// -- Basic arithmetic functions

/// Adds `num` to the top number on the stack
int rpn_add(rpn_calc *calc);

#endif // !LIBRPN_H
