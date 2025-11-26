#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
    int type;
    double value;
    char oper;
    char fname[16];
} Token;

Token *token_add_number(double val);
Token *token_add_oper(char ch);
Token *token_add_var();
Token *token_add_func(char fname[16]);

#endif