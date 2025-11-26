#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token* token_add_number(double val) {
    Token* ct = (Token*)malloc(sizeof(Token));
    ct->type = 0;
    ct->value = val;
    return ct;
}

Token* token_add_oper(char ch) {
    Token* ct = (Token*)malloc(sizeof(Token));
    ct->type = 1;
    ct->oper = ch;
    return ct;
}

Token* token_add_var() {
    Token* ct = (Token*)malloc(sizeof(Token));
    ct->type = 2;
    return ct;
}

Token* token_add_func(char fname[16]) {
    Token* ct = (Token*)malloc(sizeof(Token));
    ct->type = 3;
    strncpy(ct->fname, fname, 16);
    return ct;
}
