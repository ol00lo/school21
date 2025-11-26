#include "stack.h"

#include <stdlib.h>

void stack_init(Stack *s) { s->curr_token = -1; }

void stack_add_token(Stack *s, Token *t) {
    if (s->curr_token < MAX_STACK_LEN - 1)
        s->tokens[++s->curr_token] = t;
    else
        printf("n/a");
}

Token *stack_pop_token(Stack *s) {
    if (s->curr_token >= 0) return s->tokens[s->curr_token--];
    return NULL;
}

Token *stack_peek_token(Stack *s) {
    if (s->curr_token >= 0) return s->tokens[s->curr_token];
    return NULL;
}

int stack_empty(Stack *s) { return s->curr_token == -1; }

void stack_freee(Stack *s) {
    for (int i = 0; i < s->curr_token; i++) {
        if (s->tokens[i]) free(s->tokens[i]);
    }
}
