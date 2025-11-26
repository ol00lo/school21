#ifndef STACK_OPER_H
#define STACK_OPER_H

#include "stack.h"

Stack tokenize(char *inp);
Stack shunting_yard(Stack *inp);

#endif