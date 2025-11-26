#ifndef STACK_H
#define STACK_H

#include <stdio.h>

#include "token.h"

#define MAX_STACK_LEN 100

typedef struct {
    Token *tokens[MAX_STACK_LEN];
    int curr_token;
} Stack;

void stack_init(Stack *s);
void stack_add_token(Stack *s, Token *t);
Token *stack_pop_token(Stack *s);
Token *stack_peek_token(Stack *s);
int stack_empty(Stack *s);
void stack_freee(Stack *s);

#endif