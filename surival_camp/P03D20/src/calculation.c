#include "calculation.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

double calc_func(Token* t, Token* arg, int* is_correct) {
    double res;
    if (strcmp(t->fname, "sin") == 0)
        res = sin(arg->value);
    else if (strcmp(t->fname, "cos") == 0)
        res = cos(arg->value);
    else if (strcmp(t->fname, "tan") == 0)
        res = tan(arg->value);
    else if (strcmp(t->fname, "ctg") == 0)
        res = 1 / tan(arg->value);
    else if (strcmp(t->fname, "ln") == 0) {
        if (arg->value <= 0) {
            *is_correct = 1;
            free(arg);
            free(t);
            res = 0;
        } else
            res = log(arg->value);
    } else if (strcmp(t->fname, "sqrt") == 0) {
        if (arg->value < 0) {
            *is_correct = 1;
            free(arg);
            free(t);
            res = 0;
        } else
            res = sqrt(arg->value);
    } else {
        *is_correct = 1;
        res = 0;
    }
    return res;
}

double calc_oper(Token* t, Token* right, Token* left, int* is_correct) {
    double res;
    switch (t->oper) {
        case '+':
            res = left->value + right->value;
            break;
        case '-':
            res = left->value - right->value;
            break;
        case '*':
            res = left->value * right->value;
            break;
        case '/': {
            if (right->value == 0) {
                *is_correct = 1;
                res = 0;
            } else
                res = left->value + right->value;
            break;
        }
        default:
            *is_correct = 1;
            res = 0;
            break;
    }
    return res;
}

double calc_res(Stack* s, double x, int* is_correct) {
    Stack calc;
    stack_init(&calc);
    *is_correct = 0;

    for (int i = 0; i <= s->curr_token; i++) {
        Token* t = s->tokens[i];
        if (t->type == 0) {
            stack_add_token(&calc, token_add_number(t->value));
        } else if (t->type == 2) {
            stack_add_token(&calc, token_add_number(x));
        } else if (t->type == 3) {
            if (calc.curr_token < 0) {
                *is_correct = 1;
            } else {
                Token* arg = stack_pop_token(&calc);
                double res = calc_func(t, arg, is_correct);
                free(arg);
                stack_add_token(&calc, token_add_number(res));
            }
        } else if (t->type == 1) {
            if (calc.curr_token < 1) {
                *is_correct = 1;
            } else {
                Token* right = stack_pop_token(&calc);
                Token* left = stack_pop_token(&calc);
                double res = calc_oper(t, right, left, is_correct);
                free(left);
                free(right);
                stack_add_token(&calc, token_add_number(res));
            }
        }
    }
    if (calc.curr_token != 0) *is_correct = 1;
    double res = calc.tokens[0]->value;
    free(calc.tokens[0]);
    return (is_correct) ? res : 0;
}