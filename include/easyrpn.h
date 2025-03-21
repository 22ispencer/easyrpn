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

/// Create a new calculator state.
rpn_calc *rpn_init();
/// Destroy all app data, this frees `calc`.
void rpn_deinit(rpn_calc *calc);
/// Adds `num` to the top of the stack.
int rpn_stack_push(rpn_calc *calc, double num);
/// Remove the top number in the stack.
double rpn_stack_drop(rpn_calc *calc);
/// Swap the top two values on the stack.
int rpn_stack_swap(rpn_calc *calc);
/// Roll the top value to the last value and move every other value forwards.
void rpn_stack_roll(rpn_calc *calc);

// -- Basic arithmetic functions --

/// Adds `num` to the top number on the stack.
int rpn_add(rpn_calc *calc);
/// Subtracts `num` from the top number on the stack.
int rpn_subtract(rpn_calc *calc);
/// Multiplies `num` by the top numbers on the stack.
int rpn_multiply(rpn_calc *calc);
/// Divides the top number of the stack by `num`.
int rpn_divide(rpn_calc *calc);

// -- Exponential Operations --

/// Updates the stack by calling e^x on the top value in the stack.
int rpn_exp(rpn_calc *calc);
/// Computes the natural log of the top number of the stack
int rpn_ln(rpn_calc *calc);

// -- Power Operations --

int rpn_pow(rpn_calc *calc);
int rpn_sqrt(rpn_calc *calc);
int rpn_root(rpn_calc *calc);

// -- Trigonometric Operations --

int rpn_sin(rpn_calc *calc);
int rpn_cos(rpn_calc *calc);
int rpn_tan(rpn_calc *calc);
int rpn_asin(rpn_calc *calc);
int rpn_acos(rpn_calc *calc);
int rpn_atan(rpn_calc *calc);

#endif // !LIBRPN_H
