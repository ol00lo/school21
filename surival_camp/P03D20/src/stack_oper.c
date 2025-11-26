#include "stack_oper.h"

#include <stdlib.h>
#include <string.h>

int is_digit(char c) { return c >= '0' && c <= '9'; }

int is_letter(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

int get_priority(char oper) {
    switch (oper) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

double atof(const char *str) {
    double result = 0;
    double fraction = 1.0;
    int i = 0;
    int is_point = 0;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            if (!is_point) {
                result = result * 10 + (str[i] - '0');
            } else {
                fraction *= 0.1;
                result += (str[i] - '0') * fraction;
            }
        } else if (str[i] == '.') {
            if (is_point) break;
            is_point = 1;
        } else
            break;
        i++;
    }
    return result;
}

int is_func(const char *ch, int *len) {
    const char *funcs[] = {"sin", "cos", "tan", "ctg", "sqrt", "ln"};
    int num_func = sizeof(funcs) / sizeof(char *);

    for (int i = 0; i < num_func; i++) {
        int clen = strlen(funcs[i]);
        if (strncmp(ch, funcs[i], clen) == 0) {
            *len = clen;
            return 1;
        }
    }
    return 0;
}

Stack tokenize(char *inp) {
    Stack tokens;
    stack_init(&tokens);
    int i = 0;
    int len = strlen(inp);
    while (i < len) {
        if (inp[i] == ' ' || inp[i] == '\t') {
            i++;
        } else if (is_letter(inp[i])) {
            int clen;
            if (is_func(inp + i, &clen)) {
                char fname[16];
                strncpy(fname, inp + i, clen);
                fname[clen] = '\0';
                stack_add_token(&tokens, token_add_func(fname));
                i += clen;
            } else if (inp[i] == 'x') {
                stack_add_token(&tokens, token_add_var());
                i++;
            }
        } else if (is_digit(inp[i])) {
            char num_str[20];
            int j = 0;
            while (i < len && is_digit(inp[i])) num_str[j++] = inp[i++];
            if (i < len && inp[i] == '.') {
                num_str[j++] = inp[i++];
                while (i < len && is_digit(inp[i])) num_str[j++] = inp[i++];
            }
            num_str[j] = '\0';
            double val = atof(num_str);
            stack_add_token(&tokens, token_add_number(val));
        } else if (inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/' || inp[i] == '(' ||
                   inp[i] == ')') {
            stack_add_token(&tokens, token_add_oper(inp[i]));
            i++;
        } else {
            i++;
        }
    }
    return tokens;
}

Stack shunting_yard(Stack *inp) {
    Stack out;
    Stack oper;
    stack_init(&out);
    stack_init(&oper);

    for (int i = 0; i <= inp->curr_token; i++) {
        Token *t = inp->tokens[i];
        if (t->type == 0 || t->type == 2) {
            stack_add_token(&out, t);
        } else if (t->type == 3) {
            stack_add_token(&oper, t);
        } else if (t->type == 1) {
            if (t->oper == '(') {
                stack_add_token(&oper, t);
            } else if (t->oper == ')') {
                while (!stack_empty(&oper) && stack_peek_token(&oper)->oper != '(')
                    stack_add_token(&out, stack_pop_token(&oper));

                if (!stack_empty(&oper) && stack_peek_token(&oper)->oper == '(') free(stack_pop_token(&oper));
                if (!stack_empty(&oper) && stack_peek_token(&oper)->type == 3)
                    stack_add_token(&out, stack_pop_token(&oper));
                free(t);
            } else {
                while (!stack_empty(&oper) && stack_peek_token(&oper)->oper != '(' &&
                       stack_peek_token(&oper)->type != 3 &&
                       get_priority(stack_peek_token(&oper)->oper) >= get_priority(t->oper)) {
                    stack_add_token(&out, stack_pop_token(&oper));
                }
                stack_add_token(&oper, t);
            }
        }
    }
    while (!stack_empty(&oper)) stack_add_token(&out, stack_pop_token(&oper));
    return out;
}